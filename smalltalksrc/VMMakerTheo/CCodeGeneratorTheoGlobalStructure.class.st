Class {
	#name : #CCodeGeneratorTheoGlobalStructure,
	#superclass : #CCodeGeneratorGlobalStructure,
	#category : #VMMakerTheo
}

{ #category : #'C code generator' }
CCodeGeneratorTheoGlobalStructure >> emitCCodeAsFunctionCallOn: aStream level: level method: aMethod [
	"Translate this message send into a C function call"

	aMethod selector == #break ifTrue:
		[aStream nextPutAll: '/* send of break elided */'.
		 ^aMethod].

	"Special case for pluggable modules. Replace messages to interpreterProxy
	 by interpreterProxy->message(..) if the message is not builtin"
	(self shouldGenerateAsInterpreterProxySend: aMethod) ifTrue:
		[(self noteUsedPluginFunction: aMethod selector) ifTrue:
			[aStream nextPutAll: 'interpreterProxy->']].

	aStream nextPutAll: (self cFunctionNameFor: aMethod selector); nextPut: $(.

	"Only include the receiver as the first argument in certain cases.
	 The receiver is always included if it is an expression.
	 If it is a variable:
		 If the vmClass says it is an implicit variable, don't include it.
		 If the variable is 'self' and the method being called is not in
		 the method set (i.e. it is some external code), don't include it."
	(aMethod shouldExcludeReceiverAsFirstArgument: self) ifFalse:
		[(aMethod receiver structTargetKindIn: self) == #struct ifTrue:
			[aStream nextPut: $&].
		aMethod receiver emitCCodeOn: aStream level: level generator: self.
		 aMethod args isEmpty ifFalse:
			[aStream nextPutAll: ', ']].
	aMethod args
		do: [ :arg| arg emitCCodeAsArgumentOn: aStream level: level generator: self]
		separatedBy: [aStream nextPut: $,; space].
	aMethod args ifNotEmpty: [aStream nextPut: $,; space].
	(TVariableNode new setName: #self)
		emitCCodeAsArgumentOn: aStream level: level generator: self.
	aStream nextPut: $)
]

{ #category : #'C code generator' }
CCodeGeneratorTheoGlobalStructure >> emitCFunctionPrototypeForMethod: aMethod isPrototype: isPrototype onStream: aStream [
	| args |
	args := aMethod args copy.
	args add: #self.
	args
		do: [ :arg | aStream nextPutAll: (aMethod declarationAt: arg) ]
		separatedBy: [ aStream nextPutAll: ', ' ].
	aStream nextPut: $)
]

{ #category : #'C code generator' }
CCodeGeneratorTheoGlobalStructure >> emitCMacros: methodList on: aStream [ 
	"Store the global variable declarations on the given stream.  Answer any constants used in the macros."
	| usedConstants |
	macros isEmpty ifTrue: [^#()].
	aStream cr; nextPutAll: '/*** Macros ***/'; cr.
	usedConstants := Set new.
	(methodList reject: [:m| m isRealMethod]) do:
		[:m |
		m definedAsMacro ifTrue:
			[ | macroDefinition |
			macroDefinition := (macros at: m selector) trimBoth.
			(macroDefinition beginsWith: '()')
				ifTrue: [ macroDefinition := '(self)', (macroDefinition allButFirst: 2) ]
				ifFalse:[ macroDefinition := String streamContents: [:s| 
						s << (macroDefinition first: (macroDefinition indexOf: $)) - 1).
						s << ', self'.
						s << (macroDefinition last: (macroDefinition size - (macroDefinition indexOf: $)) + 1)).
						]].
			aStream
				nextPutAll: '#define ';
				nextPutAll:(self cFunctionNameFor: m selector);
				nextPutAll: macroDefinition; cr.
			 m compiledMethod literalsDo:
				[:lit|
				(lit isVariableBinding and: [(macros at: m selector) includesSubstring: lit key]) ifTrue:
					[usedConstants add: lit key]]]].
	aStream cr.
	^usedConstants
]

{ #category : #'C code generator' }
CCodeGeneratorTheoGlobalStructure >> emitCVariablesOn: aStream [
	"Store the global variable declarations on the given stream.
	 Break logic into vars for structure and vars for non-structure."
	| structure nonstruct |

	structure := WriteStream on: (String new: 32768).
	nonstruct := WriteStream on: (String new: 32768).

	aStream nextPutAll: '/*** Variables ***/'; cr.
	structure
		nextPutAll: '#if SQ_USE_GLOBAL_STRUCT'; cr;
		nextPutAll: '# define _iss /* define in-struct static as void */'; cr;
		nextPutAll: 'static struct foo {'; cr;
		nextPutAll: '#else'; cr;
		nextPutAll: '# define _iss static'; cr;
		nextPutAll: '#endif'; cr.
	self buildSortedVariablesCollection do:
		[ :var | | decl varString inStruct target |
		target := (inStruct := self placeInStructure: (varString := var asString)) 
					ifTrue: [structure]
					ifFalse: [nonstruct].
		decl := variableDeclarations at: varString ifAbsent: ['sqInt ' , varString].
		decl first == $# "support cgen var: #bytecodeSetSelector declareC: '#define bytecodeSetSelector 0' hack"
			ifTrue:
				[target nextPutAll: decl; cr]
			ifFalse:
				[self isGeneratingPluginCode
					ifTrue:
						[varString = 'interpreterProxy'
							ifTrue: "quite special..."
								[self preDeclareInterpreterProxyOn: target]
							ifFalse: [target nextPutAll: 'static ']]
					ifFalse:
						[(vmClass mustBeGlobal: varString) ifFalse:
							[target nextPutAll: (inStruct ifTrue: ['_iss '] ifFalse: ['static '])]].
				target nextPutAll: decl; nextPut: $;; cr]].
	structure
		nextPutAll: '_iss void (*primitiveFunctionPointer)();';cr;
		nextPutAll: '#undef _iss'; cr;
		nextPutAll: '#if SQ_USE_GLOBAL_STRUCT'; cr;
		nextPutAll: ' } fum;'; cr;
		nextPutAll: ' #if SQ_USE_GLOBAL_STRUCT_REG';cr;
		nextPutAll: '# define DECL_MAYBE_SQ_GLOBAL_STRUCT /* using a global reg pointer */'; cr;
		nextPutAll: '# define DECL_MAYBE_VOLATILE_SQ_GLOBAL_STRUCT /* using a global reg pointer */'; cr;
		nextPutAll:'#else';cr;
		nextPutAll: '# define DECL_MAYBE_SQ_GLOBAL_STRUCT register struct foo * foo = &fum;'; cr;
		nextPutAll: '# define DECL_MAYBE_VOLATILE_SQ_GLOBAL_STRUCT volatile register struct foo * foo = &fum;'; cr;
		nextPutAll: '#endif';cr;
		nextPutAll: 'int numberOfImage;'; cr;
		nextPutAll: 'struct foo * all_threads_global;'; cr;
		nextPutAll: 'pthread_t * thread_id;'; cr;
		nextPutAll: '# define GIV(interpreterInstVar) (returnGlobalStructForCurrentThread(0)->interpreterInstVar)'; cr;
		nextPutAll: '#else'; cr;
		nextPutAll: '# define DECL_MAYBE_SQ_GLOBAL_STRUCT /* oh, no mr bill! */'; cr;
		nextPutAll: '# define DECL_MAYBE_VOLATILE_SQ_GLOBAL_STRUCT /* oh no, mr bill! */'; cr;
		nextPutAll: '# define GIV(interpreterInstVar) interpreterInstVar'; cr;
		nextPutAll: '#endif'; cr.

	"if the machine needs the fum structure defining locally, do it now; global register users don't need that, but DO need some batshit insane C macro fudging in order to convert the define of USE_GLOBAL_STRUCT_REG into a simple string to use in the asm clause below. Sigh."
	structure
		nextPutAll: '#if SQ_USE_GLOBAL_STRUCT'; cr;
		nextPutAll: '#if SQ_USE_GLOBAL_STRUCT_REG';cr;
		nextPutAll: '#define fooxstr(s) foostr(s)'; cr;
		nextPutAll: '#define foostr(s)  #s'; cr;
		nextPutAll: 'register struct foo * foo asm(fooxstr(USE_GLOBAL_STRUCT_REG));'; cr;
		nextPutAll: '#else'; cr;
		nextPutAll: 'static struct foo * foo = &fum;'; cr;
		nextPutAll: '#endif'; cr;
		nextPutAll: '#endif'; cr.

	aStream
		nextPutAll: structure contents;
		nextPutAll: nonstruct contents;
		cr
]

{ #category : #'C translation' }
CCodeGeneratorTheoGlobalStructure >> generateDeny: denyMsgNode on: aStream indent: level [
	"Generate the C code for a deny: expr onto the given stream."

	aStream nextPutAll: 'assert(!('.
	self emitCExpression: denyMsgNode args first on: aStream.
	aStream nextPutAll: '), self)'
]
