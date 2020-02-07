/****************************************************************************
*   PROJECT: Common include
*   FILE:    sq.h
*   CONTENT: 
*
*   AUTHOR:  
*   ADDRESS: 
*   EMAIL:   
*   RCSID:   $Id: sq.h 1283 2005-12-31 00:51:12Z rowledge $
*
*/

#ifndef _SQ_H
#define _SQ_H

#include "sqConfig.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "sqMemoryAccess.h"
#include "sqVirtualMachine.h"

#define true	1
#define false	0
#define null	0  /* using "null" because nil is predefined in Think C */

#if !defined(IMAGE_DIALECT_NAME)
# if NewspeakVM
#	define IMAGE_DIALECT_NAME "Newspeak"
#	define DEFAULT_IMAGE_NAME "newspeak.image"
#	define IMAGE_ENV_NAME "NEWSPEAK_IMAGE"
# elif PharoVM
#	define IMAGE_DIALECT_NAME "Pharo"
#	define DEFAULT_IMAGE_NAME "Pharo.image"
#	define IMAGE_ENV_NAME "PHARO_IMAGE"
# else
#	define IMAGE_DIALECT_NAME "Squeak"
#	define DEFAULT_IMAGE_NAME "squeak.image"
#	define IMAGE_ENV_NAME "SQUEAK_IMAGE"
# endif
#endif

/* Pluggable primitives macros. */

/* Note: All pluggable primitives are defined as
	EXPORT(int) somePrimitive(void)
   All non-static variables in the VM and plugins are declared as
	VM_EXPORT type var
   If the platform requires special declaration modifiers, the EXPORT and
   VM_EXPORT macros can be redefined.
*/
#define EXPORT(returnType) returnType
#define VM_EXPORT
#define VM_FUNCTION_EXPORT(returnType) returnType

/* Image save/restore macros. */

/* Note: The image file save and restore code uses these macros; they
   can be redefined in sqPlatformSpecific.h if desired. These default
   versions are defined in terms of the ANSI Standard C libraries.
*/
#define sqImageFile					   FILE *
#define sqImageFileClose(f)                  		   fclose(f)
#define sqImageFileOpen(fileName, mode)      		   fopen(fileName, mode)
#define sqImageFilePosition(f)               		   ftell(f)
#define sqImageFileRead(ptr, sz, count, f)   		   fread(ptr, sz, count, f)
#define sqImageFileSeek(f, pos)              		   fseek(f, pos, SEEK_SET)
#define sqImageFileSeekEnd(f, pos)              	   fseek(f, pos, SEEK_END)
#define sqImageFileWrite(ptr, sz, count, f)  		   fwrite(ptr, sz, count, f)
#define sqImageFileStartLocation(fileRef, fileName, size)  0

/* Platform-dependent macros for handling object memory. */

/* Note: The grow/shrink macros assume that the object memory can be extended
   continuously at its prior end. The garbage collector cannot deal with
   'holes' in the object memory so the support code needs to reserve the
   virtual maximum of pages that can be allocated beforehand. The amount of
   'extra' memory should describe the amount of memory that can be allocated
   from the OS (including swap space if the flag is set to true) and must not
   exceed the prior reserved memory.
   In other words: don't you dare to report more free space then you can
   actually allocate.
   The default implementation assumes a fixed size memory allocated at startup.
*/
#define sqAllocateMemory(minHeapSize, desiredHeapSize)  malloc(desiredHeapSize)
#define sqGrowMemoryBy(oldLimit, delta)			oldLimit
#define sqShrinkMemoryBy(oldLimit, delta)		oldLimit
#define sqMemoryExtraBytesLeft(includingSwap)		0

#if SPURVM
/* Allocate a region of memory of al least sz bytes, at or above minAddr.
 * If the attempt fails, answer null.  If the attempt succeeds, answer the
 * start of the region and assign its size through asp.
 */
extern void *sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto(sqInt sz, void *minAddr, sqInt *asp, sqInt self);
extern void sqDeallocateMemorySegmentAtOfSize(void *addr, sqInt sz, sqInt self);
#endif /* SPURVM */
/* Platform-dependent memory size adjustment macro. */

/* Note: This macro can be redefined to allows platforms with a
   fixed application memory partition (notably, the Macintosh)
   to reserve extra C heap memory for special applications that need
   it (e.g., for a 3D graphics library). Since most platforms can
   extend their application memory partition at run time if needed,
   this macro is defined as a noop here and redefined if necessary
   in sqPlatformSpecific.h.
*/

