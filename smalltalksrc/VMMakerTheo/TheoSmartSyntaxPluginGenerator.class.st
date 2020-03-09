Class {
	#name : #TheoSmartSyntaxPluginGenerator,
	#superclass : #SmartSyntaxPluginCodeGenerator,
	#category : #VMMakerTheo
}

{ #category : #'as yet unclassified' }
TheoSmartSyntaxPluginGenerator >> CFunctionAsSelector [

 ^  #(#memcpy:_:_: 
		#sizeof:
		#getenv:
		#free:
		#strlen:
		#log
		#mod:f:
		#sin
		#atan
		#ld:exp:
		#sqrt
		#exp
		#me:ms:et:
		#f:open:
		#putchar:
		#fflush
		#strncmp:_:_: 
		#printf:
		#malloc:
		#strcpy:_:
		#strcat:_:
		#strncpy:_:_:
		#memmove:_:_:
		#c:alloc:
		#re:alloc:
		#strcmp:
		#long:jmp:
		#getchar
		#setjmp:
		#alloca:
		#f:printf:
		#fr:exp:
		#time:
		)
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> emitCCodeAsFunctionCallOn: aStream level: level method: aMethod [
	"Translate this message send into a C function call"

	aMethod selector == #break
		ifTrue: [ aStream nextPutAll: '/* send of break elided */'.
			^ aMethod ].
	"self haltIf: [ (self cFunctionNameFor: aMethod selector) includesSubstring:  'stObjectatput' ]."
	"Special case for pluggable modules. Replace messages to interpreterProxy
	 by interpreterProxy->message(..) if the message is not builtin"
	(self shouldGenerateAsInterpreterProxySend: aMethod)
		ifTrue: [ (self noteUsedPluginFunction: aMethod selector)
				ifTrue: [ aStream nextPutAll: 'interpreterProxy->' ] ].
	aStream
		nextPutAll: (self cFunctionNameFor: aMethod selector);
		nextPut: $(.

	"Only include the receiver as the first argument in certain cases.
	 The receiver is always included if it is an expression.
	 If it is a variable:
		 If the vmClass says it is an implicit variable, don't include it.
		 If the variable is 'self' and the method being called is not in
		 the method set (i.e. it is some external code), don't include it."
	(aMethod shouldExcludeReceiverAsFirstArgument: self)
		ifFalse: [ (aMethod receiver structTargetKindIn: self) == #struct
				ifTrue: [ aStream nextPut: $& ].
			aMethod receiver emitCCodeOn: aStream level: level generator: self.
			(aMethod args isNotEmpty or: [self nonUnarySelector includes: aMethod selector])
				ifTrue: [ aStream nextPutAll: ', ' ]  ].
	aMethod args
		do:
			[ :arg | arg emitCCodeAsArgumentOn: aStream level: level generator: self ]
		separatedBy: [ aStream
				nextPut: $,;
				space ].
	"self haltIf: [ aMethod selector includesSubstring: 'integerObjectOf' ]."
	(self selectorsToExclude includes: aMethod selector)
		ifFalse: [ aMethod args
				ifNotEmpty: [ aStream
						nextPut: $,;
						space ].
			(TVariableNode new setName: #self)
				emitCCodeAsArgumentOn: aStream
				level: level
				generator: self ].
	aStream nextPut: $).
	"self haltIf: [ aStream contents includesSubstring: 'fetchFloatAtinto']."
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> emitCFunctionPrototypeForMethod: aMethod isPrototype: isPrototype onStream: aStream [
	| args declarations |
	args := aMethod args copy.
	declarations := aMethod declarations copy.
	"self haltIf: [ (self cFunctionNameFor: aMethod selector) includesSubstring:  'primitiveCompareString' ]."
	(self selectorExcludedForFunctionPrototype includes: aMethod selector)
		ifFalse: [ args add: #self.
			declarations at: #self put: 'struct foo * self' ].
	args
		do: [ :arg | 
			aStream
				nextPutAll: (declarations at: arg ifAbsent: [ #sqInt , ' ' , arg ]) ]
		separatedBy: [ aStream nextPutAll: ', ' ].
	aStream nextPut: $)
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> emitCFunctionPrototypes: methodList on: aStream [ 
	"Store prototype declarations for all non-inlined methods on the given stream.
	 Add a define for a NoDbgRegParms attribute for static functions used for debugging.
	 gcc and other compilers will use non-standard calling conventions for static functions
	 when optimizing.  The optimization can render the functions unusable in gdb.  The sqConfig.h
	 file for the platform should define PlatformNoDbgRegParms suitably for the platform's
	 compiler, if the compiler can be persuaded not to generate such functions.
	 Add a define for a NeverInline attribute that tells the compiler never to inline functions
	 with the attribute.  We mark functions we want to observe in a profiler as NeverInline.
	 The sqConfig.h file for the platform should define NeverInline suitably for the platform's
	 compiler, if the compiler can be persuaded not to inline certain functions."
	aStream cr; nextPutAll: '/*** Function Prototypes ***/'; cr.
	vmClass ifNotNil:
		[NoRegParmsInAssertVMs ifTrue:
			[aStream nextPutAll: '\\#if !PRODUCTION && defined(PlatformNoDbgRegParms)\# define NoDbgRegParms PlatformNoDbgRegParms\#endif' withCRs.
			 aStream nextPutAll: '\\#if !defined(NoDbgRegParms)\# define NoDbgRegParms /*empty*/\#endif\\' withCRs].
		 aStream nextPutAll: '\\#if !defined(NeverInline)\# define NeverInline /*empty*/\#endif\\' withCRs.].
	aStream nextPutAll: 'struct foo;';cr;cr.
	(methodList select: [:m| m isRealMethod and: [self shouldGenerateMethod: m]]) do:
		[:m |
		vmClass ifNotNil:
			[(NoRegParmsInAssertVMs and: [m export not and: [m isStatic and: [m args notEmpty]]]) ifTrue:
				[m addFunctionAttribute: 'NoDbgRegParms'].
			 m inline == #never ifTrue:
				[m addFunctionAttribute: 'NeverInline']].
		m emitCFunctionPrototype: aStream generator: self].
	aStream cr
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> genCallOf: aSelector withAll: nodes on: aStream [
	"self haltIf: [ aSelector includesSubstring: 'integerObjectOf' ]."
	^ super
		genCallOf: aSelector
		withAll: nodes, {
			(TVariableNode new setName: #self)
				"emitCCodeAsArgumentOn: aStream
				level: 0
				generator: self" }
		on: aStream
]

{ #category : #'asOop:/asValue:' }
TheoSmartSyntaxPluginGenerator >> generateCoerceToBooleanObjectFrom: aNode on: aStream [
	pluginFunctionsUsed add: #trueObject; add: #falseObject.
	aStream nextPutAll: '(('.
	self emitCExpression: aNode on: aStream.
	aStream nextPutAll: ') ? trueObject(self) : falseObject(self))'
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> preDeclareMacrosForFastClassCheckingOn: aStream [
	"These macros can be used to check for various cases of Integer types.
	 Since they can be defined based on existing API, this is a good trade off:
	 - avoid extending the interpreterProxy API unnecessarily
	 - provide fast type checking"
	
	"Speed-up generated code for internal plugins by using macros and fixed class indices to define this well known functionality."
	#(	'#if defined(SQUEAK_BUILTIN_PLUGIN)' cr

		'# define isIntegerObject(oop, self) ((oop) & 1)' cr

		'# if SPURVM'
		'extern sqInt classIndexOf(sqInt, struct foo *);'
	"Compact class indices are hardcoded here because there is no guarantee that the pool values at generation time
	 are that of SPUR.. Make sure they are in sync with SpurMemoryManager class>>initializeCompactClassIndices"
		'#	define LargeNegativeIntegerClassIndex 32'
		'#	define LargePositiveIntegerClassIndex 33'
		'#	if BytesPerOop == 4'
		'#	  define isImmediate(oop, self) ((oop) & 3)'
		'#	else'
		'#	  define isImmediate(oop, self) ((oop) & 7)'
		'#	endif'
		'#	define isKindOfInteger(oop, self) (isImmediate(oop, self) ? isIntegerObject(oop, self) : (unsigned)(classIndexOf(oop, self) - LargeNegativeIntegerClassIndex) <= 1)'
		'#	define isLargeIntegerObject(oop, self) (!isImmediate(oop, self) && (unsigned)(classIndexOf(oop, self) - LargeNegativeIntegerClassIndex) <= 1)'
		'#	define isLargeNegativeIntegerObject(oop, self) (!isImmediate(oop, self) && classIndexOf(oop, self) == LargeNegativeIntegerClassIndex)'
		'#	define isLargePositiveIntegerObject(oop, self) (!isImmediate(oop, self) && classIndexOf(oop, self) == LargePositiveIntegerClassIndex)'
		'# endif /* SPURVM */'
		'#endif /* defined(SQUEAK_BUILTIN_PLUGIN) */' cr

	"If the functionality has not been defined via macros, define default versions using existing plugin API"
		'#if !defined(isKindOfInteger)'
		'# define isLargeNegativeIntegerObject(oop, self) (fetchClassOf(oop, self) == classLargeNegativeInteger(self))'
		'# define isLargePositiveIntegerObject(oop, self) (fetchClassOf(oop, self) == classLargePositiveInteger(self))'
		'# define isLargeIntegerObject(oop, self) (isLargeNegativeIntegerObject(oop, self) || isLargePositiveIntegerObject(oop, self))'
		'# define isKindOfInteger(oop , self) (isIntegerObject(oop, self) || isLargeNegativeIntegerObject(oop, self) || isLargePositiveIntegerObject(oop, self))'
		'#endif' cr) do:
		[:element|
		aStream cr.
		element ~~ #cr ifTrue: [aStream nextPutAll: element]]
]

{ #category : #'as yet unclassified' }
TheoSmartSyntaxPluginGenerator >> selectorExcludedForCommodities [

 ^  #(#minorVersion
#majorVersion
		) , self selectorExcludedForFunctionPrototype 
]

{ #category : #'C code generator' }
TheoSmartSyntaxPluginGenerator >> selectorExcludedForFunctionPrototype [

 ^ 	#(
	)	
]

{ #category : #'as yet unclassified' }
TheoSmartSyntaxPluginGenerator >> selectorsToExclude [

	^ self CFunctionAsSelector, self selectorExcludedForCommodities 
]
