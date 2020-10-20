Class {
	#name : #CMutexAndCond,
	#superclass : #VMStructType,
	#instVars : [
		'mutex',
		'condition'
	],
	#category : #'VMMaker-Support'
}

{ #category : #translation }
CMutexAndCond class >> instVarNamesAndTypesForTranslationDo: aBinaryBlock [
	"Enumerate aBinaryBlock with the names and C type strings for the inst vars to include in the typedef for the reciever."
	"self typedef"
	self instVarNames do:
		[:ivn|
		aBinaryBlock
			value: ivn
			value: (ivn caseOf: {
						['mutex']		-> [#'pthread_mutex_t'].
						['condition']		-> [#'pthread_cond_t *'].
					 }
					otherwise:
						[#sqInt])]
]

{ #category : #accessing }
CMutexAndCond >> condition [
	^ condition
]

{ #category : #accessing }
CMutexAndCond >> condition: anObject [
	condition := anObject
]

{ #category : #accessing }
CMutexAndCond >> mutex [
	^ mutex
]

{ #category : #accessing }
CMutexAndCond >> mutex: anObject [
	mutex := anObject
]