#define reserveExtraCHeapBytes(origHeapSize, bytesToReserve) origHeapSize

/* Platform-dependent millisecond clock macros. */

/* Note: The Squeak VM uses two different clock functions for timing, and
   the Cog VMs provide a third.

   The primary one, ioMSecs(), is used to implement Delay and Time
   millisecondClockValue. The resolution of this clock
   determines the resolution of these basic timing functions. For
   doing real-time control of music and MIDI, a clock with resolution
   down to one millisecond is preferred, but a coarser clock (say,
   1/60th second) can be used in a pinch.

   The function ioMicroMSecs() is used only to collect timing statistics
   for the garbage collector and other VM facilities. (The function
   name is meant to suggest that the function is based on a clock
   with microsecond accuracy, even though the times it returns are
   in units of milliseconds.) This clock must have enough precision to
   provide accurate timings, and normally isn't called frequently
   enough to slow down the VM. Thus, it can use a more expensive clock
   than ioMSecs(). This function is listed in the sqVirtualMachine plugin
   support mechanism and thus needs to be a real function, even if a macro is
   use to point to it.

   There was a third form that used to be used for quickly timing primitives in
   order to try to keep millisecond delays up to date. That is no longer used.

   The wall clock is answered by ioSeconds, which answers the number of seconds
   since the start of the 20th century (12pm Dec 31, 1900).

   The Cog VMs depend on a heartbeat to cause the VM to check for interrupts at
   regular intervals (of the order of ever millisecond).  The heartbeat on these
   VMs is responsible for updating a 64-bit microsecond clock with the number
   of microseconds since the start of the 20th century (12pm Dec 31, 1900)
   available via ioUTCMicroseconds and ioLocalMicroseconds.  When exact time is
   required we provide ioUTCMicrosecondsNow & ioLocalMicrosecondsNow that update
   the clock to return the time right now, rather than of the last heartbeat.
*/

long ioMSecs(sqInt self);
sqInt ioMicroMSecs(sqInt self);

/* duplicate the generated definition in the interpreter.  If they differ the
 * compiler will complain and catch it for us.  We use 0x1FFFFFFF instead of
 * 0x3FFFFFFF so that twice the maximum clock value remains in the positive
 * SmallInteger range.  This assumes 31 bit SmallIntegers; 0x3FFFFFFF is
 * SmallInteger maxVal.
 */
#define MillisecondClockMask 0x1FFFFFFF

#if STACKVM
extern void forceInterruptCheckFromHeartbeat(sqInt self);
unsigned volatile long long  ioUTCMicrosecondsNow(sqInt self);
unsigned volatile long long  ioUTCMicroseconds(sqInt self);
unsigned volatile long long  ioLocalMicrosecondsNow(sqInt self);
unsigned volatile long long  ioLocalMicroseconds(sqInt self);
unsigned          long long  ioUTCStartMicroseconds(sqInt self);
sqInt	ioLocalSecondsOffset(sqInt self);
void	ioUpdateVMTimezone(sqInt self);
void	ioSynchronousCheckForEvents(sqInt self);
void	checkHighPriorityTickees(usqLong, sqInt self);
# if ITIMER_HEARTBEAT		/* Hack; allow heartbeat to avoid */
extern int numAsyncTickees; /* prodHighPriorityThread unless necessary */
# endif						/* see platforms/unix/vm/sqUnixHeartbeat.c */
void	ioGetClockLogSizeUsecsIdxMsecsIdx(sqInt*,void**,sqInt*,void**,sqInt*, sqInt self);
void	addIdleUsecs(sqInt, sqInt self);
#endif

/* this function should return the value of the high performance
   counter if there is such a thing on this platform (otherwise return 0) */
sqLong ioHighResClock(sqInt self);

/* New filename converting function; used by the interpreterProxy function 
  ioFilenamefromStringofLengthresolveAliases. Most platforms can ignore the
  resolveAlias boolean - it seems to only be of use by OSX but is crucial there.
*/
sqInt sqGetFilenameFromString(char * aCharBuffer, char * aFilenameString, sqInt filenameLength, sqInt aBoolean);

