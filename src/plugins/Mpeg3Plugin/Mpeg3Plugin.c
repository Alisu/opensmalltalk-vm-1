/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.983 uuid: 4cdca841-6318-4c49-95de-8c47d0d7e91d
   from
	Mpeg3Plugin VMMaker.oscog-eem.983 uuid: 4cdca841-6318-4c49-95de-8c47d0d7e91d
 */
static char __buildInfo[] = "Mpeg3Plugin VMMaker.oscog-eem.983 uuid: 4cdca841-6318-4c49-95de-8c47d0d7e91d " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "Mpeg3Plugin.h"
#include "sqMemoryAccess.h"


/*** Constants ***/


/*** Function Prototypes ***/
static sqInt checkFileEntry(mpeg3_t *  aMpegFile);
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) initialiseModule(void);
static sqInt makeFileEntry(mpeg3_t *  aMpegFile);
static mpeg3_t * mpeg3tValueOf(sqInt mpeg3tHandle);
EXPORT(sqInt) primitiveMPEG3AudioChannels(void);
EXPORT(sqInt) primitiveMPEG3AudioSamples(void);
EXPORT(sqInt) primitiveMPEG3CheckSig(void);
EXPORT(sqInt) primitiveMPEG3Close(void);
EXPORT(sqInt) primitiveMPEG3DropFrames(void);
EXPORT(sqInt) primitiveMPEG3EndOfAudio(void);
EXPORT(sqInt) primitiveMPEG3EndOfVideo(void);
EXPORT(sqInt) primitiveMPEG3FrameRate(void);
EXPORT(sqInt) primitiveMPEG3GenerateToc(void);
EXPORT(sqInt) primitiveMPEG3GetFrame(void);
EXPORT(sqInt) primitiveMPEG3GetSample(void);
EXPORT(sqInt) primitiveMPEG3GetTime(void);
EXPORT(sqInt) primitiveMPEG3HasAudio(void);
EXPORT(sqInt) primitiveMPEG3HasVideo(void);
EXPORT(sqInt) primitiveMPEG3Open(void);
EXPORT(sqInt) primitiveMPEG3OpenABuffer(void);
EXPORT(sqInt) primitiveMPEG3PreviousFrame(void);
EXPORT(sqInt) primitiveMPEG3ReadAudio(void);
EXPORT(sqInt) primitiveMPEG3ReadFrame(void);
EXPORT(sqInt) primitiveMPEG3ReadFrameBufferOffset(void);
EXPORT(sqInt) primitiveMPEG3ReReadAudio(void);
EXPORT(sqInt) primitiveMPEG3SampleRate(void);
EXPORT(sqInt) primitiveMPEG3SeekPercentage(void);
EXPORT(sqInt) primitiveMPEG3SetCpus(void);
EXPORT(sqInt) primitiveMPEG3SetFrame(void);
EXPORT(sqInt) primitiveMPEG3SetMmx(void);
EXPORT(sqInt) primitiveMPEG3SetSample(void);
EXPORT(sqInt) primitiveMPEG3TellPercentage(void);
EXPORT(sqInt) primitiveMPEG3TotalAStreams(void);
EXPORT(sqInt) primitiveMPEG3TotalVStreams(void);
EXPORT(sqInt) primitiveMPEG3VideoFrames(void);
EXPORT(sqInt) primitiveMPEG3VideoHeight(void);
EXPORT(sqInt) primitiveMPEG3VideoWidth(void);
static sqInt removeFileEntry(mpeg3_t *  aMpegFile);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
EXPORT(sqInt) shutdownModule(void);
static sqInt sqAssert(sqInt aBool);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*booleanValueOf)(sqInt obj);
static sqInt (*byteSizeOf)(sqInt oop);
static sqInt (*classByteArray)(void);
static sqInt (*failed)(void);
static sqInt (*falseObject)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*floatObjectOf)(double  aFloat);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*integerObjectOf)(sqInt value);
static sqInt (*ioFilenamefromStringofLengthresolveAliases)(char *aCharBuffer, char *aFilenameString, sqInt filenameLength, sqInt aBoolean);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*isIndexable)(sqInt oop);
static sqInt (*isWords)(sqInt oop);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*slotSizeOf)(sqInt oop);
static double (*stackFloatValue)(sqInt offset);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
static sqInt (*trueObject)(void);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt booleanValueOf(sqInt obj);
extern sqInt byteSizeOf(sqInt oop);
extern sqInt classByteArray(void);
extern sqInt failed(void);
extern sqInt falseObject(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt floatObjectOf(double  aFloat);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern sqInt integerObjectOf(sqInt value);
extern sqInt ioFilenamefromStringofLengthresolveAliases(char *aCharBuffer, char *aFilenameString, sqInt filenameLength, sqInt aBoolean);
extern sqInt isBytes(sqInt oop);
extern sqInt isIndexable(sqInt oop);
extern sqInt isWords(sqInt oop);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt slotSizeOf(sqInt oop);
extern double stackFloatValue(sqInt offset);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern sqInt trueObject(void);
extern
#endif
struct VirtualMachine* interpreterProxy;
static sqInt maximumNumberOfFilesToWatch;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"Mpeg3Plugin VMMaker.oscog-eem.983 (i)"
#else
	"Mpeg3Plugin VMMaker.oscog-eem.983 (e)"
#endif
;
static mpeg3_t *mpegFiles[1024+1];


static sqInt
checkFileEntry(mpeg3_t *  aMpegFile)
{
	sqInt i;

	for (i = 1; i <= maximumNumberOfFilesToWatch; i += 1) {
		if ((mpegFiles[i]) == aMpegFile) {
			return 1;
		}
	}
	return 0;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

EXPORT(sqInt)
initialiseModule(void)
{
	sqInt i;

	maximumNumberOfFilesToWatch = 1024;
	for (i = 1; i <= maximumNumberOfFilesToWatch; i += 1) {
		mpegFiles[i] = 0;
	}
	return true;
}

static sqInt
makeFileEntry(mpeg3_t *  aMpegFile)
{
	sqInt i;

	for (i = 1; i <= maximumNumberOfFilesToWatch; i += 1) {
		if ((mpegFiles[i]) == 0) {
			mpegFiles[i] = aMpegFile;
			return 1;
		}
	}
	return 0;
}


/*	Return a pointer to the first byte of of the mpeg3_t record within the 
	given Smalltalk object, or nil if socketOop is not a mpeg3_t record. */

static mpeg3_t *
mpeg3tValueOf(sqInt mpeg3tHandle)
{
	sqInt check;
	mpeg3_t **  index;

	success((isBytes(mpeg3tHandle))
	 && ((byteSizeOf(mpeg3tHandle)) == 4));
	if (failed()) {
		return null;
	}
	else {
		index = ((mpeg3_t **) (firstIndexableField(mpeg3tHandle)));
		check = checkFileEntry(*index);
		if (check == 0) {
			return null;
		}
		return *index;
	}
}


/*	int mpeg3_audio_channels(mpeg3_t *file,int stream) */

EXPORT(sqInt)
primitiveMPEG3AudioChannels(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber >= (mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_audio_channels(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	long mpeg3_audio_samples(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3AudioSamples(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_audio_samples(file,aNumber);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_check_sig(char *path) */

EXPORT(sqInt)
primitiveMPEG3CheckSig(void)
{
	char *path;
	sqInt result;
	char storage[1024] ;
	sqInt sz;
	sqInt _return_value;

	success(isBytes(stackValue(0)));
	path = ((char *) (firstIndexableField(stackValue(0))));
	if (failed()) {
		return null;
	}
	sz = byteSizeOf(((sqInt)(long)(path) - BaseHeaderSize));
	ioFilenamefromStringofLengthresolveAliases(storage, path, sz, 1);
	result = mpeg3_check_sig(storage);
	_return_value = ((result) ? trueObject() : falseObject());
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	int mpeg3_close(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3Close(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	mpeg3_t **  index;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	removeFileEntry(file); mpeg3_close(file);
	index = ((mpeg3_t **) (firstIndexableField(fileHandle)));
	*index = 0;
	if (failed()) {
		return null;
	}
	pop(1);
	return null;
}


/*	int mpeg3_drop_frames(mpeg3_t *file, long frames, int stream) */

EXPORT(sqInt)
primitiveMPEG3DropFrames(void)
{
	sqInt aFrameNumber;
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(2);
	aFrameNumber = stackIntegerValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	result = mpeg3_drop_frames(file,aFrameNumber,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(4, _return_value);
	return null;
}


/*	int mpeg3_end_of_audio(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3EndOfAudio(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_end_of_audio(file,aNumber);
	_return_value = ((result) ? trueObject() : falseObject());
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_end_of_video(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3EndOfVideo(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_end_of_video(file,aNumber);
	_return_value = ((result) ? trueObject() : falseObject());
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	float mpeg3_frame_rate(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3FrameRate(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	double  result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result =  mpeg3_frame_rate(file,aNumber);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_generate_toc_for_Squeak(FILE *output, char *path, int
	timecode_search, int print_streams, char *buffer)
 */

EXPORT(sqInt)
primitiveMPEG3GenerateToc(void)
{
	char *aString;
	sqInt bufferSize;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt streams;
	sqInt timecode;

	fileHandle = stackValue(3);
	timecode = stackIntegerValue(2);
	streams = booleanValueOf(stackValue(1));
	success(isBytes(stackValue(0)));
	aString = ((char *) (firstIndexableField(stackValue(0))));
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	bufferSize = slotSizeOf(stackValue(0));
	mpeg3_generate_toc_for_Squeak(file,timecode,streams,aString,bufferSize);
	if (failed()) {
		return null;
	}
	pop(4);
	return null;
}


/*	long mpeg3_get_frame(mpeg3_t *file,int stream) */

EXPORT(sqInt)
primitiveMPEG3GetFrame(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_get_frame(file,aNumber);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_video_width(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3GetSample(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_get_sample(file,aNumber);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	double mpeg3_get_time(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3GetTime(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	double  result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	result = mpeg3_get_time(file);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	int mpeg3_has_audio(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3HasAudio(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	result = mpeg3_has_audio(file);
	_return_value = ((result) ? trueObject() : falseObject());
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	int mpeg3_has_video(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3HasVideo(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	result = mpeg3_has_video(file);
	_return_value = ((result) ? trueObject() : falseObject());
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	mpeg3_t* mpeg3_open(char *path) */

EXPORT(sqInt)
primitiveMPEG3Open(void)
{
	mpeg3_t ** index;
	sqInt mpeg3Oop;
	char *path;
	char storage[1024];
	sqInt sz;

	success(isBytes(stackValue(0)));
	path = ((char *) (firstIndexableField(stackValue(0))));
	if (failed()) {
		return null;
	}
	sz = byteSizeOf(((sqInt)(long)(path) - BaseHeaderSize));
	ioFilenamefromStringofLengthresolveAliases(storage, path, sz, 1);
	mpeg3Oop = instantiateClassindexableSize(classByteArray(), 4);
	index = ((mpeg3_t **) (firstIndexableField(mpeg3Oop)));
	*index = mpeg3_open(storage,0); makeFileEntry(*index);
	if (failed()) {
		return null;
	}
	popthenPush(2, mpeg3Oop);
	return null;
}

EXPORT(sqInt)
primitiveMPEG3OpenABuffer(void)
{
	mpeg3_t ** index;
	sqInt mpeg3Oop;
	char *path;
	sqInt size;

	success(isBytes(stackValue(1)));
	path = ((char *) (firstIndexableField(stackValue(1))));
	size = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	mpeg3Oop = instantiateClassindexableSize(classByteArray(), 4);
	index = ((mpeg3_t **) (firstIndexableField(mpeg3Oop)));
	*index = mpeg3_open(path,size); makeFileEntry(*index);
	if (failed()) {
		return null;
	}
	popthenPush(3, mpeg3Oop);
	return null;
}


/*	int mpeg3_previous_frame(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3PreviousFrame(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (file == null) {
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_previous_frame(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_read_audio(mpeg3_t *file, 
	float *output_f, 
	short *output_i, 
	int channel, 
	long samples,
	int stream) */

EXPORT(sqInt)
primitiveMPEG3ReadAudio(void)
{
	sqInt aChannelNumber;
	sqInt aNumber;
	sqInt *anArray;
	short *  arrayBase;
	sqInt aSampleNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(4);
	success(isIndexable(stackValue(3)));
	anArray = ((int *) (firstIndexableField(stackValue(3))));
	aChannelNumber = stackIntegerValue(2);
	aSampleNumber = stackIntegerValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(6, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(6, 0);
		return null;
	}
	arrayBase = ((short *) anArray);
	if (failed()) {
		return null;
	}
	result = mpeg3_read_audio(file,(float *) NULL,arrayBase,aChannelNumber,aSampleNumber,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(6, _return_value);
	return null;
}

EXPORT(sqInt)
primitiveMPEG3ReadFrame(void)
{
	unsigned *aBuffer;
	sqInt aByteNumber;
	sqInt aNumber;
	unsigned char *bufferBaseAddr;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt height;
	sqInt i;
	sqInt model;
	sqInt outHeight;
	unsigned char  **  outputRowsPtr;
	sqInt outWidth;
	sqInt result;
	sqInt width;
	sqInt xNumber;
	sqInt yNumber;
	sqInt _return_value;


	/* int mpeg3_read_frame(mpeg3_t *file,
	   unsigned char **output_rows,
	   int in_x,
	   int in_y,
	   int in_w,
	   int in_h,
	   int out_w,
	   int out_h,
	   int color_model,
	   int stream) */

	fileHandle = stackValue(10);
	success(isWords(stackValue(9)));
	aBuffer = ((unsigned *) (firstIndexableField(stackValue(9))));
	xNumber = stackIntegerValue(8);
	yNumber = stackIntegerValue(7);
	width = stackIntegerValue(6);
	height = stackIntegerValue(5);
	outWidth = stackIntegerValue(4);
	outHeight = stackIntegerValue(3);
	model = stackIntegerValue(2);
	aNumber = stackIntegerValue(1);
	aByteNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(12, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(12, 0);
		return null;
	}
	bufferBaseAddr = ((unsigned char *) aBuffer);
	outputRowsPtr = (unsigned char **) memoryAllocate(1,sizeof(unsigned char*) * outHeight);
	for (i = 0; i < outHeight; i += 1) {
		outputRowsPtr[i] = (bufferBaseAddr + (aByteNumber * i));
	}
	result = mpeg3_read_frame(file,outputRowsPtr,xNumber,yNumber,width,height,outWidth,outHeight,model,aNumber);
	memoryFree(outputRowsPtr);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(12, _return_value);
	return null;
}

EXPORT(sqInt)
primitiveMPEG3ReadFrameBufferOffset(void)
{
	unsigned *aBuffer;
	sqInt aBufferOffset;
	sqInt aByteNumber;
	sqInt aNumber;
	unsigned char *bufferBaseAddr;
	mpeg3_t * file;
	sqInt fileHandle;
	sqInt height;
	sqInt i;
	sqInt model;
	sqInt outHeight;
	unsigned char  ** outputRowsPtr;
	sqInt outWidth;
	sqInt result;
	sqInt width;
	sqInt xNumber;
	sqInt yNumber;
	sqInt _return_value;


	/* int mpeg3_read_frame(mpeg3_t *file,
	   unsigned char **output_rows,
	   int in_x,
	   int in_y,
	   int in_w,
	   int in_h,
	   int out_w,
	   int out_h,
	   int color_model,
	   int stream) */

	fileHandle = stackValue(11);
	success(isWords(stackValue(10)));
	aBuffer = ((unsigned *) (firstIndexableField(stackValue(10))));
	aBufferOffset = stackIntegerValue(9);
	xNumber = stackIntegerValue(8);
	yNumber = stackIntegerValue(7);
	width = stackIntegerValue(6);
	height = stackIntegerValue(5);
	outWidth = stackIntegerValue(4);
	outHeight = stackIntegerValue(3);
	model = stackIntegerValue(2);
	aNumber = stackIntegerValue(1);
	aByteNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(13, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(13, 0);
		return null;
	}
	bufferBaseAddr = ((unsigned char *) aBuffer);
	outputRowsPtr = (unsigned char **) memoryAllocate(1,sizeof(unsigned char*) * outHeight);
	for (i = 0; i < outHeight; i += 1) {
		outputRowsPtr[i] = ((bufferBaseAddr + aBufferOffset) + (aByteNumber * i));
	}
	result = mpeg3_read_frame(file,outputRowsPtr,xNumber,yNumber,width,height,outWidth,outHeight,model,aNumber);
	memoryFree(outputRowsPtr);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(13, _return_value);
	return null;
}


/*	int mpeg3_reread_audio(mpeg3_t *file, 
	float *output_f, 
	short *output_i, 
	int channel, 
	long samples,
	int stream) */

EXPORT(sqInt)
primitiveMPEG3ReReadAudio(void)
{
	sqInt aChannelNumber;
	sqInt aNumber;
	sqInt *anArray;
	short *  arrayBase;
	sqInt aSampleNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(4);
	success(isIndexable(stackValue(3)));
	anArray = ((int *) (firstIndexableField(stackValue(3))));
	aChannelNumber = stackIntegerValue(2);
	aSampleNumber = stackIntegerValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(6, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(6, 0);
		return null;
	}
	arrayBase = ((short *) anArray);
	if (failed()) {
		return null;
	}
	result = mpeg3_reread_audio(file,(float *) NULL,arrayBase,aChannelNumber,aSampleNumber,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(6, _return_value);
	return null;
}


/*	int mpeg3_sample_rate(mpeg3_t *file,int stream) */

EXPORT(sqInt)
primitiveMPEG3SampleRate(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_sample_rate(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_seek_percentage(mpeg3_t *file, double percentage) */

EXPORT(sqInt)
primitiveMPEG3SeekPercentage(void)
{
	double aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackFloatValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (aNumber < 0.0) {
		success(0);
		return null;
	}
	if (aNumber > 1.0) {
		success(0);
		return null;
	}
	if (file == null) {
		return null;
	}
	result = mpeg3_seek_percentage(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_set_cpus(mpeg3_t *file, int cpus) */

EXPORT(sqInt)
primitiveMPEG3SetCpus(void)
{
	sqInt cpus;
	mpeg3_t *  file;
	sqInt fileHandle;

	fileHandle = stackValue(1);
	cpus = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (cpus < 0) {
		success(0);
		return null;
	}
	if (file == null) {
		return null;
	}
	mpeg3_set_cpus(file,cpus);
	if (failed()) {
		return null;
	}
	pop(2);
	return null;
}


/*	int mpeg3_set_frame(mpeg3_t *file, long frame, int stream) */

EXPORT(sqInt)
primitiveMPEG3SetFrame(void)
{
	double aFrameNumber;
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(2);
	aFrameNumber = stackFloatValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	result = mpeg3_set_frame(file,(long) aFrameNumber,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(4, _return_value);
	return null;
}


/*	int mpeg3_set_mmx(mpeg3_t *file, int use_mmx) */

EXPORT(sqInt)
primitiveMPEG3SetMmx(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt mmx;

	fileHandle = stackValue(1);
	mmx = booleanValueOf(stackValue(0));
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	mpeg3_set_mmx(file,mmx);
	if (failed()) {
		return null;
	}
	pop(2);
	return null;
}


/*	int mpeg3_set_sample(mpeg3_t *file, long sample, int stream) */

EXPORT(sqInt)
primitiveMPEG3SetSample(void)
{
	sqInt aNumber;
	double aSampleNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(2);
	aSampleNumber = stackFloatValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_astreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(4, 0);
		return null;
	}
	if (aSampleNumber < 0) {
		success(0);
		return null;
	}
	result = mpeg3_set_sample(file,aSampleNumber,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(4, _return_value);
	return null;
}


/*	double mpeg3_tell_percentage(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3TellPercentage(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	double  result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	result = mpeg3_tell_percentage(file);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	int mpeg3_total_astreams(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3TotalAStreams(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(2, 0);
		return null;
	}
	result = mpeg3_total_astreams(file);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	int mpeg3_total_vstreams(mpeg3_t *file) */

EXPORT(sqInt)
primitiveMPEG3TotalVStreams(void)
{
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		return null;
	}
	result = mpeg3_total_vstreams(file);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(2, _return_value);
	return null;
}


/*	long mpeg3_video_frames(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3VideoFrames(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_video_frames(file,aNumber);
	_return_value = floatObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_video_height(mpeg3_t *file,int stream) */

EXPORT(sqInt)
primitiveMPEG3VideoHeight(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_video_height(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}


/*	int mpeg3_video_width(mpeg3_t *file, int stream) */

EXPORT(sqInt)
primitiveMPEG3VideoWidth(void)
{
	sqInt aNumber;
	mpeg3_t *  file;
	sqInt fileHandle;
	sqInt result;
	sqInt _return_value;

	fileHandle = stackValue(1);
	aNumber = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	file = mpeg3tValueOf(fileHandle);
	if (file == null) {
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	if (aNumber < 0) {
		success(0);
		return null;
	}
	if (aNumber >= (result = mpeg3_total_vstreams(file))) {
		success(0);
		if (failed()) {
			return null;
		}
		popthenPush(3, 0);
		return null;
	}
	result = mpeg3_video_width(file,aNumber);
	_return_value = integerObjectOf(result);
	if (failed()) {
		return null;
	}
	popthenPush(3, _return_value);
	return null;
}

static sqInt
removeFileEntry(mpeg3_t *  aMpegFile)
{
	sqInt i;

	for (i = 1; i <= maximumNumberOfFilesToWatch; i += 1) {
		if ((mpegFiles[i]) == aMpegFile) {
			mpegFiles[i] = 0;
			return 1;
		}
	}
	return 0;
}


/*	Note: This is coded so that it can be run in Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		booleanValueOf = interpreterProxy->booleanValueOf;
		byteSizeOf = interpreterProxy->byteSizeOf;
		classByteArray = interpreterProxy->classByteArray;
		failed = interpreterProxy->failed;
		falseObject = interpreterProxy->falseObject;
		firstIndexableField = interpreterProxy->firstIndexableField;
		floatObjectOf = interpreterProxy->floatObjectOf;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		integerObjectOf = interpreterProxy->integerObjectOf;
		ioFilenamefromStringofLengthresolveAliases = interpreterProxy->ioFilenamefromStringofLengthresolveAliases;
		isBytes = interpreterProxy->isBytes;
		isIndexable = interpreterProxy->isIndexable;
		isWords = interpreterProxy->isWords;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		slotSizeOf = interpreterProxy->slotSizeOf;
		stackFloatValue = interpreterProxy->stackFloatValue;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
		trueObject = interpreterProxy->trueObject;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}

EXPORT(sqInt)
shutdownModule(void)
{
	sqInt i;

	for (i = 1; i <= maximumNumberOfFilesToWatch; i += 1) {
		if ((mpegFiles[i]) != 0) {
			mpeg3_close(mpegFiles[i]);
			mpegFiles[i] = 0;
		}
	}
	return true;
}

static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* Mpeg3Plugin_exports[][3] = {
	{"Mpeg3Plugin", "getModuleName", (void*)getModuleName},
	{"Mpeg3Plugin", "initialiseModule", (void*)initialiseModule},
	{"Mpeg3Plugin", "primitiveMPEG3AudioChannels\000\001", (void*)primitiveMPEG3AudioChannels},
	{"Mpeg3Plugin", "primitiveMPEG3AudioSamples\000\001", (void*)primitiveMPEG3AudioSamples},
	{"Mpeg3Plugin", "primitiveMPEG3CheckSig\000\377", (void*)primitiveMPEG3CheckSig},
	{"Mpeg3Plugin", "primitiveMPEG3Close\000\001", (void*)primitiveMPEG3Close},
	{"Mpeg3Plugin", "primitiveMPEG3DropFrames\000\001", (void*)primitiveMPEG3DropFrames},
	{"Mpeg3Plugin", "primitiveMPEG3EndOfAudio\000\001", (void*)primitiveMPEG3EndOfAudio},
	{"Mpeg3Plugin", "primitiveMPEG3EndOfVideo\000\001", (void*)primitiveMPEG3EndOfVideo},
	{"Mpeg3Plugin", "primitiveMPEG3FrameRate\000\001", (void*)primitiveMPEG3FrameRate},
	{"Mpeg3Plugin", "primitiveMPEG3GenerateToc\000\001", (void*)primitiveMPEG3GenerateToc},
	{"Mpeg3Plugin", "primitiveMPEG3GetFrame\000\001", (void*)primitiveMPEG3GetFrame},
	{"Mpeg3Plugin", "primitiveMPEG3GetSample\000\001", (void*)primitiveMPEG3GetSample},
	{"Mpeg3Plugin", "primitiveMPEG3GetTime\000\001", (void*)primitiveMPEG3GetTime},
	{"Mpeg3Plugin", "primitiveMPEG3HasAudio\000\001", (void*)primitiveMPEG3HasAudio},
	{"Mpeg3Plugin", "primitiveMPEG3HasVideo\000\001", (void*)primitiveMPEG3HasVideo},
	{"Mpeg3Plugin", "primitiveMPEG3Open\000\377", (void*)primitiveMPEG3Open},
	{"Mpeg3Plugin", "primitiveMPEG3OpenABuffer\000\000", (void*)primitiveMPEG3OpenABuffer},
	{"Mpeg3Plugin", "primitiveMPEG3PreviousFrame\000\001", (void*)primitiveMPEG3PreviousFrame},
	{"Mpeg3Plugin", "primitiveMPEG3ReadAudio\000\001", (void*)primitiveMPEG3ReadAudio},
	{"Mpeg3Plugin", "primitiveMPEG3ReadFrame\000\001", (void*)primitiveMPEG3ReadFrame},
	{"Mpeg3Plugin", "primitiveMPEG3ReadFrameBufferOffset\000\001", (void*)primitiveMPEG3ReadFrameBufferOffset},
	{"Mpeg3Plugin", "primitiveMPEG3ReReadAudio\000\001", (void*)primitiveMPEG3ReReadAudio},
	{"Mpeg3Plugin", "primitiveMPEG3SampleRate\000\001", (void*)primitiveMPEG3SampleRate},
	{"Mpeg3Plugin", "primitiveMPEG3SeekPercentage\000\001", (void*)primitiveMPEG3SeekPercentage},
	{"Mpeg3Plugin", "primitiveMPEG3SetCpus\000\001", (void*)primitiveMPEG3SetCpus},
	{"Mpeg3Plugin", "primitiveMPEG3SetFrame\000\001", (void*)primitiveMPEG3SetFrame},
	{"Mpeg3Plugin", "primitiveMPEG3SetMmx\000\001", (void*)primitiveMPEG3SetMmx},
	{"Mpeg3Plugin", "primitiveMPEG3SetSample\000\001", (void*)primitiveMPEG3SetSample},
	{"Mpeg3Plugin", "primitiveMPEG3TellPercentage\000\001", (void*)primitiveMPEG3TellPercentage},
	{"Mpeg3Plugin", "primitiveMPEG3TotalAStreams\000\001", (void*)primitiveMPEG3TotalAStreams},
	{"Mpeg3Plugin", "primitiveMPEG3TotalVStreams\000\001", (void*)primitiveMPEG3TotalVStreams},
	{"Mpeg3Plugin", "primitiveMPEG3VideoFrames\000\001", (void*)primitiveMPEG3VideoFrames},
	{"Mpeg3Plugin", "primitiveMPEG3VideoHeight\000\001", (void*)primitiveMPEG3VideoHeight},
	{"Mpeg3Plugin", "primitiveMPEG3VideoWidth\000\001", (void*)primitiveMPEG3VideoWidth},
	{"Mpeg3Plugin", "setInterpreter", (void*)setInterpreter},
	{"Mpeg3Plugin", "shutdownModule\000\377", (void*)shutdownModule},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveMPEG3AudioChannelsAccessorDepth = 1;
signed char primitiveMPEG3AudioSamplesAccessorDepth = 1;
signed char primitiveMPEG3CloseAccessorDepth = 1;
signed char primitiveMPEG3DropFramesAccessorDepth = 1;
signed char primitiveMPEG3EndOfAudioAccessorDepth = 1;
signed char primitiveMPEG3EndOfVideoAccessorDepth = 1;
signed char primitiveMPEG3FrameRateAccessorDepth = 1;
signed char primitiveMPEG3GenerateTocAccessorDepth = 1;
signed char primitiveMPEG3GetFrameAccessorDepth = 1;
signed char primitiveMPEG3GetSampleAccessorDepth = 1;
signed char primitiveMPEG3GetTimeAccessorDepth = 1;
signed char primitiveMPEG3HasAudioAccessorDepth = 1;
signed char primitiveMPEG3HasVideoAccessorDepth = 1;
signed char primitiveMPEG3OpenABufferAccessorDepth = 0;
signed char primitiveMPEG3PreviousFrameAccessorDepth = 1;
signed char primitiveMPEG3ReadAudioAccessorDepth = 1;
signed char primitiveMPEG3ReadFrameAccessorDepth = 1;
signed char primitiveMPEG3ReadFrameBufferOffsetAccessorDepth = 1;
signed char primitiveMPEG3ReReadAudioAccessorDepth = 1;
signed char primitiveMPEG3SampleRateAccessorDepth = 1;
signed char primitiveMPEG3SeekPercentageAccessorDepth = 1;
signed char primitiveMPEG3SetCpusAccessorDepth = 1;
signed char primitiveMPEG3SetFrameAccessorDepth = 1;
signed char primitiveMPEG3SetMmxAccessorDepth = 1;
signed char primitiveMPEG3SetSampleAccessorDepth = 1;
signed char primitiveMPEG3TellPercentageAccessorDepth = 1;
signed char primitiveMPEG3TotalAStreamsAccessorDepth = 1;
signed char primitiveMPEG3TotalVStreamsAccessorDepth = 1;
signed char primitiveMPEG3VideoFramesAccessorDepth = 1;
signed char primitiveMPEG3VideoHeightAccessorDepth = 1;
signed char primitiveMPEG3VideoWidthAccessorDepth = 1;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
