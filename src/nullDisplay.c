#include "pharo.h"

#define UNIMPLEMENTED unimplementedPrimitive(__FUNCTION__);

void unimplementedPrimitive(const char* name){
	logWarn("Unimplemented primitive: %s\n", name);
}

#ifdef WIN64
int ioSetCursorARGB(sqInt cursorBitsIndex, sqInt extentX, sqInt extentY, sqInt offsetX, sqInt offsetY)
#else
sqInt ioSetCursorARGB(sqInt cursorBitsIndex, sqInt extentX, sqInt extentY, sqInt offsetX, sqInt offsetY)
#endif
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioForceDisplayUpdate(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioFormPrint(sqInt bitsAddr, sqInt width, sqInt height, sqInt depth,
		  double hScale, double vScale, sqInt landscapeFlag, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

void
ioNoteDisplayChangedwidthheightdepth(void *b, int w, int h, int d, sqInt self)
{
	UNIMPLEMENTED
}

sqInt
ioSetFullScreen(sqInt fullScreen, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioSetCursor(sqInt cursorBitsIndex, sqInt offsetX, sqInt offsetY, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioSetCursorWithMask(sqInt cursorBitsIndex, sqInt cursorMaskIndex, sqInt offsetX, sqInt offsetY, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioShowDisplay(sqInt dispBitsIndex, sqInt width, sqInt height, sqInt depth,
		    sqInt affectedL, sqInt affectedR, sqInt affectedT, sqInt affectedB, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioHasDisplayDepth(sqInt depth, sqInt self)
{
	return true;
}

sqInt
ioSetDisplayMode(sqInt width, sqInt height, sqInt depth, sqInt fullscreenFlag, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

char*
ioGetWindowLabel(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioSetWindowLabelOfSize(void *lblIndex, sqInt sz, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioGetWindowWidth(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioGetWindowHeight(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioSetWindowWidthHeight(sqInt w, sqInt h, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioIsWindowObscured(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioGetNextEvent(sqInputEvent *evt, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioGetButtonState(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioGetKeystroke(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioMousePoint(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioPeekKeystroke(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioProcessEvents(sqInt self)
{
    aioPoll(0);
    return 0;
}

double
ioScreenScaleFactor(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioScreenSize(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt
ioScreenDepth(sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt clipboardSize(sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

sqInt
clipboardReadIntoAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex, sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

sqInt
clipboardWriteFromAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex, sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

static sqInt
dropInit (sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

static sqInt
dropShutdown (sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

char*
dropRequestFileName(sqInt dropIndex)
{
	UNIMPLEMENTED
    return 0;
}

sqInt
dropRequestFileHandle(sqInt dropIndex)
{
	UNIMPLEMENTED
    return nilObject();
}

sqInt
ioBeep(sqInt self)
{
	UNIMPLEMENTED
    return 0;
}

sqInt
ioDisablePowerManager(sqInt disableIfNonZero, sqInt self){
	UNIMPLEMENTED
    return true;
}

void
ioClearProfile(sqInt self){
	UNIMPLEMENTED
}

long
ioControlNewProfile(int on, unsigned long buffer_size, sqInt self){
	UNIMPLEMENTED
	return 0;
}


int plugInNotifyUser(char *msg) {
	UNIMPLEMENTED
	return 0;
}

int plugInTimeToReturn() {
    return false;
}

void
ioNewProfileStatus(sqInt *running, long *buffersize, sqInt self)
{
	UNIMPLEMENTED
}

long
ioNewProfileSamplesInto(void *sampleBuffer, sqInt self)
{
	UNIMPLEMENTED
    return 0;
}


sqInt crashInThisOrAnotherThread(sqInt flags, sqInt self)
{
	UNIMPLEMENTED
	return 0;
}

sqInt ioSetInputSemaphore(sqInt semaIndex, sqInt self){
	UNIMPLEMENTED;
	return 1;
}

void ioSignalInputEvent(sqInt self){
	UNIMPLEMENTED;
}

char* ioGetLogDirectory(sqInt self){
    return "";
}

sqInt ioSetLogDirectoryOfSize(void* lblIndex, sqInt sz, sqInt self){
    return 1;
}