/* Macro to provide default null behaviour for ftruncate - a non-ansi call
   used in FilePlugin.
   Override in sqPlatformSpecific.h for each platform that implements a
   file truncate, or consider replacing the
   ../Cross/plugins/FilePlugin/sqFilePluginBasicPrims.c
   file with a platform specific version as Win32 and RISC OS do. 
*/
#define sqFTruncate(filenum, fileoffset) true

/* Macros to support Mac browser plugin without ugly code in Interpreter. */

#define insufficientMemorySpecifiedError()	error("Insufficient memory for this image")
#define insufficientMemoryAvailableError()	error("Failed to allocate memory for the heap")
#define unableToReadImageError()		error("Read failed or premature end of image file")
#define browserPluginReturnIfNeeded()
#define browserPluginInitialiseIfNeeded(arg)

/* Platform-specific header file may redefine earlier definitions and macros. */

#include "sqPlatformSpecific.h"

/* Interpreter entry points. */

/* Disable Intel compiler inlining of error which is used for breakpoints */
#ifdef __INTEL_COMPILER 
#   pragma auto_inline(off)
#endif
extern void error(char *s, sqInt self);
#ifdef __INTEL_COMPILER 
#   pragma auto_inline(on)
#endif
sqInt checkedByteAt(sqInt byteAddress, sqInt self);
sqInt checkedByteAtput(sqInt byteAddress, sqInt byte, sqInt self);
sqInt checkedLongAt(sqInt byteAddress, sqInt self);
sqInt checkedLongAtput(sqInt byteAddress, sqInt a32BitInteger, sqInt self);
sqInt interpret();
sqInt primitiveFail();
sqInt signalSemaphoreWithIndex(sqInt semaIndex, sqInt self);
sqInt doSignalExternalSemaphores(sqInt, sqInt self);
sqInt success(sqInt);

/* Display, mouse, keyboard, time. */

extern VM_EXPORT void *displayBits;
extern VM_EXPORT int displayWidth, displayHeight, displayDepth;
extern VM_EXPORT sqInt sendWheelEvents;

sqInt ioBeep(sqInt self);
sqInt ioExit(sqInt self);
sqInt ioExitWithErrorCode(int);
sqInt crashInThisOrAnotherThread(sqInt flags, sqInt self);
sqInt fullDisplayUpdate(sqInt self);
void  ioNoteDisplayChangedwidthheightdepth(void *bitsOrHandle, int w, int h, int d, sqInt self);
sqInt ioForceDisplayUpdate(sqInt self);
sqInt ioFormPrint(sqInt bitsAddr, sqInt width, sqInt height, sqInt depth,
		  double hScale, double vScale, sqInt landscapeFlag, sqInt self);
sqInt ioSetFullScreen(sqInt fullScreen, sqInt self);
double ioScreenScaleFactor(sqInt self);
sqInt ioScreenSize(sqInt self);
sqInt ioScreenDepth(sqInt self);
sqInt ioSeconds(sqInt self);
sqInt ioSecondsNow(sqInt self);
sqInt ioSetCursor(sqInt cursorBitsIndex, sqInt offsetX, sqInt offsetY, sqInt self);
sqInt ioSetCursorWithMask(sqInt cursorBitsIndex, sqInt cursorMaskIndex, sqInt offsetX, sqInt offsetY, sqInt self);
sqInt ioShowDisplay(sqInt dispBitsIndex, sqInt width, sqInt height, sqInt depth,
		    sqInt affectedL, sqInt affectedR, sqInt affectedT, sqInt affectedB, sqInt self);
sqInt ioHasDisplayDepth(sqInt depth, sqInt self);
sqInt ioSetDisplayMode(sqInt width, sqInt height, sqInt depth, sqInt fullscreenFlag, sqInt self);
char* ioGetLogDirectory(sqInt self);
sqInt ioSetLogDirectoryOfSize(void* lblIndex, sqInt sz, sqInt self);
char* ioGetWindowLabel(sqInt self);
sqInt ioSetWindowLabelOfSize(void *lblIndex, sqInt sz, sqInt self);
sqInt ioGetWindowWidth(sqInt self);
sqInt ioGetWindowHeight(sqInt self);
sqInt ioSetWindowWidthHeight(sqInt w, sqInt h, sqInt self);
sqInt ioIsWindowObscured(sqInt self);

sqInt ioRelinquishProcessorForMicroseconds(sqInt microSeconds, sqInt self);
#if STACKVM || NewspeakVM
/* thread subsystem support for e.g. sqExternalSemaphores.c */
void ioInitThreads(sqInt self);

