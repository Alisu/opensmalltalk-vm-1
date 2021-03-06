"
SistaRegisterAllocatingCogit is a port of SistaCogit under RegisterAllocatingCogit.  Its subclass SistaCogitClone holds those methods that are identical to SistaCogit's.  This class holds the methods that are different.  SistaRegisterAllocatingCogit's initialize method keeps things up-to-date and arranges that no method implemented in SistaRegisterAllocatingCogit is implemented in SistaCogitClone so that super sends in SistaCogitClone activate code in RegisterAllocatingCogit as intended.

Instance Variables
	branchReachedOnlyForCounterTrip:		<Object>
	ceTrapTrampoline:		<Object>
	counterIndex:		<Object>
	counters:		<Object>
	initialCounterValue:		<Object>
	numCounters:		<Object>

branchReachedOnlyForCounterTrip
	- xxxxx

ceTrapTrampoline
	- xxxxx

counterIndex
	- xxxxx

counters
	- xxxxx

initialCounterValue
	- xxxxx

numCounters
	- xxxxx

"
Class {
	#name : #SistaRegisterAllocatingCogit,
	#superclass : #RegisterAllocatingCogit,
	#instVars : [
		'numCounters',
		'counters',
		'counterIndex',
		'initialCounterValue',
		'ceTrapTrampoline',
		'branchReachedOnlyForCounterTrip'
	],
	#classVars : [
		'CounterBytes',
		'MaxCounterValue'
	],
	#pools : [
		'VMSqueakClassIndices'
	],
	#category : #'VMMaker-JIT'
}

