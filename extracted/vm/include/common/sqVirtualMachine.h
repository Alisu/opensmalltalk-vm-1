#ifndef _SqueakVM_H
#define _SqueakVM_H

/* We expect interp.h to define VM_PROXY_MAJOR & VM_PROXY_MINOR, and other
 * defines such as STACKVM, appropriately for the VM generated with it.
 */
#include "interp.h"

#if SPURVM
# define VM_VERSION "5.0"
#else
# define VM_VERSION "4.5"
#endif

#ifndef VM_PROXY_MAJOR
/* Increment the following number if you change the order of
   functions listed or if you remove functions */
# define VM_PROXY_MAJOR 1
#endif

#ifndef VM_PROXY_MINOR
/* Increment the following number if you add functions at the end */
# if SPURVM
#	define VM_PROXY_MINOR 13
# else
#	define VM_PROXY_MINOR 12
# endif
#endif

#include "sqMemoryAccess.h"

#if VM_PROXY_MINOR > 8
# define PrimNoErr 0
# define PrimErrGenericFailure 1
# define PrimErrBadReceiver 2
# define PrimErrBadArgument 3
# define PrimErrBadIndex 4
# define PrimErrBadNumArgs 5
# define PrimErrInappropriate 6
# define PrimErrUnsupported 7
# define PrimErrNoModification 8
# define PrimErrNoMemory 9
# define PrimErrNoCMemory 10
# define PrimErrNotFound 11
# define PrimErrBadMethod 12
# define PrimErrNamedInternal 13
# define PrimErrObjectMayMove 14

/* VMCallbackContext opaque type avoids all including setjmp.h & vmCallback.h */
typedef struct _VMCallbackContext *vmccp;
#endif

typedef sqInt (*CompilerHook)();

struct foo;