/* Management of the external semaphore table (max size set at startup) */
#if !defined(INITIAL_EXT_SEM_TABLE_SIZE)
# define INITIAL_EXT_SEM_TABLE_SIZE 256
#endif
int   ioGetMaxExtSemTableSize(sqInt self);
void  ioSetMaxExtSemTableSize(int, sqInt self);

/* these are used both in the STACKVM & the COGMTVM */
# if !defined(ioCurrentOSThread)
sqOSThread ioCurrentOSThread(sqInt self);
# endif
# if !defined(ioOSThreadsEqual)
int  ioOSThreadsEqual(sqOSThread,sqOSThread, sqInt self);
# endif
# if !COGMTVM
extern sqOSThread ioVMThread;
# define getVMOSThread() ioVMThread
# endif
#endif /* STACKVM || NewspeakVM */

#if STACKVM
/* Event polling via periodic heartbeat thread. */
int returnGIVNumberForHearbeat(sqInt self);
void setIOHeartbeatGIVToUse(int, sqInt self);
void  ioInitHeartbeat(sqInt self);
int   ioHeartbeatMilliseconds(sqInt self);
void  ioSetHeartbeatMilliseconds(int, sqInt self);
unsigned long ioHeartbeatFrequency(int, sqInt self);
#endif /* STACKVM */

#if COGMTVM
#define THRLOGSZ 256
extern int thrlogidx;
extern char *thrlog[];

/* Debug logging that defers printing.  Use like printf, e.g.
 * TLOG("tryLockVMToIndex vmOwner = %d\n", vmOwner, sqInt self);
 * Requires #include "sqAtomicOps.h"
 * N.B. The following still isn't safe.  If enough log entries are made by other
 * threads after myindex is obtained but before asprintf completes we can get
 * two threads using the same entry.  But this is good enough for now.
 */
#define THRLOG(...) do { int myidx, nextidx; \
	do { myidx = thrlogidx; \
		 nextidx = (myidx+1)&(THRLOGSZ-1, sqInt self); \
	} while (!sqCompareAndSwap(thrlogidx,myidx,nextidx), sqInt self); \
	if (thrlog[myidx]) free(thrlog[myidx], sqInt self); \
	asprintf(thrlog + myidx, __VA_ARGS__, sqInt self); \
} while (0)

extern sqOSThread getVMOSThread(sqInt self);
/* Please read the comment for CogThreadManager in the VMMaker package for
 * documentation of this API.  N.B. code is included from sqPlatformSpecific.h
 * before the code here.  e.g.
 * # include <pthread.h>
 * # define sqOSThread pthread_t
 * # define sqOSSemaphore pthread_cond_t
 * # define ioOSThreadsEqual(a,b) pthread_equal(a,b)
 */
# if !defined(ioGetThreadLocalThreadIndex)
long ioGetThreadLocalThreadIndex(sqInt self);
# endif
# if !defined(ioSetThreadLocalThreadIndex)
void ioSetThreadLocalThreadIndex(long, sqInt self);
# endif

# if !defined(ioNewOSThread)
int  ioNewOSThread(void (*func)(void *), void *, sqInt self);
# endif
# if !defined(ioExitOSThread)
void ioExitOSThread(sqOSThread thread, sqInt self);
# endif
# if !defined(ioReleaseOSThreadState)
void ioReleaseOSThreadState(sqOSThread thread, sqInt self);
# endif
# if !defined(ioOSThreadIsAlive)
int  ioOSThreadIsAlive(sqOSThread, sqInt self);
# endif
int  ioNewOSSemaphore(sqOSSemaphore *, sqInt self);
# if !defined(ioDestroyOSSemaphore)
void ioDestroyOSSemaphore(sqOSSemaphore *, sqInt self);
# endif
void ioSignalOSSemaphore(sqOSSemaphore *, sqInt self);
void ioWaitOnOSSemaphore(sqOSSemaphore *, sqInt self);
int  ioNumProcessors(sqInt self);
# if !defined(ioTransferTimeslice)
void ioTransferTimeslice(sqInt self);
# endif
#endif /* COGMTVM */

/* Profiling. */
void  ioProfileStatus(sqInt *running, void **exestartpc, void **exelimitpc,
					  void **vmhst, long *nvmhbin, void **eahst, long *neahbin, sqInt self);
