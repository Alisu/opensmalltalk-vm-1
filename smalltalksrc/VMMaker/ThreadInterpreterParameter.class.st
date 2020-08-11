Class {
	#name : #ThreadInterpreterParameter,
	#superclass : #VMStructType,
	#instVars : [
		'imagePath',
		'imageArguments',
		'interpreterState'
	],
	#category : #'VMMaker-Support'
}

{ #category : #translation }
ThreadInterpreterParameter class >> instVarNamesAndTypesForTranslationDo: aBinaryBlock [
	"Enumerate aBinaryBlock with the names and C type strings for the inst vars to include in the typedef for the reciever."
	"self typedef"
	self instVarNames do:
		[:ivn|
		aBinaryBlock
			value: ivn
			value: (ivn caseOf: {
						['imagePath']		-> [#'char  *'].
						['imageArguments']		-> [#'char *'].
						['interpreterState']	-> [#'struct foo *']. }
					otherwise:
						[#sqInt])]
]

{ #category : #accessing }
ThreadInterpreterParameter >> imageArguments [
	^ imageArguments
]

{ #category : #accessing }
ThreadInterpreterParameter >> imageArguments: anObject [
	imageArguments := anObject
]

{ #category : #accessing }
ThreadInterpreterParameter >> imagePath [
	^ imagePath
]

{ #category : #accessing }
ThreadInterpreterParameter >> imagePath: anObject [
	imagePath := anObject
]

{ #category : #accessing }
ThreadInterpreterParameter >> interpreterState [
	^ interpreterState
]

{ #category : #accessing }
ThreadInterpreterParameter >> interpreterState: anObject [
	interpreterState := anObject
]
