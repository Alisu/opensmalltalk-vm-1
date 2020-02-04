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
	aStream nextPut: $,; space.
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
