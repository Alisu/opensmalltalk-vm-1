/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.2493 uuid: d7437cc5-75c7-4a43-af6b-0f85bf0cebe6
   from
	SoundPlugin VMMaker.oscog-eem.2493 uuid: d7437cc5-75c7-4a43-af6b-0f85bf0cebe6
 */
static char __buildInfo[] = "SoundPlugin VMMaker.oscog-eem.2493 uuid: d7437cc5-75c7-4a43-af6b-0f85bf0cebe6 " __DATE__ ;



#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
#endif

#include "SoundPlugin.h"
#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadArgument 3


/*** Function Prototypes ***/
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) initialiseModule(void);
EXPORT(sqInt) primitiveGetDefaultSoundPlayer(void);
EXPORT(sqInt) primitiveGetDefaultSoundRecorder(void);
EXPORT(sqInt) primitiveGetNumberOfSoundPlayerDevices(void);
EXPORT(sqInt) primitiveGetNumberOfSoundRecorderDevices(void);
EXPORT(sqInt) primitiveGetSoundPlayerDeviceName(void);
EXPORT(sqInt) primitiveGetSoundRecorderDeviceName(void);
EXPORT(sqInt) primitiveSetDefaultSoundPlayer(void);
EXPORT(sqInt) primitiveSetDefaultSoundRecorder(void);
EXPORT(sqInt) primitiveSoundAvailableSpace(void);
EXPORT(sqInt) primitiveSoundEnableAEC(void);
EXPORT(sqInt) primitiveSoundGetRecordingSampleRate(void);
EXPORT(sqInt) primitiveSoundGetRecordLevel(void);
EXPORT(sqInt) primitiveSoundGetVolume(void);
EXPORT(sqInt) primitiveSoundInsertSamples(void);
EXPORT(sqInt) primitiveSoundPlaySamples(void);
EXPORT(sqInt) primitiveSoundPlaySilence(void);
EXPORT(sqInt) primitiveSoundRecordSamples(void);
EXPORT(sqInt) primitiveSoundSetLeftVolume(void);
EXPORT(sqInt) primitiveSoundSetRecordLevel(void);
EXPORT(sqInt) primitiveSoundStart(void);
EXPORT(sqInt) primitiveSoundStartRecording(void);
EXPORT(sqInt) primitiveSoundStartWithSemaphore(void);
EXPORT(sqInt) primitiveSoundStop(void);
EXPORT(sqInt) primitiveSoundStopRecording(void);
EXPORT(sqInt) primitiveSoundSupportsAEC(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine *anInterpreter);
EXPORT(sqInt) shutdownModule(void);
static sqInt sqAssert(sqInt aBool);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*booleanValueOf)(sqInt obj);
static sqInt (*byteSizeOf)(sqInt oop);
static sqInt (*classArray)(void);
static sqInt (*classString)(void);
static sqInt (*failed)(void);
static sqInt (*falseObject)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*floatObjectOf)(double aFloat);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*isBooleanObject)(sqInt oop);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*isFloatObject)(sqInt oop);
static sqInt (*isIntegerObject)(sqInt objectPointer);
static sqInt (*isWords)(sqInt oop);
static sqInt (*methodArgumentCount)(void);
static sqInt (*nilObject)(void);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*popRemappableOop)(void);
static sqInt (*positive32BitIntegerFor)(unsigned int integerValue);
static usqInt (*positive32BitValueOf)(sqInt oop);
static sqInt (*primitiveFail)(void);
static sqInt (*primitiveFailFor)(sqInt reasonCode);
static sqInt (*pushRemappableOop)(sqInt oop);
static sqInt (*signed32BitIntegerFor)(sqInt integerValue);
static sqInt (*slotSizeOf)(sqInt oop);
static double (*stackFloatValue)(sqInt offset);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*storePointerofObjectwithValue)(sqInt index, sqInt oop, sqInt valuePointer);
static sqInt (*success)(sqInt aBoolean);
static sqInt (*trueObject)(void);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt booleanValueOf(sqInt obj);
extern sqInt byteSizeOf(sqInt oop);
extern sqInt classArray(void);
extern sqInt classString(void);
extern sqInt failed(void);
extern sqInt falseObject(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt floatObjectOf(double aFloat);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
#if VM_PROXY_MAJOR > 1 || (VM_PROXY_MAJOR == 1 && VM_PROXY_MINOR >= 15)
extern sqInt isBooleanObject(sqInt oop);
#else
# define isBooleanObject(oop) 0
#endif
extern sqInt isBytes(sqInt oop);
extern sqInt isFloatObject(sqInt oop);
#if !defined(isIntegerObject)
extern sqInt isIntegerObject(sqInt objectPointer);
#endif
extern sqInt isWords(sqInt oop);
extern sqInt methodArgumentCount(void);
extern sqInt nilObject(void);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt popRemappableOop(void);
extern sqInt positive32BitIntegerFor(unsigned int integerValue);
extern usqInt positive32BitValueOf(sqInt oop);
extern sqInt primitiveFail(void);
extern sqInt primitiveFailFor(sqInt reasonCode);
extern sqInt pushRemappableOop(sqInt oop);
extern sqInt signed32BitIntegerFor(sqInt integerValue);
extern sqInt slotSizeOf(sqInt oop);
extern double stackFloatValue(sqInt offset);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt storePointerofObjectwithValue(sqInt index, sqInt oop, sqInt valuePointer);
extern sqInt success(sqInt aBoolean);
extern sqInt trueObject(void);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"SoundPlugin VMMaker.oscog-eem.2493 (i)"
#else
	"SoundPlugin VMMaker.oscog-eem.2493 (e)"
#endif
;



/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

	/* SoundPlugin>>#initialiseModule */
EXPORT(sqInt)
initialiseModule(void)
{
	return soundInit();
}


/*	Answer a String with the operating system name of the default output
	device, or nil
 */
/*	no arguments */

	/* SoundPlugin>>#primitiveGetDefaultSoundPlayer */
EXPORT(sqInt)
primitiveGetDefaultSoundPlayer(void)
{
	char *cDeviceName;
	sqInt newString;
	char *newStringPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 0)) {
		return primitiveFail();
	}
	cDeviceName = getDefaultSoundPlayer();
	if (cDeviceName == 0) {
		return popthenPush(1, nilObject());
	}
	sz = strlen(cDeviceName);
	newString = instantiateClassindexableSize(classString(), sz);
	newStringPtr = firstIndexableField(newString);
	strncpy(newStringPtr, cDeviceName, sz);
	return popthenPush(1, newString);
}


