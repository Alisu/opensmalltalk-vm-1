Extension { #name : #PharoVMMaker }

{ #category : #'*VMMakerTheo' }
PharoVMMaker >> generateTheoVM [

	| interpreterClass optionsPairsArrayArg maker optionsPairsArray | 

	CurrentSmartSyntaxPluginCodeGenerator
		value: TheoSmartSyntaxPluginGenerator
		during: [
			VMMaker initializeForPharo.
			interpreterClass := TheoStackInterpreter.
			(interpreterClass bindingOf: #COGMTVM) value: false.

			maker := CrossPlatformVMMakerWithInterpreterParameter new.
			optionsPairsArrayArg := #(COGMTVM false
						ObjectMemory Spur64BitMemoryManager
						MULTIPLEBYTECODESETS true
						bytecodeTableInitializer initializeBytecodeTableForSqueakV3PlusClosuresSistaV1Hybrid).
			optionsPairsArray := (StackToRegisterMappingCogit isNil or: [optionsPairsArrayArg includes: #Cogit])
									ifTrue: [optionsPairsArrayArg]
									ifFalse: [optionsPairsArrayArg, { #Cogit. StackToRegisterMappingCogit name }].
			VMClass initializeForPlugins: optionsPairsArray.
			maker
				sourceDirectoryName: (VMMaker fullNameForPath: (self outputDirectory / 'generated'));
				platformRootDirectoryName: (VMMaker fullNameForPath: (self outputDirectory / 'generated'));
				options: optionsPairsArray;
				interpreterClass: interpreterClass.
			maker externalModules addAll: #( LargeIntegersPlugin LocalePlugin).
			
			[ maker
				doCleanupOldFiles;
				generatePlugins;
				generateInterpreterFile;	
				generateCogitFiles
			] valueSupplyingAnswer:true.]
]