typedef struct VirtualMachine {


	struct foo* interpreterState;
	sqInt (*minorVersion)(void);
	sqInt (*majorVersion)(void);

	/* InterpreterProxy methodsFor: 'stack access' */

	sqInt  (*pop)(sqInt nItems, struct foo * self);
	sqInt  (*popthenPush)(sqInt nItems, sqInt oop, struct foo * self);
	sqInt  (*push)(sqInt object, struct foo * self);
	sqInt  (*pushBool)(sqInt trueOrFalse, struct foo * self);
	sqInt  (*pushFloat)(double f, struct foo * self);
	sqInt  (*pushInteger)(sqInt integerValue, struct foo * self);
	double (*stackFloatValue)(sqInt offset, struct foo * self);
	sqInt  (*stackIntegerValue)(sqInt offset, struct foo * self);
	sqInt  (*stackObjectValue)(sqInt offset, struct foo * self);
	sqInt  (*stackValue)(sqInt offset, struct foo * self);

	/* InterpreterProxy methodsFor: 'object access' */

	sqInt  (*argumentCountOf)(sqInt methodPointer, struct foo * self);
	void  *(*arrayValueOf)(sqInt oop, struct foo * self);
	sqInt  (*byteSizeOf)(sqInt oop, struct foo * self);
	void  *(*fetchArrayofObject)(sqInt fieldIndex, sqInt objectPointer, struct foo * self);
	sqInt  (*fetchClassOf)(sqInt oop, struct foo * self);
	double (*fetchFloatofObject)(sqInt fieldIndex, sqInt objectPointer, struct foo * self);
	sqInt  (*fetchIntegerofObject)(sqInt fieldIndex, sqInt objectPointer, struct foo * self);
	sqInt  (*fetchPointerofObject)(sqInt fieldIndex, sqInt oop, struct foo * self);
/*  sqInt  (*fetchWordofObject)(sqInt fieldFieldIndex, sqInt oop); *
 * has been rescinded as of VMMaker 3.8 and the 64bitclean VM      *
 * work. To support old plugins we keep a valid function in        *
 * the same location in the VM struct but rename it to             *
 * something utterly horrible to scare off the natives. A new      *
 * equivalent but 64 bit valid function is added as                *
 * 'fetchLong32OfObject'                                           */
	sqInt  (*obsoleteDontUseThisFetchWordofObject)(sqInt fieldFieldIndex, sqInt oop, struct foo * self);
	void  *(*firstFixedField)(sqInt oop, struct foo * self);
	void  *(*firstIndexableField)(sqInt oop, struct foo * self);
	sqInt  (*literalofMethod)(sqInt offset, sqInt methodPointer, struct foo * self);
	sqInt  (*literalCountOf)(sqInt methodPointer, struct foo * self);
	sqInt  (*methodArgumentCount)(struct foo * self);
	sqInt  (*methodPrimitiveIndex)(struct foo * self);
	sqInt  (*primitiveIndexOf)(sqInt methodPointer, struct foo * self);
	sqInt  (*sizeOfSTArrayFromCPrimitive)(void *cPtr, struct foo * self);
	sqInt  (*slotSizeOf)(sqInt oop, struct foo * self);
	sqInt  (*stObjectat)(sqInt array, sqInt fieldIndex, struct foo * self);
	sqInt  (*stObjectatput)(sqInt array, sqInt fieldIndex, sqInt value, struct foo * self);
	sqInt  (*stSizeOf)(sqInt oop, struct foo * self);
	sqInt  (*storeIntegerofObjectwithValue)(sqInt fieldIndex, sqInt oop, sqInt integer, struct foo * self);
	sqInt  (*storePointerofObjectwithValue)(sqInt fieldIndex, sqInt oop, sqInt valuePointer, struct foo * self);

	/* InterpreterProxy methodsFor: 'testing' */

	sqInt (*isKindOf)(sqInt oop, char *aString, struct foo * self);
	sqInt (*isMemberOf)(sqInt oop, char *aString, struct foo * self);
	sqInt (*isBytes)(sqInt oop, struct foo * self);
	sqInt (*isFloatObject)(sqInt oop, struct foo * self);
	sqInt (*isIndexable)(sqInt oop, struct foo * self);
	sqInt (*isIntegerObject)(sqInt oop, struct foo * self);
	sqInt (*isIntegerValue)(sqInt intValue, struct foo * self);
	sqInt (*isPointers)(sqInt oop, struct foo * self);
	sqInt (*isWeak)(sqInt oop, struct foo * self);
	sqInt (*isWords)(sqInt oop, struct foo * self);
	sqInt (*isWordsOrBytes)(sqInt oop, struct foo * self);

	/* InterpreterProxy methodsFor: 'converting' */

	sqInt  (*booleanValueOf)(sqInt obj, struct foo * self);
	sqInt  (*checkedIntegerValueOf)(sqInt intOop, struct foo * self);
	sqInt  (*floatObjectOf)(double aFloat, struct foo * self);
	double (*floatValueOf)(sqInt oop, struct foo * self);
	sqInt  (*integerObjectOf)(sqInt value, struct foo * self);
	sqInt  (*integerValueOf)(sqInt oop, struct foo * self);
	sqInt  (*positive32BitIntegerFor)(unsigned int integerValue, struct foo * self);
	usqInt (*positive32BitValueOf)(sqInt oop, struct foo * self);

	/* InterpreterProxy methodsFor: 'special objects' */

	sqInt (*characterTable)(struct foo * self);
	sqInt (*displayObject)(struct foo * self);
	sqInt (*falseObject)(struct foo * self);
	sqInt (*nilObject)(struct foo * self);
	sqInt (*trueObject)(struct foo * self);

	/* InterpreterProxy methodsFor: 'special classes' */

	sqInt (*classArray)(struct foo * self);
	sqInt (*classBitmap)(struct foo * self);
	sqInt (*classByteArray)(struct foo * self);
	sqInt (*classCharacter)(struct foo * self);
	sqInt (*classFloat)(struct foo * self);
	sqInt (*classLargePositiveInteger)(struct foo * self);
	sqInt (*classPoint)(struct foo * self);
	sqInt (*classSemaphore)(struct foo * self);
	sqInt (*classSmallInteger)(struct foo * self);
	sqInt (*classString)(struct foo * self);

	/* InterpreterProxy methodsFor: 'instance creation' */

	sqInt (*clone)(sqInt oop, struct foo * self);
	sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size, struct foo * self);
	sqInt (*makePointwithxValueyValue)(sqInt xValue, sqInt yValue, struct foo * self);
	sqInt (*popRemappableOop)(struct foo * self);
	sqInt (*pushRemappableOop)(sqInt oop, struct foo * self);

	/* InterpreterProxy methodsFor: 'other' */

	sqInt (*becomewith)(sqInt array1, sqInt array2, struct foo * self);
	sqInt (*byteSwapped)(sqInt w, struct foo * self);
	sqInt (*failed)(struct foo * self);
	sqInt (*fullDisplayUpdate)(struct foo * self);
	void (*fullGC)(struct foo * self);
	void (*incrementalGC)(struct foo * self);
	sqInt (*primitiveFail)(struct foo * self);
	sqInt (*showDisplayBitsLeftTopRightBottom)(sqInt aForm, sqInt l, sqInt t, sqInt r, sqInt b, struct foo * self);
	sqInt (*signalSemaphoreWithIndex)(sqInt semaIndex);
	sqInt (*success)(sqInt aBoolean, struct foo * self);
	sqInt (*superclassOf)(sqInt classPointer, struct foo * self);