{ #category : #'clone maintennance' }
SistaRegisterAllocatingCogit class >> dateAndTimeFrom: timeStampString [
	^(timeStampString copyFrom: (timeStampString findFirst: [:c| c isDigit]) to: timeStampString size) asDateAndTime
]

{ #category : #'clone maintennance' }
SistaRegisterAllocatingCogit class >> implementation: aMethodReference isDifferentThan: bMethodReference [
	^aMethodReference isValid
	 and: [bMethodReference isValid
			ifTrue: [aMethodReference sourceString ~= bMethodReference sourceString]
			ifFalse: [true]]
]

{ #category : #'clone maintennance' }
SistaRegisterAllocatingCogit class >> implementation: aMethodReference isNewerThan: bMethodReference [
	^(self dateAndTimeFrom: aMethodReference timeStamp) > (self dateAndTimeFrom: bMethodReference timeStamp)
]

{ #category : #'class initialization' }
SistaRegisterAllocatingCogit class >> initializeWithOptions: optionsDictionary [

	self syncCodeWithSistaCogit ifTrue: "The subclass's #initializeWithOptions: method changed; resend."
		[^self initializeWithOptions: optionsDictionary].

	"Things are up-to-date; continue"
	^super initializeWithOptions: optionsDictionary
]

{ #category : #'class initialization' }
SistaRegisterAllocatingCogit class >> syncCodeIn: sourceClass with: destClass leavingUnchanged: selectorOrNil [
	"Make sure that the SistaRegisterAllocatingCogit/SistaCogitClone combination is up-to-date w.r.t. SistaCogit.
	 - 	SistaCogitClone should have all methods in SistaCogit except those implemented in SistaRegisterAllocatingCogit.
		This means that super sends in SistaCogitClone will be understood in SistaRegisterAllocatingCogit, not
		SistaRegisterAllocatingCogit.
	 -	newer methods in SistaCogitClone that are implemented in SistaRegisterAllocatingCogit should be moved up to
		SistaRegisterAllocatingCogit becaude it means that we probably changed them in SistaCogitClone by mistake
		and forgot to copy them up.
	 -	the same goes for the class side, except for the intializeWithOptions: method which /should/ exist in both
		SistaRegisterAllocatingCogit and SistaCogitClone, because it runs this initialization."

	| methodTimeStamp |
	methodTimeStamp := selectorOrNil ifNotNil:
					[(destClass superclass >>> selectorOrNil) isValid ifTrue:
						[(destClass >>> selectorOrNil) isValid
							ifTrue: [(destClass >>> selectorOrNil) timeStamp]
							ifFalse: ['ancient 01/01/1901 00:00']]].

	destClass selectorsDo:
		[:s|
		(s ~~ selectorOrNil
		 and: [(destClass superclass >>> s) isValid
		 and: [self implementation: destClass >>> s isNewerThan: destClass superclass >>> s]]) ifTrue:
			[destClass superclass recompile: s from: destClass.
			 (destClass superclass whichCategoryIncludesSelector: s) ~= (destClass whichCategoryIncludesSelector: s) ifTrue:
				[destClass superclass organization classify: s under: (destClass whichCategoryIncludesSelector: s)]]].

	sourceClass selectorsDo:
		[:s|
		(self implementation: sourceClass >>> s isDifferentThan: destClass >>> s) ifTrue:
			[destClass recompile: s from: sourceClass.
			 (destClass whichCategoryIncludesSelector: s) ~= (sourceClass whichCategoryIncludesSelector: s) ifTrue:
				[destClass organization classify: s under: (sourceClass whichCategoryIncludesSelector: s)]]].


	destClass superclass selectorsDo:
		[:s|
		(s ~~ selectorOrNil
		 and: [(destClass >>> s) isValid]) ifTrue:
			[destClass removeSelector: s]].

	^methodTimeStamp notNil
	  and: [(destClass >>> selectorOrNil) isValid
	  and: [(methodTimeStamp beginsWith: 'ancient')
		or: [(self dateAndTimeFrom: (destClass >>> selectorOrNil) timeStamp) ~= (self dateAndTimeFrom: methodTimeStamp)]]]
]

{ #category : #'class initialization' }
SistaRegisterAllocatingCogit class >> syncCodeWithSistaCogit [
	"Make sure that the SistaRegisterAllocatingCogit/SistaCogitClone combination is up-to-date w.r.t. SistaCogit.
	 - 	SistaCogitClone should have all methods in SistaCogit except those implemented in SistaRegisterAllocatingCogit.
		This means that super sends in SistaCogitClone will be understood in SistaRegisterAllocatingCogit, not
		RegisterAllocatingCogit.
	 -	newer methods in SistaCogitClone that are implemented in SistaRegisterAllocatingCogit should be moved up to
		SistaRegisterAllocatingCogit because it means that we probably changed them in SistaCogitClone by mistake
		and forgot to copy them up.
	 -	the same goes for the class side, except for the intializeWithOptions: method which /should/ exist in both
		SistaRegisterAllocatingCogit and SistaCogitClone, because it runs this initialization."
	| syncAction |
	syncAction :=
		[self syncCodeIn: SistaCogit with: SistaCogitClone leavingUnchanged: nil.
		 self syncCodeIn: SistaCogit class with: SistaCogitClone class leavingUnchanged: #initializeWithOptions:].
	^(Smalltalk classNamed: #CurrentReadOnlySourceFiles)
		ifNil: syncAction
		ifNotNil: [:crosf| crosf cacheDuring: syncAction]
]

{ #category : #'bytecode generator support' }
SistaRegisterAllocatingCogit >> genCounterTripOnlyJumpIf: boolean to: targetBytecodePC [ 
	"Specific version if the branch is only reached while falling through if the counter trips after an inlined #== branch. We do not regenerate the counter logic in this case to avoid 24 bytes instructions."
	
	<var: #ok type: #'AbstractInstruction *'>
	<var: #mustBeBooleanTrampoline type: #'AbstractInstruction *'>

	| ok mustBeBooleanTrampoline |

	extA := 0.
	
	self ssTop popToReg: TempReg.
	self ssPop: 1.

	counterIndex := counterIndex + 1. "counters are increased / decreased in the inlined branch"

	"We need SendNumArgsReg because of the mustBeBooleanTrampoline"
	self ssAllocateRequiredReg: SendNumArgsReg.
	self MoveCq: 1 R: SendNumArgsReg.
	
	"The first time this is reached, it calls necessarily the counter trip for the trampoline because SendNumArgsReg is non zero"
	mustBeBooleanTrampoline := self genCallMustBeBooleanFor: boolean.

	self annotateBytecode: self Label.

	"Cunning trick by LPD.  If true and false are contiguous subtract the smaller.
	 Correct result is either 0 or the distance between them.  If result is not 0 or
	 their distance send mustBeBoolean."
	self assert: (objectMemory objectAfter: objectMemory falseObject) = objectMemory trueObject.
	self genSubConstant: boolean R: TempReg.
	self JumpZero: (self ensureFixupAt: targetBytecodePC).

	self CmpCq: (boolean = objectMemory falseObject
					ifTrue: [objectMemory trueObject - objectMemory falseObject]
					ifFalse: [objectMemory falseObject - objectMemory trueObject])
		R: TempReg.
		
	ok := self JumpZero: 0.
	self MoveCq: 0 R: SendNumArgsReg. "if counterReg is 0 this is a mustBeBoolean, not a counter trip."		

	self Jump: mustBeBooleanTrampoline.
	
	ok jmpTarget: self Label.
	^0
]

{ #category : #'bytecode generators' }
SistaRegisterAllocatingCogit >> genForwardersInlinedIdenticalOrNotIf: orNot [
	"Override to count inlined branches if followed by a conditional branch.
	 We borrow the following conditional branch's counter and when about to
	 inline the comparison we decrement the counter (without writing it back)
	 and if it trips simply abort the inlining, falling back to the normal send which
	 will then continue to the conditional branch which will trip and enter the abort."
	| nextPC postBranchPC targetBytecodePC branchDescriptor counterReg fixup jumpEqual jumpNotEqual
	  counterAddress countTripped unforwardArg unforwardRcvr argReg rcvrReg regMask |
	<var: #fixup type: #'BytecodeFixup *'>
	<var: #countTripped type: #'AbstractInstruction *'>
	<var: #label type: #'AbstractInstruction *'>
	<var: #branchDescriptor type: #'BytecodeDescriptor *'>
	<var: #jumpEqual type: #'AbstractInstruction *'>
	<var: #jumpNotEqual type: #'AbstractInstruction *'>

	((coInterpreter isOptimizedMethod: methodObj) or: [needsFrame not]) ifTrue:
		[^super genForwardersInlinedIdenticalOrNotIf: orNot].

	regMask := 0.
	
	self extractMaybeBranchDescriptorInto: [ :descr :next :postBranch :target | 
		branchDescriptor := descr. nextPC := next. postBranchPC := postBranch. targetBytecodePC := target ].
	
	unforwardRcvr := (objectRepresentation isUnannotatableConstant: (self ssValue: 1)) not.
	unforwardArg := (objectRepresentation isUnannotatableConstant: self ssTop) not.
	
	"If an operand is an annotable constant, it may be forwarded, so we need to store it into a 
	register so the forwarder check can jump back to the comparison after unforwarding the constant.
	However, if one of the operand is an unnanotable constant, does not allocate a register for it 
	(machine code will use operations on constants)."
	rcvrReg:= argReg := NoReg.
	self 
		allocateEqualsEqualsRegistersArgNeedsReg: unforwardArg 
		rcvrNeedsReg: unforwardRcvr 
		into: [ :rcvr :arg | rcvrReg:= rcvr. argReg := arg ].
		
	argReg ~= NoReg ifTrue: [ regMask := self registerMaskFor: argReg ].
	rcvrReg ~= NoReg ifTrue: [ regMask := regMask bitOr: (self registerMaskFor: rcvrReg) ].
	
	"Only interested in inlining if followed by a conditional branch."
	(branchDescriptor isBranchTrue or: [branchDescriptor isBranchFalse]) ifFalse:
		[^ self 
			genIdenticalNoBranchArgIsConstant: unforwardArg not
			rcvrIsConstant: unforwardRcvr not
			argReg: argReg 
			rcvrReg: rcvrReg 
			orNotIf: orNot].
	
	unforwardArg ifTrue: [ objectRepresentation genEnsureOopInRegNotForwarded: argReg scratchReg: TempReg ].
	unforwardRcvr ifTrue: [ objectRepresentation genEnsureOopInRegNotForwarded: rcvrReg scratchReg: TempReg ].
	
	counterReg := self allocateRegNotConflictingWith: regMask.
	self 
		genExecutionCountLogicInto: [ :cAddress :countTripBranch | 
			counterAddress := cAddress. 
			countTripped := countTripBranch ] 
		counterReg: counterReg.
	
	self assert: (unforwardArg or: [ unforwardRcvr ]).
	self genCmpArgIsConstant: unforwardArg not rcvrIsConstant: unforwardRcvr not argReg: argReg rcvrReg: rcvrReg.
	self ssPop: 2.
	
	orNot == branchDescriptor isBranchTrue "orNot is true for ~~"
		ifFalse:
			[ fixup := (self ensureNonMergeFixupAt: postBranchPC) asUnsignedInteger.
			self JumpZero:  (self ensureNonMergeFixupAt: targetBytecodePC) asUnsignedInteger ]
		ifTrue:
			[ fixup := (self ensureNonMergeFixupAt: targetBytecodePC) asUnsignedInteger.
			self JumpZero: (self ensureNonMergeFixupAt: postBranchPC) asUnsignedInteger ].
	
	self genFallsThroughCountLogicCounterReg: counterReg counterAddress: counterAddress.
	self Jump: fixup.
	
	countTripped jmpTarget: self Label.
	
	"inlined version of #== ignoring the branchDescriptor if the counter trips to have normal state for the optimizer"
	self ssPop: -2. 
	self genCmpArgIsConstant: unforwardArg not rcvrIsConstant: unforwardRcvr not argReg: argReg rcvrReg: rcvrReg.
	self ssPop: 2. 
	
	"This code necessarily directly falls through the jumpIf: code which pops the top of the stack into TempReg. 
	We therefore directly assign the result to TempReg to save one move instruction"
	jumpEqual := orNot ifFalse: [self JumpZero: 0] ifTrue: [self JumpNonZero: 0].
	self genMoveFalseR: TempReg.
	jumpNotEqual := self Jump: 0.
	jumpEqual jmpTarget: (self genMoveTrueR: TempReg).
	jumpNotEqual jmpTarget: self Label.
	self ssPushRegister: TempReg.
	
	(self fixupAt: nextPC) notAFixup ifTrue: [ branchReachedOnlyForCounterTrip := true ].
	
	^ 0
]

{ #category : #'bytecode generator support' }
SistaRegisterAllocatingCogit >> genJumpIf: boolean to: targetBytecodePC [
	"The heart of performance counting in Sista.  Conditional branches are 6 times less
	 frequent than sends and can provide basic block frequencies (send counters can't).
	 Each conditional has a 32-bit counter split into an upper 16 bits counting executions
	 and a lower half counting untaken executions of the branch.  Executing the branch
	 decrements the upper half, tripping if the count goes negative.  Not taking the branch
	 decrements the lower half.  N.B. We *do not* eliminate dead branches (true ifTrue:/true ifFalse:)
	 so that scanning for send and branch data is simplified and that branch data is correct."
	<inline: false>
	| ok counterAddress countTripped retry nextPC nextDescriptor desc eventualTarget reg |
	<var: #ok type: #'AbstractInstruction *'>
	<var: #desc type: #'CogSimStackEntry *'>
	<var: #retry type: #'AbstractInstruction *'>
	<var: #countTripped type: #'AbstractInstruction *'>
	<var: #nextDescriptor type: #'BytecodeDescriptor *'>

	"In optimized code we don't generate counters to improve performance"
	(coInterpreter isOptimizedMethod: methodObj) ifTrue:
		[^super genJumpIf: boolean to: targetBytecodePC].
	
	"If the branch is reached only for the counter trip trampoline 
	(typically, var1 == var2 ifTrue: falls through to the branch only for the trampoline)
	we generate a specific path to drastically reduce the number of machine instructions"
	branchReachedOnlyForCounterTrip ifTrue: 
		[branchReachedOnlyForCounterTrip := false.
		 ^self genCounterTripOnlyJumpIf: boolean to: targetBytecodePC].

	"We detect and: / or:, if found, we don't generate the counters to avoid pathological counter slow down"
	boolean = objectMemory falseObject ifTrue:
		[ nextPC := bytecodePC + (self generatorAt: byte0) numBytes.
		  nextDescriptor := self generatorForPC: nextPC.
		  nextDescriptor generator ==  #genPushConstantTrueBytecode ifTrue: [ ^ super genJumpIf: boolean to: targetBytecodePC ].
		  nextDescriptor := self generatorForPC: targetBytecodePC.
		  nextDescriptor generator == #genPushConstantFalseBytecode ifTrue: [ ^ super genJumpIf: boolean to: targetBytecodePC ]. ].

	extA := 0. "We ignore the noMustBeBoolean flag. It should not be present in methods with counters, and if it is we don't care."

	"We don't generate counters on branches on true/false, the basicblock usage can be inferred"
	desc := self ssTop.
	(self stackEntryIsBoolean: desc) ifTrue:
		[ ^ super genJumpIf: boolean to: targetBytecodePC ].

	eventualTarget := self eventualTargetOf: targetBytecodePC.

	self flag: 'Because of the restriction on x64 that absolute loads must target %rax, it would perhaps be a better choice to use TempReg (%rax) for the counter reg and SendNumArgsReg for the boolean.'.
	"try and use the top entry's register if any, but only if it can be destroyed."
	reg := (desc type ~= SSRegister
			or: [(self anyReferencesToRegister: desc register inAllButTopNItems: 0)
			or: [(desc register = ReceiverResultReg and: [self receiverIsInReceiverResultReg])]])
				ifTrue: [TempReg]
				ifFalse: [desc register].
	desc popToReg: reg.
	self ssPop: 1.

	"We need SendNumArgsReg because of the mustBeBooleanTrampoline"
	self ssAllocateRequiredReg: SendNumArgsReg.

	retry := self Label.
	self 
		genExecutionCountLogicInto: [ :cAddress :countTripBranch | 
			counterAddress := cAddress. 
			countTripped := countTripBranch ] 
		counterReg: SendNumArgsReg.
	counterIndex := counterIndex + 1.

	"Cunning trick by LPD.  If true and false are contiguous subtract the smaller.
	 Correct result is either 0 or the distance between them.  If result is not 0 or
	 their distance send mustBeBoolean."
	self assert: (objectMemory objectAfter: objectMemory falseObject) = objectMemory trueObject.
	self genSubConstant: boolean R: reg.
	self JumpZero: (self ensureFixupAt: eventualTarget).

	self genFallsThroughCountLogicCounterReg: SendNumArgsReg counterAddress: counterAddress.

	self CmpCq: (boolean = objectMemory falseObject
					ifTrue: [objectMemory trueObject - objectMemory falseObject]
					ifFalse: [objectMemory falseObject - objectMemory trueObject])
		R: reg.
	ok := self JumpZero: 0.
	self MoveCq: 0 R: SendNumArgsReg. "if counterReg is 0 this is a mustBeBoolean, not a counter trip."
	reg ~= TempReg ifTrue:
		[self MoveR: reg R: TempReg].
	countTripped jmpTarget: self Label.
	self copySimStackToScratch: simSpillBase.
	self ssFlushTo: simStackPtr.
	self genCallMustBeBooleanFor: boolean.
						
	"If we're in an image which hasn't got the Sista code loaded then the ceCounterTripped: trampoline
	 will return directly to machine code, returning the boolean.  So the code should jump back to the
	 retry point. The trampoline preserves register state when taking the ceCounterTripped: path."
	"Clément: For some reason if I write self annotateBytecode: (self Jump: retry) the annotation is not at the correct place."
	"Eliot: Annotations apply the the address following an instruction, and the annotation must be for the return address
	 of the call (since this is the address the run-time sees), so it must be on a label before the jump, not after the jump."
	self annotateBytecode: self Label.
	simSpillBase ~= scratchSpillBase ifTrue:
		[self assert: simSpillBase > scratchSpillBase.
		 self AddCq: simSpillBase - scratchSpillBase * objectMemory wordSize R: SPReg].
	self Jump: retry.

	ok jmpTarget: self Label.
	self restoreSimStackFromScratch.
	^0
]

{ #category : #'bytecode generators' }
SistaRegisterAllocatingCogit >> genSpecialSelectorComparison [
	"Override to count inlined branches if followed by a conditional branch.
	 We borrow the following conditional branch's counter and when about to
	 inline the comparison we decrement the counter (without writing it back)
	 and if it trips simply abort the inlining, falling back to the normal send which
	 will then continue to the conditional branch which will trip and enter the abort."
	| nextPC postBranchPC targetPC primDescriptor branchDescriptor
	  rcvrIsInt rcvrIsConst argIsIntConst argInt jumpNotSmallInts inlineCAB
	  counterAddress countTripped counterReg index rcvrReg argReg
	   branchToTarget needMergeToContinue needMergeToTarget |
	<var: #countTripped type: #'AbstractInstruction *'>
	<var: #primDescriptor type: #'BytecodeDescriptor *'>
	<var: #jumpNotSmallInts type: #'AbstractInstruction *'>
	<var: #branchDescriptor type: #'BytecodeDescriptor *'>

	(coInterpreter isOptimizedMethod: methodObj) ifTrue:
		[^self genSpecialSelectorComparisonWithoutCounters].

	primDescriptor := self generatorAt: byte0.
	argIsIntConst := self ssTop type = SSConstant
				 and: [objectMemory isIntegerObject: (argInt := self ssTop constant)].
	rcvrIsInt := ((rcvrIsConst := (self ssValue: 1) type = SSConstant)
				  and: [objectMemory isIntegerObject: (self ssValue: 1) constant])
				or: [self mclassIsSmallInteger and: [(self ssValue: 1) isSameEntryAs: self simSelf]].

	"short-cut the jump if operands are SmallInteger constants."
	(argIsIntConst and: [rcvrIsInt and: [rcvrIsConst]]) ifTrue:
		[^ self genStaticallyResolvedSpecialSelectorComparison].

	self extractMaybeBranchDescriptorInto: [ :descr :next :postBranch :target | 
		branchDescriptor := descr. nextPC := next. postBranchPC := postBranch. targetPC := target ].

	"Only interested in inlining if followed by a conditional branch."
	inlineCAB := branchDescriptor isBranchTrue or: [branchDescriptor isBranchFalse].
	"Further, only interested in inlining = and ~= if there's a SmallInteger constant involved.
	 The relational operators successfully statically predict SmallIntegers; the equality operators do not."
	(inlineCAB and: [primDescriptor opcode = JumpZero or: [primDescriptor opcode = JumpNonZero]]) ifTrue:
		[inlineCAB := argIsIntConst or: [rcvrIsInt]].
	inlineCAB ifFalse:
		[^self genSpecialSelectorSend].

	"In-line the comparison and the jump, but if the types are not SmallInteger then we will need
	 to do a send and fall through to the following conditional branch.  Since we're allocating values
	 in registers we would like to keep those registers live on the inlined path and reload registers
	 along the non-inlined send path.  The merge logic at the branch destinations handles this."
	argIsIntConst
		ifTrue:
			[rcvrReg := self allocateRegForStackEntryAt: 1.
			 (self ssValue: 1) popToReg: rcvrReg.
			 counterReg := self allocateRegNotConflictingWith: (self registerMaskFor: rcvrReg).
			 argReg := NoReg]
		ifFalse:
			[self allocateRegForStackTopTwoEntriesInto: [:rTop :rNext| argReg := rTop. rcvrReg := rNext].
			 self ssTop popToReg: argReg.
			 (self ssValue: 1) popToReg: rcvrReg.
			 counterReg := self allocateRegNotConflictingWith: (self registerMaskFor: rcvrReg and: argReg)].
	self ssPop: 2.
	jumpNotSmallInts := (rcvrIsInt and: [argIsIntConst]) ifFalse:
							[argIsIntConst
								ifTrue: [objectRepresentation genJumpNotSmallInteger: rcvrReg]
								ifFalse:
									[rcvrIsInt
										ifTrue: [objectRepresentation genJumpNotSmallInteger: argReg]
										ifFalse: [objectRepresentation genJumpNotSmallIntegersIn: rcvrReg and: argReg scratch: TempReg]]].

	self
		genExecutionCountLogicInto: [ :cAddress :countTripBranch | 
			counterAddress := cAddress. 
			countTripped := countTripBranch ] 
		counterReg: counterReg.

	argIsIntConst
		ifTrue: [self CmpCq: argInt R: rcvrReg]
		ifFalse: [self CmpR: argReg R: rcvrReg].
	"self printSimStack; printSimStack: (self fixupAt: postBranchPC) mergeSimStack; printSimStack: (self fixupAt: targetPC) mergeSimStack"
	"If there are merges to be performed on the forward branches we have to execute
	 the merge code only along the path requiring that merge, and exactly once."
	needMergeToTarget := self mergeRequiredForJumpTo: targetPC.
	needMergeToContinue := self mergeRequiredForJumpTo: postBranchPC.
	"Cmp is weird/backwards so invert the comparison."
	(needMergeToTarget and: [needMergeToContinue]) ifTrue:
		[branchToTarget := self genConditionalBranch: (branchDescriptor isBranchTrue
										ifTrue: [primDescriptor opcode]
										ifFalse: [self inverseBranchFor: primDescriptor opcode])
								operand: 0.
		 self Jump: (self ensureFixupAt: postBranchPC).
		 branchToTarget jmpTarget: self Label.
		 self Jump: (self ensureFixupAt: targetPC)].
	(needMergeToTarget and: [needMergeToContinue not]) ifTrue:
		[self genConditionalBranch: (branchDescriptor isBranchFalse
										ifTrue: [primDescriptor opcode]
										ifFalse: [self inverseBranchFor: primDescriptor opcode])
			operand: (self ensureFixupAt: postBranchPC) asUnsignedInteger.
		 self Jump: (self ensureFixupAt: targetPC)].
	(needMergeToTarget not and: [needMergeToContinue]) ifTrue:
		[self genConditionalBranch: (branchDescriptor isBranchTrue
										ifTrue: [primDescriptor opcode]
										ifFalse: [self inverseBranchFor: primDescriptor opcode])
			operand: (self ensureFixupAt: targetPC) asUnsignedInteger.
		 self Jump: (self ensureFixupAt: postBranchPC)].
	(needMergeToTarget or: [needMergeToContinue]) ifFalse:
		[self genConditionalBranch: (branchDescriptor isBranchTrue
										ifTrue: [primDescriptor opcode]
										ifFalse: [self inverseBranchFor: primDescriptor opcode])
			operand: (self ensureFixupAt: targetPC) asUnsignedInteger.
		 self Jump: (self ensureFixupAt: postBranchPC)].

	countTripped jmpTarget: self Label.
	jumpNotSmallInts ifNil:
		[self annotateInstructionForBytecode.
		 deadCode := true.
		 ^0].
	jumpNotSmallInts jmpTarget: countTripped getJmpTarget.
	
	self ssFlushTo: simStackPtr.
	rcvrReg = Arg0Reg
		ifTrue:
			[argReg = ReceiverResultReg
				ifTrue: [self SwapR: Arg0Reg R: Arg0Reg Scratch: TempReg. argReg := Arg0Reg]
				ifFalse: [self MoveR: rcvrReg R: ReceiverResultReg].
			 rcvrReg := ReceiverResultReg].
	argIsIntConst
		ifTrue: [self MoveCq: argInt R: Arg0Reg]
		ifFalse: [argReg ~= Arg0Reg ifTrue: [self MoveR: argReg R: Arg0Reg]].
	rcvrReg ~= ReceiverResultReg ifTrue: [self MoveR: rcvrReg R: ReceiverResultReg].
	index := byte0 - self firstSpecialSelectorBytecodeOffset.
	^self genMarshalledSend: index negated - 1 numArgs: 1 sendTable: ordinarySendTrampolines
]