/*	Answer a String with the operating system name of the default input
	device, or nil
 */
/*	no arguments */

	/* SoundPlugin>>#primitiveGetDefaultSoundRecorder */
EXPORT(sqInt)
primitiveGetDefaultSoundRecorder(void)
{
	char *cDeviceName;
	sqInt newString;
	char *newStringPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 0)) {
		return primitiveFail();
	}
	cDeviceName = getDefaultSoundRecorder();
	if (cDeviceName == 0) {
		return popthenPush(1, nilObject());
	}
	sz = strlen(cDeviceName);
	newString = instantiateClassindexableSize(classString(), sz);
	newStringPtr = firstIndexableField(newString);
	strncpy(newStringPtr, cDeviceName, sz);
	return popthenPush(1, newString);
}


/*	arguments: name(type, stack offset)
	dialString(String, 0) */
/*	answers an Integer */

	/* SoundPlugin>>#primitiveGetNumberOfSoundPlayerDevices */
EXPORT(sqInt)
primitiveGetNumberOfSoundPlayerDevices(void)
{
	sqInt result;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 0)) {
		return primitiveFail();
	}

	/* answer it */
	result = getNumberOfSoundPlayerDevices();
	result = signed32BitIntegerFor(result);
	return popthenPush(1, result);
}


/*	arguments: name(type, stack offset)
	dialString(String, 0) */
/*	answers an Integer */

	/* SoundPlugin>>#primitiveGetNumberOfSoundRecorderDevices */
EXPORT(sqInt)
primitiveGetNumberOfSoundRecorderDevices(void)
{
	sqInt result;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 0)) {
		return primitiveFail();
	}

	/* answer it */
	result = getNumberOfSoundRecorderDevices();
	result = signed32BitIntegerFor(result);
	return popthenPush(1, result);
}


/*	arguments: name(type, stack offset)
	deviceNumber(Integer, 0) */
/*	answers a string or nil */

	/* SoundPlugin>>#primitiveGetSoundPlayerDeviceName */