void  ioControlProfile(int on, void **vhp, long *nvb, void **ehp, long *neb, sqInt self);
long  ioControlNewProfile(int on, unsigned long buffer_size, sqInt self);
void  ioNewProfileStatus(sqInt *running, long *buffersize, sqInt self);
long  ioNewProfileSamplesInto(void *sampleBuffer, sqInt self);
void  ioClearProfile(sqInt self);

/* Power management. */

sqInt ioDisablePowerManager(sqInt disableIfNonZero, sqInt self);

/* User input recording I:
   In general, either set of input function can be supported,
   depending on the platform. This (first) set is state based
   and should be supported even on platforms that make use
   of the newer event driven API to support older images 
   without event support.
*/

sqInt ioGetButtonState(sqInt self);
sqInt ioGetKeystroke(sqInt self);
sqInt ioMousePoint(sqInt self);
sqInt ioPeekKeystroke(sqInt self);
/* Note: In an event driven architecture, ioProcessEvents is obsolete.
   It can be implemented as a no-op since the image will check for
   events in regular intervals. */
sqInt ioProcessEvents(sqInt self);


/* User input recording II:
   The following functions and definition can be used on
   platform supporting events directly.
*/

/* Event types. */
#define EventTypeNone		0
#define EventTypeMouse		1
#define EventTypeKeyboard	2
#define EventTypeDragDropFiles	3
#define EventTypeMenu		4
#define EventTypeWindow		5
#define EventTypeComplex	6 /* For iPhone apps */
#define EventTypeMouseWheel	7 /* optional; see sendWheelEvents & vm param 48 */
#define EventTypePlugin		8 /* Terf: events from ActiveX Controls */


/* Keypress state for keyboard events. */
#define EventKeyChar	0
#define EventKeyDown	1
#define EventKeyUp	2

/* Button definitions. */
#define RedButtonBit	4
#define YellowButtonBit	2
#define BlueButtonBit	1

/* Modifier definitions. */
#define ShiftKeyBit	1
#define CtrlKeyBit	2
#define OptionKeyBit	4
#define CommandKeyBit	8

/* generic input event */
typedef struct sqInputEvent
{
  sqIntptr_t type;				/* type of event; either one of EventTypeXXX */
  usqIntptr_t timeStamp;	/* time stamp */
  /* the interpretation of the following fields depend on the type of the event */
  sqIntptr_t unused1;
  sqIntptr_t unused2;
  sqIntptr_t unused3;
  sqIntptr_t unused4;
  sqIntptr_t unused5;
  sqIntptr_t windowIndex;		/* SmallInteger used in image to identify a host window structure */
} sqInputEvent;

/* mouse input event */
typedef struct sqMouseEvent
{
  sqIntptr_t type;				/* EventTypeMouse */
  usqIntptr_t timeStamp;	/* time stamp */
  sqIntptr_t x;					/* mouse position x */
  sqIntptr_t y;					/* mouse position y */
  sqIntptr_t buttons;				/* combination of xxxButtonBit */
  sqIntptr_t modifiers;			/* combination of xxxKeyBit */
  sqIntptr_t nrClicks;			/* number of clicks in button downs - was reserved1 */
  sqIntptr_t windowIndex;			/* host window structure */
} sqMouseEvent;

/* keyboard input event */
typedef struct sqKeyboardEvent
{
  sqIntptr_t type;				/* EventTypeKeyboard */
  usqIntptr_t timeStamp;	/* time stamp */
  sqIntptr_t charCode;			/* character code in Mac Roman encoding */
  sqIntptr_t pressCode;			/* press code; any of EventKeyXXX */
  sqIntptr_t modifiers;			/* combination of xxxKeyBit */
  sqIntptr_t utf32Code;			/* UTF-32 unicode value */
  sqIntptr_t reserved1;			/* reserved for future use */
  sqIntptr_t windowIndex;			/* host window structure */
} sqKeyboardEvent;

/* drop files event */
typedef struct sqDragDropFilesEvent
{
  sqIntptr_t type;				/* EventTypeDropFiles */
  usqIntptr_t timeStamp;	/* time stamp */
  sqIntptr_t dragType;			/* one of DragXXX (see below) */
  sqIntptr_t x;					/* mouse position x */
  sqIntptr_t y;					/* mouse position y */
  sqIntptr_t modifiers;			/* combination of xxxKeyBit */
  sqIntptr_t numFiles;			/* number of files in transaction */
  sqIntptr_t windowIndex;			/* host window structure */
} sqDragDropFilesEvent;