# if VM_PROXY_MINOR > 13
	/* Reuse these now that Cog provides a production JIT. */
	sqInt (*statNumGCs)(struct foo * self);
	sqInt (*stringForCString)(char *nullTerminatedCString, struct foo * self);
# else
	/* InterpreterProxy methodsFor: 'compiler' */

	CompilerHook *(*compilerHookVector)(void);
	sqInt         (*setCompilerInitialized)(sqInt initFlag);
# endif

#if VM_PROXY_MINOR > 1

	/* InterpreterProxy methodsFor: 'BitBlt support' */

	sqInt (*loadBitBltFrom)(sqInt bbOop, struct foo * self);
	sqInt (*copyBits)(struct foo * self);
	sqInt (*copyBitsFromtoat)(sqInt leftX, sqInt rightX, sqInt yValue, struct foo * self);

#endif

#if VM_PROXY_MINOR > 2

	sqInt (*classLargeNegativeInteger)(struct foo * self);
	sqInt (*signed32BitIntegerFor)(sqInt integerValue, struct foo * self);
	int   (*signed32BitValueOf)(sqInt oop, struct foo * self);
	sqInt (*includesBehaviorThatOf)(sqInt aClass, sqInt aSuperClass, struct foo * self);
	sqInt (*primitiveMethod)(struct foo * self);

	/* InterpreterProxy methodsFor: 'FFI support' */

	sqInt (*classExternalAddress)(struct foo * self);
	sqInt (*classExternalData)(struct foo * self);
	sqInt (*classExternalFunction)(struct foo * self);
	sqInt (*classExternalLibrary)(struct foo * self);
	sqInt (*classExternalStructure)(struct foo * self);
	void *(*ioLoadModuleOfLength)(sqInt modIndex, sqInt modLength);
	void *(*ioLoadSymbolOfLengthFromModule)(sqInt fnIndex, sqInt fnLength, sqInt handle);
	sqInt (*isInMemory)(sqInt address, struct foo * self);

#endif

#if VM_PROXY_MINOR > 3

	void *(*ioLoadFunctionFrom)(char *fnName, char *modName, struct foo * self);
	sqInt (*ioMicroMSecs)(void);

#endif

#if VM_PROXY_MINOR > 4