EXPORT(sqInt)
primitiveGetSoundPlayerDeviceName(void)
{
	char *cDeviceName;
	sqInt deviceNumber;
	sqInt newString;
	char *newStringPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 1)) {
		return primitiveFail();
	}
	deviceNumber = positive32BitValueOf(stackValue(0));
	if (failed()) {
		return null;
	}
	cDeviceName = getSoundPlayerDeviceName(deviceNumber - 1);
	if (cDeviceName == 0) {
		return popthenPush(2, nilObject());
	}
	sz = strlen(cDeviceName);
	newString = instantiateClassindexableSize(classString(), sz);
	newStringPtr = firstIndexableField(newString);
	strncpy(newStringPtr, cDeviceName, sz);
	return popthenPush(2, newString);
}


/*	arguments: name(type, stack offset)
	deviceNumber(Integer, 0) */
/*	answers a string or nil */

	/* SoundPlugin>>#primitiveGetSoundRecorderDeviceName */
EXPORT(sqInt)
primitiveGetSoundRecorderDeviceName(void)
{
	char *cDeviceName;
	sqInt deviceNumber;
	sqInt newString;
	char *newStringPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 1)) {
		return primitiveFail();
	}
	deviceNumber = positive32BitValueOf(stackValue(0));
	if (failed()) {
		return null;
	}
	cDeviceName = getSoundRecorderDeviceName(deviceNumber - 1);
	if (cDeviceName == 0) {
		return popthenPush(2, nilObject());
	}
	sz = strlen(cDeviceName);
	newString = instantiateClassindexableSize(classString(), sz);
	newStringPtr = firstIndexableField(newString);
	strncpy(newStringPtr, cDeviceName, sz);
	return popthenPush(2, newString);
}


/*	Tell the operating system to use the specified device name as the output
	device for sound.
 */
/*	arg at top of stack is the String */

	/* SoundPlugin>>#primitiveSetDefaultSoundPlayer */
EXPORT(sqInt)
primitiveSetDefaultSoundPlayer(void)
{
	char deviceName[257];
	sqInt obj;
	char *srcPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 1)) {
		return primitiveFail();
	}
	obj = stackValue(0);
	if (!(isBytes(obj))) {
		return primitiveFail();
	}
	if (!(((sz = byteSizeOf(obj))) <= 256)) {
		return primitiveFail();
	}
	srcPtr = firstIndexableField(obj);
	strncpy(deviceName, srcPtr, sz);
	deviceName[sz] = 0;
	setDefaultSoundPlayer(deviceName);
	if (!(failed())) {

		/* pop arg, leave receiver */
		pop(1);
	}
	return 0;
}


/*	Tell the operating system to use the specified device name as the input
	device for sound.
 */
/*	arg at top of stack is the String */

	/* SoundPlugin>>#primitiveSetDefaultSoundRecorder */
EXPORT(sqInt)
primitiveSetDefaultSoundRecorder(void)
{
	char deviceName[257];
	sqInt obj;
	char *srcPtr;
	sqInt sz;


	/* Parse arguments */
	if (!((methodArgumentCount()) == 1)) {
		return primitiveFail();
	}
	obj = stackValue(0);
	if (!(isBytes(obj))) {
		return primitiveFail();
	}
	if (!(((sz = byteSizeOf(obj))) <= 256)) {
		return primitiveFail();
	}
	srcPtr = firstIndexableField(obj);
	strncpy(deviceName, srcPtr, sz);
	deviceName[sz] = 0;
	setDefaultSoundRecorder(deviceName);
	if (!(failed())) {

		/* pop arg, leave receiver */
		pop(1);
	}
	return 0;
}


/*	Returns the number of bytes of available sound output buffer space. This
	should be (frames*4) if the device is in stereo mode, or (frames*2)
	otherwise 
 */

	/* SoundPlugin>>#primitiveSoundAvailableSpace */
EXPORT(sqInt)
primitiveSoundAvailableSpace(void)
{
	sqInt frames;
	sqInt _return_value;


	/* -1 if sound output not started */
	frames = snd_AvailableSpace();
	success(frames >= 0);
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(frames);
		if (!(failed())) {
			popthenPush(1, _return_value);
		}
	}
	return null;
}


/*	Enable or disable acoustic echo-cancellation (AEC). trueOrFalse should be
	0 for false, and 1 for true. */

	/* SoundPlugin>>#primitiveSoundEnableAEC: */
