/****************************************************************************
*   PROJECT: Common include
*   FILE:    FilePlugin.h
*   CONTENT:
*
*   AUTHOR:
*   ADDRESS:
*   EMAIL:
*   RCSID:   $Id$
*
*	2018-03-06 AKG Rename sqFileFileOpen() & sqFileFdOpen() to 
*	               sqConnectToFile(self) and sqConnectToFileDescriptor(self)
*	2018-03-01 AKG add sqFileFileOpen() & sqFileFdOpen()
*	2009-05-15 EEM add stdio flag; reorder SQFile to make it more compact
*	2005-03-26 IKP fix unaligned accesses to file member
*	2004-06-10 IKP 64-bit cleanliness
*	01/22/2002 JMM change off_t to squeakOffsetFileType
*/
/* File support definitions */

#include <sys/types.h>

#ifdef _MSC_VER
typedef int mode_t;
#endif

#include "sqMemoryAccess.h"

/* squeak file record; see sqFilePrims.c for details */
typedef struct {
  int			 sessionID;	/* ikp: must be first */
  void			*file;
#if defined(ACORN)
// ACORN has to have 'lastOp' as at least a 32 bit field in order to work
  int lastOp; // actually used to save file position
  char writable;
  char lastChar;
  char isStdioStream;
#else
  char			 writable;
  char			 lastOp; /* 0 = uncommitted, 1 = read, 2 = write */
  char			 lastChar;
  char			 isStdioStream;
#endif
} SQFile;

/* file i/o */

sqInt   sqFileAtEnd(SQFile *f, struct foo * self);
sqInt   sqFileClose(SQFile *f, struct foo * self);
sqInt   sqFileDeleteNameSize(char *sqFileName, sqInt sqFileNameSize, struct foo * self);
squeakFileOffsetType sqFileGetPosition(SQFile *f, struct foo * self);
sqInt   sqFileInit(struct foo * self);
sqInt   sqFileShutdown(struct foo * self);
sqInt   sqFileOpen(SQFile *f, char *sqFileName, sqInt sqFileNameSize, sqInt writeFlag, struct foo * self);
sqInt   sqFileOpenNew(SQFile *f, char *sqFileName, sqInt sqFileNameSize, sqInt *exists, struct foo * self);
sqInt   sqConnectToFileDescriptor(SQFile *f, int fd, sqInt writeFlag, struct foo * self);
sqInt   sqConnectToFile(SQFile *f, void *file, sqInt writeFlag, struct foo * self);
size_t  sqFileReadIntoAt(SQFile *f, size_t count, char *byteArrayIndex, size_t startIndex, struct foo * self);
sqInt   sqFileRenameOldSizeNewSize(char *sqOldName, sqInt sqOldNameSize, char *sqNewName, sqInt sqNewNameSize, struct foo * self);
sqInt   sqFileSetPosition(SQFile *f, squeakFileOffsetType position, struct foo * self);
squeakFileOffsetType sqFileSize(SQFile *f, struct foo * self);
sqInt   sqFileValid(SQFile *f, struct foo * self);
size_t  sqFileWriteFromAt(SQFile *f, size_t count, char *byteArrayIndex, size_t startIndex, struct foo * self);
sqInt   sqFileFlush(SQFile *f, struct foo * self);
sqInt   sqFileSync(SQFile *f, struct foo * self);
sqInt   sqFileTruncate(SQFile *f,squeakFileOffsetType offset, struct foo * self);
sqInt   sqFileThisSession(struct foo * self);
sqInt   sqFileStdioHandlesInto(SQFile files[3]);
sqInt   sqFileDescriptorType(int fdNum, struct foo * self);

/* directories */

sqInt dir_Create(char *pathString, sqInt pathStringLength);
sqInt dir_Delete(char *pathString, sqInt pathStringLength);
sqInt dir_Delimitor(void);
sqInt dir_Lookup(char *pathString, sqInt pathStringLength, sqInt index,
		/* outputs: */
		char *name, sqInt *nameLength, sqInt *creationDate, sqInt *modificationDate,
		sqInt *isDirectory, squeakFileOffsetType *sizeIfFile, sqInt *posixPermissions, sqInt *isSymlink);
sqInt dir_EntryLookup(char *pathString, sqInt pathStringLength, char *nameString, sqInt nameStringLength,
		/* outputs: */
		char *name, sqInt *nameLength, sqInt *creationDate, sqInt *modificationDate,
		sqInt *isDirectory, squeakFileOffsetType *sizeIfFile, sqInt *posixPermissions, sqInt *isSymlink);
sqInt dir_PathToWorkingDir(char *pathName, sqInt pathNameMax);
sqInt dir_SetMacFileTypeAndCreator(char *filename, sqInt filenameSize, char *fType, char *fCreator);
sqInt dir_GetMacFileTypeAndCreator(char *filename, sqInt filenameSize, char *fType, char *fCreator);
