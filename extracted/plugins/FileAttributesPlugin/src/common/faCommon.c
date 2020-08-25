/*
 * faCommon.c
 *
 * Provides a number of platform independent functions for FileAttributesPlugin.
 */

#include "sq.h"
#include "faCommon.h"

extern struct VirtualMachine * interpreterProxy;
int	vmSessionId = 0;


/*
 * faInitialiseModule
 *
 * Initialise global data for the FileAttributesPlugin.
 *
 * This function must be called only once each each time the VM is run.
 */
sqInt 
faInitialiseModule(struct foo * self)
{
	if (vmSessionId == 0)
		return interpreterProxy->falseObject(self);
	vmSessionId = interpreterProxy->getThisSessionID(self);
	return interpreterProxy->trueObject(self);
}



/*
 * faInitSessionId
 *
 * Initialise the supplied session.
 */
sqInt 
faInitSessionId(int *sessionId, struct foo * self)
{
	*sessionId = vmSessionId;
	return FA_SUCCESS;
}



/*
 * faValidateSessionId
 *
 * Check that the supplied faPath structure looks valid.
 *
 * Currently this is just checking that the sessionId is correct.
 */
sqInt 
faValidateSessionId(int sessionId, struct foo * self)
{
	return sessionId == vmSessionId;
}



/*
 * faInvalidateSessionId
 *
 * Mark the supplied faPath structure as invalid.
 */
sqInt 
faInvalidateSessionId(int *sessionId, struct foo * self)
{
	*sessionId = 0;
	return FA_SUCCESS;
}



sqInt 
faSetStDirOop(fapath *aFaPath, sqInt pathNameOop, struct foo * self)
{
int	len;
char	*pathName;


	len = interpreterProxy->stSizeOf(pathNameOop, self);
	pathName = interpreterProxy->arrayValueOf(pathNameOop, self);
	return faSetStDir(aFaPath, pathName, len, self);
}



sqInt 
faSetStPathOop(fapath *aFaPath, sqInt pathNameOop, struct foo * self)
{
int		len;
char	*pathName;


	len = interpreterProxy->stSizeOf(pathNameOop, self);
	pathName = interpreterProxy->arrayValueOf(pathNameOop, self);
	return faSetStPath(aFaPath, pathName, len, self);
}



/*
 * faCharToByteArray
 *
 * Copy the supplied C string to a newly allocated ByteArray
 */
sqInt faCharToByteArray(const char *cBuf, sqInt *byteArrayOop, struct foo * self)
{
unsigned char *byteArrayPtr;
sqInt len;
sqInt newByteArray;


	/* We never return strings longer than PATH_MAX */
	len = strlen(cBuf);
	if (len >= FA_PATH_MAX) {
		return -1 /* stringTooLong */;
	}
	newByteArray = interpreterProxy->instantiateClassindexableSize(interpreterProxy->classByteArray(self), len, self);
	if (!(newByteArray)) {
		return interpreterProxy->primitiveFailFor(PrimErrNoMemory, self);
	}
	byteArrayPtr = interpreterProxy->arrayValueOf(newByteArray, self);
	memcpy(byteArrayPtr, cBuf, len);
	byteArrayOop[0] = newByteArray;
	return 0;
}