#  if !defined(sqLong)
#   if _MSC_VER
#     define sqLong __int64
#     define usqLong unsigned __int64
#   else
#     define sqLong long long
#     define usqLong unsigned long long
#   endif
#  endif

	sqInt  (*positive64BitIntegerFor)(usqLong integerValue, struct foo * self);
	usqLong(*positive64BitValueOf)(sqInt oop, struct foo * self);
	sqInt  (*signed64BitIntegerFor)(sqLong integerValue, struct foo * self);
	sqLong (*signed64BitValueOf)(sqInt oop, struct foo * self);

#endif

#if VM_PROXY_MINOR > 5
	sqInt (*isArray)(sqInt oop, struct foo * self);
	void (*forceInterruptCheck)(struct foo * self);
#endif

#if VM_PROXY_MINOR > 6
	sqInt  (*fetchLong32ofObject)(sqInt fieldFieldIndex, sqInt oop, struct foo * self);
	sqInt  (*getThisSessionID)(struct foo * self);
	sqInt  (*ioFilenamefromStringofLengthresolveAliases)(char* aCharBuffer, char* filenameIndex, sqInt filenameLength, sqInt resolveFlag, struct foo * self);
	sqInt  (*vmEndianness)(struct foo * self);	
#endif

#if VM_PROXY_MINOR > 7
  /* New methods for proxy version 1.8 */

  /* callbackEnter: Re-enter the interpreter loop for a callback.
     Arguments:
       callbackID: Pointer to a location receiving the callback ID
                   used in callbackLeave
     Returns: True if successful, false otherwise */
  sqInt (*callbackEnter)(sqInt *callbackID, struct foo * self);

  /* callbackLeave: Leave the interpreter from a previous callback
     Arguments:
       callbackID: The ID of the callback received from callbackEnter()
     Returns: True if succcessful, false otherwise. */
  sqInt (*callbackLeave)(sqInt  callbackID, struct foo * self);

  /* addGCRoot: Add a variable location to the garbage collector.
     The contents of the variable location will be updated accordingly.
     Arguments:
       varLoc: Pointer to the variable location
     Returns: True if successful, false otherwise. */
  sqInt (*addGCRoot)(sqInt *varLoc, struct foo * self);

  /* removeGCRoot: Remove a variable location from the garbage collector.
     Arguments:
       varLoc: Pointer to the variable location
     Returns: True if successful, false otherwise.
  */
  sqInt (*removeGCRoot)(sqInt *varLoc, struct foo * self);
#endif

#if VM_PROXY_MINOR > 8
	/* See interp.h and above for standard error codes. */
	sqInt  (*primitiveFailFor)(sqInt code, struct foo * self);
	void (*(*setInterruptCheckChain)(void (*aFunction)(void)))();
	sqInt  (*classAlien)(struct foo * self);
	sqInt  (*classUnsafeAlien)(struct foo * self);
	sqInt  (*sendInvokeCallbackStackRegistersJmpbuf)(sqInt thunkPtrAsInt, sqInt stackPtrAsInt, sqInt regsPtrAsInt, sqInt jmpBufPtrAsInt, struct foo * self);
	sqInt  (*reestablishContextPriorToCallback)(sqInt callbackContext, struct foo * self);
	sqInt *(*getStackPointer)(struct foo * self);
	sqInt  (*isOopImmutable)(sqInt oop, struct foo * self);
	sqInt  (*isOopMutable)(sqInt oop, struct foo * self);
#endif

#if VM_PROXY_MINOR > 9
# if VM_PROXY_MINOR > 13 /* OS Errors available in primitives; easy return forms */
  sqInt  (*methodReturnBool)(sqInt, struct foo * self);
  sqInt  (*methodReturnFloat)(double, struct foo * self);
  sqInt  (*methodReturnInteger)(sqInt, struct foo * self);
  sqInt  (*methodReturnString)(char *, struct foo * self);
#	define returnSelf() methodReturnValue(0)
# else
  sqInt  (*methodArg)  (sqInt index); /* These ended up never being used. */
  sqInt  (*objectArg)  (sqInt index);
  sqInt  (*integerArg) (sqInt index);
  double (*floatArg)   (sqInt index);