EXPORT(sqInt)
primitiveSoundEnableAEC(void)
{
	sqInt result;
	sqInt trueOrFalse;

	if (!(isIntegerObject(stackValue(0)))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	trueOrFalse = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	if (!(failed())) {
		result = snd_EnableAEC(trueOrFalse);
		if (!(result == 0)) {
			primitiveFailFor(result);
		}
	}
	if (!(failed())) {
		pop(1);
	}
	return null;
}


/*	Return a float representing the actual sampling rate during recording.
	Fail if not currently recording.
 */

	/* SoundPlugin>>#primitiveSoundGetRecordingSampleRate */
EXPORT(sqInt)
primitiveSoundGetRecordingSampleRate(void)
{
	double rate;
	sqInt _return_value;


	/* fail if not recording */
	rate = snd_GetRecordingSampleRate();
	if (!(failed())) {
		_return_value = floatObjectOf(rate);
		if (!(failed())) {
			popthenPush(1, _return_value);
		}
	}
	return null;
}


/*	Get the sound input recording level in the range 0-1000. */

	/* SoundPlugin>>#primitiveSoundGetRecordLevel */
EXPORT(sqInt)
primitiveSoundGetRecordLevel(void)
{
	int level;
	sqInt _return_value;

	level = snd_GetRecordLevel();
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(level);
		if (!(failed())) {
			popthenPush(1, _return_value);
		}
	}
	return null;
}


/*	Get the sound input recording level. */

	/* SoundPlugin>>#primitiveSoundGetVolume */
EXPORT(sqInt)
primitiveSoundGetVolume(void)
{
	double left;
	sqInt results;
	double right;

	left = 0;
	right = 0;
	snd_Volume((double *) &left,(double *) &right);
	pushRemappableOop(floatObjectOf(right));
	pushRemappableOop(floatObjectOf(left));
	results = instantiateClassindexableSize(classArray(), 2);
	storePointerofObjectwithValue(0, results, popRemappableOop());
	storePointerofObjectwithValue(1, results, popRemappableOop());
	return null;
}


/*	Insert a buffer's worth of sound samples into the currently playing 
	buffer. Used to make a sound start playing as quickly as possible. The 
	new sound is mixed with the previously buffered sampled. */
/*	Details: Unlike primitiveSoundPlaySamples, this primitive always starts 
	with the first sample the given sample buffer. Its third argument 
	specifies the number of samples past the estimated sound output buffer 
	position the inserted sound should start. If successful, it returns the 
	number of samples inserted. */

	/* SoundPlugin>>#primitiveSoundInsertSamples:from:leadTime: */