#define SQDragEnter	1 /* drag operation from OS entered Squeak window	 */
#define SQDragMove	2 /* drag operation from OS moved within Squeak window */
#define SQDragLeave	3 /* drag operation from OS left Squeak window	 */
#define SQDragDrop	4 /* drag operation dropped contents onto Squeak.      */
#define SQDragRequest	5 /* data request from other app. */

/* menu event */
typedef struct sqMenuEvent
{
  sqIntptr_t type;				/* type of event; EventTypeMenu */
  usqIntptr_t timeStamp;	/* time stamp */
  /* the interpretation of the following fields depend on the type  of the event */
  sqIntptr_t menu;				/* platform-dependent to indicate which menu was picked */
  sqIntptr_t menuItem;			/* given a menu having 1 to N items this maps to the menu item number */
  sqIntptr_t reserved1;			/* reserved for future use */
  sqIntptr_t reserved2;			/* reserved for future use */
  sqIntptr_t reserved3;			/* reserved for future use */
  sqIntptr_t windowIndex;			/* host window structure */
} sqMenuEvent;

/* window action event */
typedef struct sqWindowEvent
{
  sqIntptr_t type;				/* type of event;  EventTypeWindow */
  usqIntptr_t timeStamp;	/* time stamp */
  /* the interpretation of the following fields depend on the type  of the event */
  sqIntptr_t action;				/* one of WindowEventXXX (see below) */
  sqIntptr_t value1;				/* used for rectangle edges */
  sqIntptr_t value2;				/* used for rectangle edges */
  sqIntptr_t value3;				/* used for rectangle edges */
  sqIntptr_t value4;				/* used for rectangle edges */
  sqIntptr_t windowIndex;			/* host window structure */
} sqWindowEvent;

#define WindowEventMetricChange	1 /* size or position of window changed - value1-4 are left/top/right/bottom values */
#define WindowEventClose	2 /* window close icon pressed */
#define WindowEventIconise	3 /* window iconised or hidden etc */
#define WindowEventActivated	4 /* window made active - some platforms only - do not rely upon this */
#define WindowEventPaint	5 /* window area (in value1-4) needs updating. Some platforms do not need to send this, do not rely on it in image */
#define WindowEventStinks	6 /* this window stinks (just to see if people read this stuff) */

typedef struct sqComplexEvent
{
  sqIntptr_t type;				/* type of event;  EventTypeComplex */
  usqIntptr_t timeStamp;	/* time stamp */
  /* the interpretation of the following fields depend on the type  of the event */
  sqIntptr_t action;		        /* one of ComplexEventXXX (see below) */
  sqIntptr_t objectPointer;		/* used to point to object */
  sqIntptr_t unused1;
  sqIntptr_t unused2;
  sqIntptr_t unused3;
  sqIntptr_t windowIndex;			/* host window structure */
} sqComplexEvent;

#define ComplexEventTypeTouchsDown	1
#define ComplexEventTypeTouchsUp	2
#define ComplexEventTypeTouchsMoved	3
#define ComplexEventTypeTouchsStationary 4
#define ComplexEventTypeTouchsCancelled	5
#define ComplexEventTypeAccelerationData	6
#define ComplexEventTypeLocationData	7
#define ComplexEventTypeApplicationData	8


/* Set an asynchronous input semaphore index for events. */
sqInt ioSetInputSemaphore(sqInt semaIndex, sqInt self);
/* Retrieve the next input event from the OS. */
sqInt ioGetNextEvent(sqInputEvent *evt, sqInt self);

/* Log the event procesing chain. */
#if defined(DEBUG_EVENT_CHAIN)
# define LogEventChain(parms) fprintf parms
# define dbgEvtChF stderr
#else
# define LogEventChain(parms) 0
#endif

/* Image file and VM path names. */
extern char imageName[];
char *getImageName();
sqInt imageNameGetLength(sqInt sqImageNameIndex, sqInt length);
sqInt imageNamePutLength(sqInt sqImageNameIndex, sqInt length);
sqInt imageNameSize();
sqInt vmPathSize();
sqInt vmPathGetLength(sqInt sqVMPathIndex, sqInt length);

/* The following was not exported by sq.h but we need it
   since if we don't have CURRENT_VERSION around anymore
   and we may want to check for the image version we need it */
sqInt readableFormat(sqInt imageVersion, sqInt self);

