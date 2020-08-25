/*
 * faCommon.h
 *
 * Declerations for FileAttributes platform independent functions.
 */

#include "faConstants.h"
#include "faSupport.h"

/*
 * FAPathPtr
 *
 * FAPathPtr is used to pass a pointer to the faPath between the VM and image.
 * It holds the current VM session ID to prevent stale pointers being used 
 * across VM restarts.
 *
 * The definition here has to be kept in sync with the VMMaker version.
 */
typedef struct fapathptrstruct {
	int	sessionId;
	fapath	*faPath;
	} FAPathPtr;


sqInt faInitialiseModule();
sqInt faInitSessionId(int *sessionId, struct foo * self);
sqInt faValidateSessionId(int sessionId, struct foo * self);
sqInt faInvalidateSessionId(int *sessionId, struct foo * self);
sqInt faSetStDirOop(fapath *aFaPath, sqInt pathNameOop, struct foo * self);
sqInt faSetStPathOop(fapath *aFaPath, sqInt pathNameOop, struct foo * self);
sqInt faCharToByteArray(const char *cBuf, sqInt *byteArrayOop, struct foo * self);