# endif
  sqInt  (*methodReturnValue) (sqInt oop, struct foo * self);
  sqInt  (*topRemappableOop)  (struct foo * self);
#endif

#if VM_PROXY_MINOR > 10
# if !SPURVM
#	define DisownVMLockOutFullGC 1
# endif
  sqInt	(*disownVM)(sqInt flags, struct foo * self);
  sqInt	(*ownVM)   (sqInt threadIdAndFlags, struct foo * self);
  void  (*addHighPriorityTickee)(void (*ticker)(void), unsigned periodms);
  void  (*addSynchronousTickee)(void (*ticker)(void), unsigned periodms, unsigned roundms);
  volatile usqLong (*utcMicroseconds)(void);
  void (*tenuringIncrementalGC)(struct foo * self);
  sqInt (*isYoung) (sqInt anOop, struct foo * self);
  sqInt (*isKindOfClass)(sqInt oop, sqInt aClass, struct foo * self);
  sqInt (*primitiveErrorTable)(struct foo * self);
  sqInt (*primitiveFailureCode)(struct foo * self);
  sqInt (*instanceSizeOf)(sqInt aClass, struct foo * self);
#endif

#if VM_PROXY_MINOR > 11
/* VMCallbackContext opaque type avoids all including setjmp.h & vmCallback.h */
  sqInt (*sendInvokeCallbackContext)(vmccp, struct foo * self);
  sqInt (*returnAsThroughCallbackContext)(int, vmccp, sqInt, struct foo * self);
  sqIntptr_t  (*signedMachineIntegerValueOf)(sqInt, struct foo * self);
  sqIntptr_t  (*stackSignedMachineIntegerValue)(sqInt, struct foo * self);
  usqIntptr_t (*positiveMachineIntegerValueOf)(sqInt, struct foo * self);
  usqIntptr_t (*stackPositiveMachineIntegerValue)(sqInt, struct foo * self);
  sqInt	 (*getInterruptPending)(struct foo * self);
  char  *(*cStringOrNullFor)(sqInt, struct foo * self);
  void  *(*startOfAlienData)(sqInt, struct foo * self);
  usqInt (*sizeOfAlienData)(sqInt, struct foo * self);
  sqInt  (*signalNoResume)(sqInt, struct foo * self);
#endif

#if VM_PROXY_MINOR > 12 /* Spur */
  sqInt (*isImmediate)(sqInt objOop, struct foo * self);
  sqInt (*characterObjectOf)(int charCode, struct foo * self);
  sqInt (*characterValueOf)(sqInt objOop, struct foo * self);
  sqInt (*isCharacterObject)(sqInt objOop, struct foo * self);
  sqInt (*isCharacterValue)(int charCode, struct foo * self);
  sqInt (*isPinned)(sqInt objOop, struct foo * self);
  sqInt (*pinObject)(sqInt objOop, struct foo * self);
  sqInt (*unpinObject)(sqInt objOop, struct foo * self);
#endif

#if VM_PROXY_MINOR > 13 /* OS Errors available in primitives; easy return forms (see above) */
  sqInt  (*primitiveFailForOSError)(sqLong osErrorCode, struct foo * self);
  sqInt  (*methodReturnReceiver)(struct foo * self);
  sqInt  (*primitiveFailForFFIExceptionat)(usqLong exceptionCode, usqInt pc, struct foo * self);
#endif

#if VM_PROXY_MINOR > 14 /* SmartSyntaxPlugin validation rewrite support */
  sqInt  (*isBooleanObject)(sqInt oop, struct foo * self);
  sqInt  (*isPositiveMachineIntegerObject)(sqInt, struct foo * self);
#endif

  sqInt (*ptEnterInterpreterFromCallback)(vmccp);
  sqInt (*ptExitInterpreterToCallback)(vmccp);
  sqInt (*ptDisableCogIt)(void*);

  sqInt (*isNonImmediate)(sqInt oop, struct foo * self);

} VirtualMachine;

#endif /* _SqueakVM_H */