EXPORT(sqInt)
primitiveSoundInsertSamples(void)
{
	unsigned *buf;
	sqInt frameCount;
	sqInt framesPlayed;
	sqInt leadTime;
	sqInt _return_value;

	framesPlayed = 0;
	if (!((isIntegerObject(stackValue(2)))
		 && ((isWords(stackValue(1)))
		 && (isIntegerObject(stackValue(0)))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	frameCount = stackIntegerValue(2);
	buf = ((unsigned *) (firstIndexableField(stackValue(1))));
	leadTime = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	success(frameCount <= (slotSizeOf(((sqInt)(sqIntptr_t)(buf) - BaseHeaderSize))));
	if (!(failed())) {
		framesPlayed = snd_InsertSamplesFromLeadTime(frameCount, (void *)buf, leadTime);
		success(framesPlayed >= 0);
	}
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(framesPlayed);
		if (!(failed())) {
			popthenPush(4, _return_value);
		}
	}
	return null;
}


/*	Output a buffer's worth of sound samples. */

	/* SoundPlugin>>#primitiveSoundPlaySamples:from:startingAt: */
EXPORT(sqInt)
primitiveSoundPlaySamples(void)
{
	unsigned *buf;
	sqInt frameCount;
	sqInt framesPlayed;
	sqInt startIndex;
	sqInt _return_value;

	framesPlayed = 0;
	if (!((isIntegerObject(stackValue(2)))
		 && ((isWords(stackValue(1)))
		 && (isIntegerObject(stackValue(0)))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	frameCount = stackIntegerValue(2);
	buf = ((unsigned *) (firstIndexableField(stackValue(1))));
	startIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	success((startIndex >= 1)
	 && (((startIndex + frameCount) - 1) <= (slotSizeOf(((sqInt)(sqIntptr_t)(buf) - BaseHeaderSize)))));
	if (!(failed())) {
		framesPlayed = snd_PlaySamplesFromAtLength(frameCount, (void *)buf, startIndex - 1);
		success(framesPlayed >= 0);
	}
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(framesPlayed);
		if (!(failed())) {
			popthenPush(4, _return_value);
		}
	}
	return null;
}


/*	Output a buffer's worth of silence. Returns the number of sample frames
	played. 
 */

	/* SoundPlugin>>#primitiveSoundPlaySilence */
EXPORT(sqInt)
primitiveSoundPlaySilence(void)
{
	sqInt framesPlayed;
	sqInt _return_value;


	/* -1 if sound output not started */
	framesPlayed = snd_PlaySilence();
	success(framesPlayed >= 0);
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(framesPlayed);
		if (!(failed())) {
			popthenPush(1, _return_value);
		}
	}
	return null;
}


/*	Record a buffer's worth of 16-bit sound samples. */

	/* SoundPlugin>>#primitiveSoundRecordSamplesInto:startingAt: */
EXPORT(sqInt)
primitiveSoundRecordSamples(void)
{
	unsigned *buf;
	sqInt bufLen;
	char *bufPtr;
	sqInt bufSizeInBytes;
	sqInt byteOffset;
	sqInt samplesRecorded;
	sqInt startWordIndex;
	sqInt _return_value;

	bufSizeInBytes = 0;
	samplesRecorded = 0;
	if (!((isWords(stackValue(1)))
		 && (isIntegerObject(stackValue(0))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	buf = ((unsigned *) (firstIndexableField(stackValue(1))));
	startWordIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	if (!(failed())) {
		bufSizeInBytes = (slotSizeOf(((sqInt)(sqIntptr_t)(buf) - BaseHeaderSize))) * 4;
		success((startWordIndex >= 1)
		 && (((startWordIndex - 1) * 2) < bufSizeInBytes));
	}
	if (!(failed())) {
		byteOffset = (startWordIndex - 1) * 2;
		bufPtr = (((char*) buf)) + byteOffset;
		bufLen = bufSizeInBytes - byteOffset;
		samplesRecorded = snd_RecordSamplesIntoAtLength(bufPtr, 0, bufLen);
	}
	if (!(failed())) {
		_return_value = positive32BitIntegerFor(samplesRecorded);
		if (!(failed())) {
			popthenPush(3, _return_value);
		}
	}
	return null;
}


/*	Set the sound input recording level. */

	/* SoundPlugin>>#primitiveSoundSetLeftVolume:rightVolume: */
EXPORT(sqInt)
primitiveSoundSetLeftVolume(void)
{
	double aLeftVolume;
	double aRightVolume;

	if (!((isFloatObject(stackValue(1)))
		 && (isFloatObject(stackValue(0))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	aLeftVolume = stackFloatValue(1);
	aRightVolume = stackFloatValue(0);
	if (failed()) {
		return null;
	}
	if (!(failed())) {
		snd_SetVolume(aLeftVolume,aRightVolume);
	}
	if (!(failed())) {
		pop(2);
	}
	return null;
}


/*	Set the sound input recording level. */

	/* SoundPlugin>>#primitiveSoundSetRecordLevel: */
EXPORT(sqInt)
primitiveSoundSetRecordLevel(void)
{
	sqInt level;

	if (!(isIntegerObject(stackValue(0)))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	level = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	if (!(failed())) {
		snd_SetRecordLevel(level);
	}
	if (!(failed())) {
		pop(1);
	}
	return null;
}


/*	Start the double-buffered sound output with the given buffer size, sample
	rate, and stereo flag.
 */

	/* SoundPlugin>>#primitiveSoundStartBufferSize:rate:stereo: */
EXPORT(sqInt)
primitiveSoundStart(void)
{
	sqInt bufFrames;
	sqInt samplesPerSec;
	sqInt stereoFlag;

	if (!((isIntegerObject(stackValue(2)))
		 && ((isIntegerObject(stackValue(1)))
		 && (isBooleanObject(stackValue(0)))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	bufFrames = stackIntegerValue(2);
	samplesPerSec = stackIntegerValue(1);
	stereoFlag = booleanValueOf(stackValue(0));
	if (failed()) {
		return null;
	}
	success(snd_Start(bufFrames, samplesPerSec, stereoFlag, 0));
	if (!(failed())) {
		pop(3);
	}
	return null;
}


/*	Start recording sound with the given parameters. */

	/* SoundPlugin>>#primitiveSoundStartRecordingDesiredSampleRate:stereo:semaIndex: */
EXPORT(sqInt)
primitiveSoundStartRecording(void)
{
	sqInt desiredSamplesPerSec;
	sqInt semaIndex;
	sqInt stereoFlag;

	if (!((isIntegerObject(stackValue(2)))
		 && ((isBooleanObject(stackValue(1)))
		 && (isIntegerObject(stackValue(0)))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	desiredSamplesPerSec = stackIntegerValue(2);
	stereoFlag = booleanValueOf(stackValue(1));
	semaIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	snd_StartRecording(desiredSamplesPerSec, stereoFlag, semaIndex);
	if (!(failed())) {
		pop(3);
	}
	return null;
}


/*	Start the double-buffered sound output with the given buffer size, sample
	rate, stereo flag, and semaphore index.
 */

	/* SoundPlugin>>#primitiveSoundStartBufferSize:rate:stereo:semaIndex: */
EXPORT(sqInt)
primitiveSoundStartWithSemaphore(void)
{
	sqInt bufFrames;
	sqInt samplesPerSec;
	sqInt semaIndex;
	sqInt stereoFlag;

	if (!((isIntegerObject(stackValue(3)))
		 && ((isIntegerObject(stackValue(2)))
		 && ((isBooleanObject(stackValue(1)))
		 && (isIntegerObject(stackValue(0))))))) {
		primitiveFailFor(PrimErrBadArgument);
		return null;
	}
	bufFrames = stackIntegerValue(3);
	samplesPerSec = stackIntegerValue(2);
	stereoFlag = booleanValueOf(stackValue(1));
	semaIndex = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	success(snd_Start(bufFrames, samplesPerSec, stereoFlag, semaIndex));
	if (!(failed())) {
		pop(4);
	}
	return null;
}


/*	Stop double-buffered sound output. */

	/* SoundPlugin>>#primitiveSoundStop */
EXPORT(sqInt)
primitiveSoundStop(void)
{
	snd_Stop();
	return null;
}


/*	Stop recording sound. */

	/* SoundPlugin>>#primitiveSoundStopRecording */
EXPORT(sqInt)
primitiveSoundStopRecording(void)
{
	snd_StopRecording();
	return null;
}


/*	Answer true if the OS/hardware supports echo-cancellation, and false
	otherwise. 
 */

	/* SoundPlugin>>#primitiveSoundSupportsAEC */
EXPORT(sqInt)
primitiveSoundSupportsAEC(void)
{
	sqInt result;

	if (!(failed())) {
		result = snd_SupportsAEC();
		if (result == 0) {
			popthenPush(1, falseObject());
			return null;
		}
		else {
			popthenPush(1, trueObject());
			return null;
		}
	}
	return null;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine *anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		booleanValueOf = interpreterProxy->booleanValueOf;
		byteSizeOf = interpreterProxy->byteSizeOf;
		classArray = interpreterProxy->classArray;
		classString = interpreterProxy->classString;
		failed = interpreterProxy->failed;
		falseObject = interpreterProxy->falseObject;
		firstIndexableField = interpreterProxy->firstIndexableField;
		floatObjectOf = interpreterProxy->floatObjectOf;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
#if VM_PROXY_MAJOR > 1 || (VM_PROXY_MAJOR == 1 && VM_PROXY_MINOR >= 15)
		isBooleanObject = interpreterProxy->isBooleanObject;
#else
#if !defined(isBooleanObject)
		isBooleanObject = 0;
#endif
#endif
		isBytes = interpreterProxy->isBytes;
		isFloatObject = interpreterProxy->isFloatObject;
		isIntegerObject = interpreterProxy->isIntegerObject;
		isWords = interpreterProxy->isWords;
		methodArgumentCount = interpreterProxy->methodArgumentCount;
		nilObject = interpreterProxy->nilObject;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		popRemappableOop = interpreterProxy->popRemappableOop;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		positive32BitValueOf = interpreterProxy->positive32BitValueOf;
		primitiveFail = interpreterProxy->primitiveFail;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
		pushRemappableOop = interpreterProxy->pushRemappableOop;
		signed32BitIntegerFor = interpreterProxy->signed32BitIntegerFor;
		slotSizeOf = interpreterProxy->slotSizeOf;
		stackFloatValue = interpreterProxy->stackFloatValue;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
		storePointerofObjectwithValue = interpreterProxy->storePointerofObjectwithValue;
		success = interpreterProxy->success;
		trueObject = interpreterProxy->trueObject;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}

	/* SoundPlugin>>#shutdownModule */
EXPORT(sqInt)
shutdownModule(void)
{
	return soundShutdown();
}

	/* SmartSyntaxInterpreterPlugin>>#sqAssert: */
static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
	return aBool;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "SoundPlugin";
void* SoundPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "initialiseModule", (void*)initialiseModule},
	{(void*)_m, "primitiveGetDefaultSoundPlayer\000\377", (void*)primitiveGetDefaultSoundPlayer},
	{(void*)_m, "primitiveGetDefaultSoundRecorder\000\377", (void*)primitiveGetDefaultSoundRecorder},
	{(void*)_m, "primitiveGetNumberOfSoundPlayerDevices\000\377", (void*)primitiveGetNumberOfSoundPlayerDevices},
	{(void*)_m, "primitiveGetNumberOfSoundRecorderDevices\000\377", (void*)primitiveGetNumberOfSoundRecorderDevices},
	{(void*)_m, "primitiveGetSoundPlayerDeviceName\000\377", (void*)primitiveGetSoundPlayerDeviceName},
	{(void*)_m, "primitiveGetSoundRecorderDeviceName\000\377", (void*)primitiveGetSoundRecorderDeviceName},
	{(void*)_m, "primitiveSetDefaultSoundPlayer\000\001", (void*)primitiveSetDefaultSoundPlayer},
	{(void*)_m, "primitiveSetDefaultSoundRecorder\000\001", (void*)primitiveSetDefaultSoundRecorder},
	{(void*)_m, "primitiveSoundAvailableSpace\000\377", (void*)primitiveSoundAvailableSpace},
	{(void*)_m, "primitiveSoundEnableAEC\000\000", (void*)primitiveSoundEnableAEC},
	{(void*)_m, "primitiveSoundGetRecordingSampleRate\000\377", (void*)primitiveSoundGetRecordingSampleRate},
	{(void*)_m, "primitiveSoundGetRecordLevel\000\377", (void*)primitiveSoundGetRecordLevel},
	{(void*)_m, "primitiveSoundGetVolume\000\377", (void*)primitiveSoundGetVolume},
	{(void*)_m, "primitiveSoundInsertSamples\000\000", (void*)primitiveSoundInsertSamples},
	{(void*)_m, "primitiveSoundPlaySamples\000\000", (void*)primitiveSoundPlaySamples},
	{(void*)_m, "primitiveSoundPlaySilence\000\377", (void*)primitiveSoundPlaySilence},
	{(void*)_m, "primitiveSoundRecordSamples\000\000", (void*)primitiveSoundRecordSamples},
	{(void*)_m, "primitiveSoundSetLeftVolume\000\000", (void*)primitiveSoundSetLeftVolume},
	{(void*)_m, "primitiveSoundSetRecordLevel\000\000", (void*)primitiveSoundSetRecordLevel},
	{(void*)_m, "primitiveSoundStart\000\000", (void*)primitiveSoundStart},
	{(void*)_m, "primitiveSoundStartRecording\000\000", (void*)primitiveSoundStartRecording},
	{(void*)_m, "primitiveSoundStartWithSemaphore\000\000", (void*)primitiveSoundStartWithSemaphore},
	{(void*)_m, "primitiveSoundStop\000\377", (void*)primitiveSoundStop},
	{(void*)_m, "primitiveSoundStopRecording\000\377", (void*)primitiveSoundStopRecording},
	{(void*)_m, "primitiveSoundSupportsAEC\000\377", (void*)primitiveSoundSupportsAEC},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{(void*)_m, "shutdownModule\000\377", (void*)shutdownModule},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveSetDefaultSoundPlayerAccessorDepth = 1;
signed char primitiveSetDefaultSoundRecorderAccessorDepth = 1;
signed char primitiveSoundEnableAECAccessorDepth = 0;
signed char primitiveSoundInsertSamplesAccessorDepth = 0;
signed char primitiveSoundPlaySamplesAccessorDepth = 0;
signed char primitiveSoundRecordSamplesAccessorDepth = 0;
signed char primitiveSoundSetLeftVolumeAccessorDepth = 0;
signed char primitiveSoundSetRecordLevelAccessorDepth = 0;
signed char primitiveSoundStartAccessorDepth = 0;
signed char primitiveSoundStartRecordingAccessorDepth = 0;
signed char primitiveSoundStartWithSemaphoreAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