/* Image security traps. */
sqInt ioCanRenameImage(sqInt self);
sqInt ioCanWriteImage(sqInt self);
sqInt ioDisableImageWrite(sqInt self);

/* Save/restore. */
/* Read the image from the given file starting at the given image offset */
size_t readImageFromFileHeapSizeStartingAt(sqImageFile f, usqInt desiredHeapSize, squeakFileOffsetType imageOffset, sqInt self);

/* Clipboard (cut/copy/paste). */
sqInt clipboardSize(sqInt self);
sqInt clipboardReadIntoAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex, sqInt self);
sqInt clipboardWriteFromAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex, sqInt self);


/* Interpreter entry points needed by compiled primitives. */
void *arrayValueOf(sqInt arrayOop, sqInt self);
sqInt checkedIntegerValueOf(sqInt intOop, sqInt self);
void *fetchArrayofObject(sqInt fieldIndex, sqInt objectPointer, sqInt self);
double fetchFloatofObject(sqInt fieldIndex, sqInt objectPointer, sqInt self);
sqInt fetchIntegerofObject(sqInt fieldIndex, sqInt objectPointer, sqInt self);
double floatValueOf(sqInt floatOop);
sqInt pop(sqInt nItems, sqInt self);
sqInt pushInteger(sqInt integerValue, sqInt self);
sqInt sizeOfSTArrayFromCPrimitive(void *cPtr, sqInt self);
sqInt storeIntegerofObjectwithValue(sqInt fieldIndex, sqInt objectPointer, sqInt integerValue, sqInt self);

/* System attributes. */
sqInt attributeSize(sqInt indexNumber);
sqInt getAttributeIntoLength(sqInt indexNumber, sqInt byteArrayIndex, sqInt length);

/*** Pluggable primitive support. ***/

/* NOTE: The following functions are those implemented by sqNamedPrims.c */
void *ioLoadExternalFunctionOfLengthFromModuleOfLength
		(sqInt functionNameIndex, sqInt functionNameLength,
		 sqInt moduleNameIndex, sqInt moduleNameLength, sqInt self);
#if SPURVM
void *ioLoadExternalFunctionOfLengthFromModuleOfLengthAccessorDepthInto
	(sqInt functionNameIndex, sqInt functionNameLength,
	 sqInt moduleNameIndex,   sqInt moduleNameLength, sqInt *accessorDepthPtr, sqInt self);
#endif
sqInt  ioUnloadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength, sqInt self);
void  *ioLoadFunctionFrom(char *functionName, char *pluginName, sqInt self);
sqInt  ioShutdownAllModules(sqInt self);
sqInt  ioUnloadModule(char *moduleName, sqInt self);
sqInt  ioUnloadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength, sqInt self);
char  *ioListBuiltinModule(sqInt moduleIndex, sqInt self);
char  *ioListLoadedModule(sqInt moduleIndex, sqInt self);
/* The next two for the FFI, also implemented in sqNamedPrims.c. */
void  *ioLoadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength, sqInt self);
void  *ioLoadSymbolOfLengthFromModule(sqInt functionNameIndex, sqInt functionNameLength, void *moduleHandle, sqInt self);

/* The next three functions must be implemented by sqXYZExternalPrims.c */
/* ioLoadModule:
	Load a module from disk.
	WARNING: this always loads a *new* module. Don't even attempt to find
	a loaded one.
	WARNING: never primitiveFail() within, just return 0
*/
void *ioLoadModule(char *pluginName, sqInt self);

/* ioFindExternalFunctionIn[AccessorDepthInto]:
	Find the function with the given name in the moduleHandle.
	WARNING: never primitiveFail() within, just return 0.
	Note in Spur takes an extra parameter which is defaulted to 0.
*/
#if SPURVM
void *ioFindExternalFunctionInAccessorDepthInto(char *lookupName, void *moduleHandle, sqInt *accessorDepthPtr, sqInt self);
# define ioFindExternalFunctionIn(ln,mh) ioFindExternalFunctionInAccessorDepthInto(ln,mh,0)
#else
void *ioFindExternalFunctionIn(char *lookupName, void *moduleHandle, sqInt self);
#endif

/* ioFreeModule:
	Free the module with the associated handle.
	WARNING: never primitiveFail() within, just return 0.
*/
sqInt ioFreeModule(void *moduleHandle, sqInt self);

/* The Squeak version from which this interpreter was generated. */
extern const char *interpreterVersion;

#endif /* _SQ_H */
