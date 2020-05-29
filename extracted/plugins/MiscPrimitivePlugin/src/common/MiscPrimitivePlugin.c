/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.2480 uuid: bb3ffda7-8241-4dea-b886-d656e474b6c1
   from
	MiscPrimitivePlugin VMMaker.oscog-eem.2480 uuid: bb3ffda7-8241-4dea-b886-d656e474b6c1
 */
static char __buildInfo[] = "MiscPrimitivePlugin VMMaker.oscog-eem.2480 uuid: bb3ffda7-8241-4dea-b886-d656e474b6c1 " __DATE__ ;



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

#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadArgument 3
#define PrimErrBadIndex 4
#define PrimErrNoModification 8
#define PrimErrUnsupported 7


/*** Function Prototypes ***/
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) primitiveCompareString(void);
EXPORT(sqInt) primitiveCompressToByteArray(void);
EXPORT(sqInt) primitiveConvert8BitSigned(void);
EXPORT(sqInt) primitiveDecompressFromByteArray(void);
EXPORT(sqInt) primitiveFindFirstInString(void);
EXPORT(sqInt) primitiveFindSubstring(void);
EXPORT(sqInt) primitiveIndexOfAsciiInString(void);
EXPORT(sqInt) primitiveStringHash(void);
EXPORT(sqInt) primitiveTranslateStringWithTable(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine *anInterpreter);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static void * (*arrayValueOf)(sqInt oop, struct foo * self);
static sqInt (*byteSizeOf)(sqInt oop, struct foo * self);
static sqInt (*failed)(struct foo * self);
static void * (*firstIndexableField)(sqInt oop, struct foo * self);
static sqInt (*isBytes)(sqInt oop, struct foo * self);
#if IMMUTABILITY
static sqInt (*isOopImmutable)(sqInt oop, struct foo * self);
#endif /* IMMUTABILITY */
static sqInt (*methodArgumentCount)(struct foo * self);
static sqInt (*methodReturnInteger)(sqInt integer, struct foo * self);
static sqInt (*methodReturnReceiver)(struct foo * self);
static sqInt (*pop)(sqInt nItems, struct foo * self);
static sqInt (*primitiveFailFor)(sqInt reasonCode, struct foo * self);
static sqInt (*sizeOfSTArrayFromCPrimitive)(void *cPtr, struct foo * self);
static sqInt (*stackIntegerValue)(sqInt offset, struct foo * self);
static sqInt (*stackValue)(sqInt offset, struct foo * self);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern void * arrayValueOf(sqInt oop, struct foo * self);
extern sqInt byteSizeOf(sqInt oop, struct foo * self);
extern sqInt failed(struct foo * self);
extern void * firstIndexableField(sqInt oop, struct foo * self);
extern sqInt isBytes(sqInt oop, struct foo * self);
#if IMMUTABILITY
#if IMMUTABILITY
extern sqInt isOopImmutable(sqInt oop, struct foo * self);
#endif /* IMMUTABILITY */
#else
# define isOopImmutable(oop) 0
#endif
extern sqInt methodArgumentCount(struct foo * self);
extern sqInt methodReturnInteger(sqInt integer, struct foo * self);
extern sqInt methodReturnReceiver(struct foo * self);
extern sqInt pop(sqInt nItems, struct foo * self);
extern sqInt primitiveFailFor(sqInt reasonCode, struct foo * self);
extern sqInt sizeOfSTArrayFromCPrimitive(void *cPtr, struct foo * self);
extern sqInt stackIntegerValue(sqInt offset, struct foo * self);
extern sqInt stackValue(sqInt offset, struct foo * self);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"MiscPrimitivePlugin VMMaker.oscog-eem.2480 (i)"
#else
	"MiscPrimitivePlugin VMMaker.oscog-eem.2480 (e)"
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


/*	ByteString (class) compare: string1 with: string2 collated: order */

	/* MiscPrimitivePlugin>>#primitiveCompareString */
EXPORT(sqInt)
primitiveCompareString(void)
{
    unsigned char c1;
    unsigned char c2;
    sqInt i;
    sqInt len1;
    sqInt len2;
    unsigned char *order;
    sqInt orderOop;
    unsigned char *string1;
    sqInt string1Oop;
    unsigned char *string2;
    sqInt string2Oop;

	orderOop = stackValue(0, interpreterProxy->interpreterState);
	string2Oop = stackValue(1, interpreterProxy->interpreterState);
	string1Oop = stackValue(2, interpreterProxy->interpreterState);
	if (!((isBytes(orderOop, interpreterProxy->interpreterState))
		 && ((isBytes(string2Oop, interpreterProxy->interpreterState))
		 && (isBytes(string1Oop, interpreterProxy->interpreterState))))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	order = firstIndexableField(orderOop, interpreterProxy->interpreterState);
	if ((sizeOfSTArrayFromCPrimitive(order, interpreterProxy->interpreterState)) < 256) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	string1 = firstIndexableField(string1Oop, interpreterProxy->interpreterState);
	string2 = firstIndexableField(string2Oop, interpreterProxy->interpreterState);
	len1 = sizeOfSTArrayFromCPrimitive(string1, interpreterProxy->interpreterState);
	len2 = sizeOfSTArrayFromCPrimitive(string2, interpreterProxy->interpreterState);
	for (i = 0; i < (((len1 < len2) ? len1 : len2)); i += 1) {
		c1 = order[string1[i]];
		c2 = order[string2[i]];
		if (!(c1 == c2)) {
			return methodReturnInteger((c1 < c2
				? 1
				: 3), interpreterProxy->interpreterState);
		}
	}
	methodReturnInteger((len1 == len2
		? 2
		: (len1 < len2
				? 1
				: 3)), interpreterProxy->interpreterState);
	return 0;
}


/*	Bitmap compress: bm toByteArray: ba */

	/* MiscPrimitivePlugin>>#primitiveCompressToByteArray */
EXPORT(sqInt)
primitiveCompressToByteArray(void)
{
    unsigned char *ba;
    int *bm;
    sqInt destSize;
    sqInt eqBytes;
    sqInt i;
    sqInt j;
    sqInt j1;
    sqInt j2;
    sqInt j3;
    sqInt j4;
    sqInt j5;
    sqInt j6;
    sqInt j7;
    sqInt k;
    int lowByte;
    sqInt m;
    sqInt size;
    int word;

	bm = arrayValueOf(stackValue(1, interpreterProxy->interpreterState), interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return null;
	}
	if (!(isBytes(stackValue(0, interpreterProxy->interpreterState), interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	if (isOopImmutable(stackValue(0, interpreterProxy->interpreterState), interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrNoModification, interpreterProxy->interpreterState);
	}
	ba = firstIndexableField(stackValue(0, interpreterProxy->interpreterState), interpreterProxy->interpreterState);
	size = sizeOfSTArrayFromCPrimitive(bm, interpreterProxy->interpreterState);
	destSize = sizeOfSTArrayFromCPrimitive(ba, interpreterProxy->interpreterState);
	if (destSize < (((size * 4) + 7) + ((size / 0x7C0) * 3))) {
		return primitiveFailFor(PrimErrUnsupported, interpreterProxy->interpreterState);
	}
	/* begin encodeInt:in:at: */
	if (size <= 223) {
		ba[0] = size;
		i = 0 + 1;
		goto l7;
	}
	if (size <= 7935) {
		ba[0] = ((size / 256) + 224);
		ba[0 + 1] = (size % 256);
		i = 0 + 2;
		goto l7;
	}
	ba[0] = 0xFF;
	/* begin encodeBytesOf:in:at: */
	for (j7 = 0; j7 <= 3; j7 += 1) {
		ba[(0 + 1) + j7] = ((((usqInt) size) >> ((3 - j7) * 8)) & 0xFF);
	}
	i = (0 + 1) + 4;
	l7:	/* end encodeInt:in:at: */;
	k = 0;
	while (k < size) {
		word = bm[k];
		lowByte = word & 0xFF;
		eqBytes = (((((usqInt) word) >> 8) & 0xFF) == lowByte)
		 && ((((((usqInt) word) >> 16) & 0xFF) == lowByte)
		 && (((((usqInt) word) >> 24) & 0xFF) == lowByte));
		j = k;
		while (((j + 1) < size)
		 && (word == (bm[j + 1]))) {
			j += 1;
		}
		if (j > k) {
			if (eqBytes) {
				/* begin encodeInt:in:at: */
				if (((((j - k) + 1) * 4) + 1) <= 223) {
					ba[i] = ((((j - k) + 1) * 4) + 1);
					i += 1;
					goto l1;
				}
				if (((((j - k) + 1) * 4) + 1) <= 7935) {
					ba[i] = ((((((j - k) + 1) * 4) + 1) / 256) + 224);
					ba[i + 1] = (((((j - k) + 1) * 4) + 1) % 256);
					i += 2;
					goto l1;
				}
				ba[i] = 0xFF;
				/* begin encodeBytesOf:in:at: */
				for (j1 = 0; j1 <= 3; j1 += 1) {
					ba[(i + 1) + j1] = ((((usqInt) ((((j - k) + 1) * 4) + 1)) >> ((3 - j1) * 8)) & 0xFF);
				}
				i = (i + 1) + 4;
	l1:	/* end encodeInt:in:at: */;
				ba[i] = lowByte;
				i += 1;
			}
			else {
				/* begin encodeInt:in:at: */
				if (((((j - k) + 1) * 4) + 2) <= 223) {
					ba[i] = ((((j - k) + 1) * 4) + 2);
					i += 1;
					goto l2;
				}
				if (((((j - k) + 1) * 4) + 2) <= 7935) {
					ba[i] = ((((((j - k) + 1) * 4) + 2) / 256) + 224);
					ba[i + 1] = (((((j - k) + 1) * 4) + 2) % 256);
					i += 2;
					goto l2;
				}
				ba[i] = 0xFF;
				/* begin encodeBytesOf:in:at: */
				for (j2 = 0; j2 <= 3; j2 += 1) {
					ba[(i + 1) + j2] = ((((usqInt) ((((j - k) + 1) * 4) + 2)) >> ((3 - j2) * 8)) & 0xFF);
				}
				i = (i + 1) + 4;
	l2:	/* end encodeInt:in:at: */;
				/* begin encodeBytesOf:in:at: */
				for (j3 = 0; j3 <= 3; j3 += 1) {
					ba[i + j3] = ((((usqInt) word) >> ((3 - j3) * 8)) & 0xFF);
				}
				i += 4;
			}
			k = j + 1;
		}
		else {
			if (eqBytes) {
				/* begin encodeInt:in:at: */
				if (((1 * 4) + 1) <= 223) {
					ba[i] = ((1 * 4) + 1);
					i += 1;
					goto l4;
				}
				if (((1 * 4) + 1) <= 7935) {
					ba[i] = ((((1 * 4) + 1) / 256) + 224);
					ba[i + 1] = (((1 * 4) + 1) % 256);
					i += 2;
					goto l4;
				}
				ba[i] = 0xFF;
				/* begin encodeBytesOf:in:at: */
				for (j4 = 0; j4 <= 3; j4 += 1) {
					ba[(i + 1) + j4] = ((((usqInt) ((1 * 4) + 1)) >> ((3 - j4) * 8)) & 0xFF);
				}
				i = (i + 1) + 4;
	l4:	/* end encodeInt:in:at: */;
				ba[i] = lowByte;
				i += 1;
				k += 1;
			}
			else {
				while (((j + 1) < size)
				 && ((bm[j]) != (bm[j + 1]))) {
					j += 1;
				}
				if ((j + 1) == size) {
					j += 1;
				}
				/* begin encodeInt:in:at: */
				if ((((j - k) * 4) + 3) <= 223) {
					ba[i] = (((j - k) * 4) + 3);
					i += 1;
					goto l6;
				}
				if ((((j - k) * 4) + 3) <= 7935) {
					ba[i] = (((((j - k) * 4) + 3) / 256) + 224);
					ba[i + 1] = ((((j - k) * 4) + 3) % 256);
					i += 2;
					goto l6;
				}
				ba[i] = 0xFF;
				/* begin encodeBytesOf:in:at: */
				for (j6 = 0; j6 <= 3; j6 += 1) {
					ba[(i + 1) + j6] = ((((usqInt) (((j - k) * 4) + 3)) >> ((3 - j6) * 8)) & 0xFF);
				}
				i = (i + 1) + 4;
	l6:	/* end encodeInt:in:at: */;
				for (m = k; m < j; m += 1) {
					/* begin encodeBytesOf:in:at: */
					for (j5 = 0; j5 <= 3; j5 += 1) {
						ba[i + j5] = ((((usqInt) (bm[m])) >> ((3 - j5) * 8)) & 0xFF);
					}
					i += 4;
				}
				k = j;
			}
		}
	}
	methodReturnInteger(i, interpreterProxy->interpreterState);
	return 0;
}


/*	SampledSound (class) convert8bitSignedFrom: aByteArray to16Bit:
	aSoundBuffer 
 */

	/* MiscPrimitivePlugin>>#primitiveConvert8BitSigned */
EXPORT(sqInt)
primitiveConvert8BitSigned(void)
{
    unsigned char *aByteArray;
    sqInt arraySize;
    unsigned short *aSoundBuffer;
    sqInt byteArrayOop;
    sqInt i;
    unsigned char s;
    sqInt soundBufferOop;

	byteArrayOop = stackValue(1, interpreterProxy->interpreterState);
	if (!(isBytes(byteArrayOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	aByteArray = firstIndexableField(byteArrayOop, interpreterProxy->interpreterState);
	soundBufferOop = stackValue(0, interpreterProxy->interpreterState);
	aSoundBuffer = arrayValueOf(soundBufferOop, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	if (isOopImmutable(soundBufferOop, interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrNoModification, interpreterProxy->interpreterState);
	}
	arraySize = sizeOfSTArrayFromCPrimitive(aByteArray, interpreterProxy->interpreterState);
	if ((byteSizeOf(soundBufferOop, interpreterProxy->interpreterState)) < (2 * arraySize)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	for (i = 0; i < arraySize; i += 1) {
		s = aByteArray[i];
		aSoundBuffer[i] = ((s > 0x7F
	? ((usqInt) (s - 256) << 8)
	: ((usqInt) s << 8)));
	}
	methodReturnReceiver(interpreterProxy->interpreterState);
	return 0;
}


/*	Bitmap decompress: bm fromByteArray: ba at: index */

	/* MiscPrimitivePlugin>>#primitiveDecompressFromByteArray */
EXPORT(sqInt)
primitiveDecompressFromByteArray(void)
{
    unsigned int anInt;
    unsigned char *ba;
    int *bm;
    unsigned int code;
    unsigned int data;
    sqInt end;
    sqInt i;
    sqInt index;
    sqInt j;
    sqInt k;
    sqInt m;
    unsigned int n;
    sqInt pastEnd;

	bm = arrayValueOf(stackValue(2, interpreterProxy->interpreterState), interpreterProxy->interpreterState);
	if (isOopImmutable(stackValue(2, interpreterProxy->interpreterState), interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrNoModification, interpreterProxy->interpreterState);
	}
	if (!(isBytes(stackValue(1, interpreterProxy->interpreterState), interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	ba = firstIndexableField(stackValue(1, interpreterProxy->interpreterState), interpreterProxy->interpreterState);
	index = stackIntegerValue(0, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return null;
	}
	i = index - 1;
	k = 0;
	end = sizeOfSTArrayFromCPrimitive(ba, interpreterProxy->interpreterState);
	pastEnd = sizeOfSTArrayFromCPrimitive(bm, interpreterProxy->interpreterState);
	while (i < end) {
		anInt = ba[i];
		i += 1;
		if (!(anInt <= 223)) {
			if (anInt <= 0xFE) {
				anInt = ((anInt - 224) * 256) + (ba[i]);
				i += 1;
			}
			else {
				anInt = 0;
				for (j = 1; j <= 4; j += 1) {
					anInt = (((usqInt) anInt << 8)) + (ba[i]);
					i += 1;
				}
			}
		}
		n = ((usqInt) anInt) >> 2;
		if ((k + n) > pastEnd) {
			return primitiveFailFor(PrimErrBadIndex, interpreterProxy->interpreterState);
		}

		/* code = 0 ifTrue: [nil]. */
		code = anInt & 3;
		if (code == 1) {
			data = ba[i];
			i += 1;
			data = data | (((usqInt) data << 8));
			data = data | (((usqInt) data << 16));
			for (j = 1; j <= n; j += 1) {
				bm[k] = data;
				k += 1;
			}
		}
		if (code == 2) {
			data = 0;
			for (j = 1; j <= 4; j += 1) {
				data = (((usqInt) data << 8)) | (ba[i]);
				i += 1;
			}
			for (j = 1; j <= n; j += 1) {
				bm[k] = data;
				k += 1;
			}
		}
		if (code == 3) {
			for (m = 1; m <= n; m += 1) {
				data = 0;
				for (j = 1; j <= 4; j += 1) {
					data = (((usqInt) data << 8)) | (ba[i]);
					i += 1;
				}
				bm[k] = data;
				k += 1;
			}
		}
	}
	pop(methodArgumentCount(interpreterProxy->interpreterState), interpreterProxy->interpreterState);
	return 0;
}


/*	ByteString (class) findFirstInString: aString inSet: inclusionMap
	startingAt: start */

	/* MiscPrimitivePlugin>>#primitiveFindFirstInString */
EXPORT(sqInt)
primitiveFindFirstInString(void)
{
    unsigned char *aString;
    sqInt aStringOop;
    sqInt i;
    unsigned char *inclusionMap;
    sqInt inclusionMapOop;
    sqInt stringSize;

	aStringOop = stackValue(2, interpreterProxy->interpreterState);
	if (!(isBytes(aStringOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	inclusionMapOop = stackValue(1, interpreterProxy->interpreterState);
	if (!(isBytes(inclusionMapOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	i = stackIntegerValue(0, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}

	/* Convert to 0-based index. */
	i -= 1;
	if (i < 0) {
		return primitiveFailFor(PrimErrBadIndex, interpreterProxy->interpreterState);
	}
	inclusionMap = firstIndexableField(inclusionMapOop, interpreterProxy->interpreterState);
	if ((sizeOfSTArrayFromCPrimitive(inclusionMap, interpreterProxy->interpreterState)) != 256) {
		return methodReturnInteger(0, interpreterProxy->interpreterState);
	}
	aString = firstIndexableField(aStringOop, interpreterProxy->interpreterState);
	stringSize = sizeOfSTArrayFromCPrimitive(aString, interpreterProxy->interpreterState);
	while ((i < stringSize)
	 && ((inclusionMap[aString[i]]) == 0)) {
		i += 1;
	}
	methodReturnInteger((i >= stringSize
		? 0
		: i + 1), interpreterProxy->interpreterState);
	return 0;
}


/*	ByteString findSubstring: key in: body startingAt: start matchTable:
	matchTable 
 */

	/* MiscPrimitivePlugin>>#primitiveFindSubstring */
EXPORT(sqInt)
primitiveFindSubstring(void)
{
    unsigned char *body;
    sqInt bodyOop;
    sqInt index;
    unsigned char *key;
    sqInt keyOop;
    sqInt keySize;
    unsigned char *matchTable;
    sqInt matchTableOop;
    sqInt start;
    sqInt startIndex;
    sqInt startIndexLimiT;

	keyOop = stackValue(3, interpreterProxy->interpreterState);
	if (!(isBytes(keyOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	bodyOop = stackValue(2, interpreterProxy->interpreterState);
	if (!(isBytes(bodyOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	start = stackIntegerValue(1, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	matchTableOop = stackValue(0, interpreterProxy->interpreterState);
	if (!(isBytes(matchTableOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	matchTable = firstIndexableField(matchTableOop, interpreterProxy->interpreterState);
	if ((sizeOfSTArrayFromCPrimitive(matchTable, interpreterProxy->interpreterState)) < 256) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	key = firstIndexableField(keyOop, interpreterProxy->interpreterState);
	if (((keySize = sizeOfSTArrayFromCPrimitive(key, interpreterProxy->interpreterState))) > 0) {

		/* adjust for zero relative indexes */
		keySize -= 1;

		/* adjust for zero relative indexes */
		start = (((start - 1) < 0) ? 0 : (start - 1));
		body = firstIndexableField(bodyOop, interpreterProxy->interpreterState);
		for (startIndex = start, startIndexLimiT = (((sizeOfSTArrayFromCPrimitive(body, interpreterProxy->interpreterState)) - 1) - keySize); startIndex <= startIndexLimiT; startIndex += 1) {
			index = 0;
			while ((matchTable[body[startIndex + index]]) == (matchTable[key[index]])) {
				if (index == keySize) {
					return methodReturnInteger(startIndex + 1, interpreterProxy->interpreterState);
				}
				index += 1;
			}
		}
	}
	return methodReturnInteger(0, interpreterProxy->interpreterState);
}


/*	ByteString indexOfAscii: anInteger inString: aString startingAt: start */

	/* MiscPrimitivePlugin>>#primitiveIndexOfAsciiInString */
EXPORT(sqInt)
primitiveIndexOfAsciiInString(void)
{
    sqInt anInteger;
    unsigned char *aString;
    sqInt aStringOop;
    sqInt pos;
    sqInt start;
    sqInt stringSize;

	anInteger = stackIntegerValue(2, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	aStringOop = stackValue(1, interpreterProxy->interpreterState);
	if (!(isBytes(aStringOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	start = stackIntegerValue(0, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	if (!(start >= 1)) {
		return primitiveFailFor(PrimErrBadIndex, interpreterProxy->interpreterState);
	}
	aString = firstIndexableField(aStringOop, interpreterProxy->interpreterState);
	stringSize = sizeOfSTArrayFromCPrimitive(aString, interpreterProxy->interpreterState);
	for (pos = (start - 1); pos < stringSize; pos += 1) {
		if ((aString[pos]) == anInteger) {
			return methodReturnInteger(pos + 1, interpreterProxy->interpreterState);
		}
	}
	return methodReturnInteger(0, interpreterProxy->interpreterState);
}


/*	ByteArray (class) hashBytes: aByteArray startingWith: speciesHash */

	/* MiscPrimitivePlugin>>#primitiveStringHash */
EXPORT(sqInt)
primitiveStringHash(void)
{
    unsigned char *aByteArray;
    sqInt byteArrayOop;
    unsigned int hash;
    sqInt pos;
    sqInt posLimiT;

	hash = stackIntegerValue(0, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	byteArrayOop = stackValue(1, interpreterProxy->interpreterState);
	if (!(isBytes(byteArrayOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	aByteArray = firstIndexableField(byteArrayOop, interpreterProxy->interpreterState);
	for (pos = 0, posLimiT = ((sizeOfSTArrayFromCPrimitive(aByteArray, interpreterProxy->interpreterState)) - 1); pos <= posLimiT; pos += 1) {
		hash = (hash + (aByteArray[pos])) * 1664525;
	}
	methodReturnInteger(hash & 0xFFFFFFF, interpreterProxy->interpreterState);
	return 0;
}


/*	ByteString (class) translate: aString from: start to: stop table: table */

	/* MiscPrimitivePlugin>>#primitiveTranslateStringWithTable */
EXPORT(sqInt)
primitiveTranslateStringWithTable(void)
{
    unsigned char *aString;
    sqInt aStringOop;
    sqInt i;
    sqInt start;
    sqInt stop;
    unsigned char *table;
    sqInt tableOop;

	aStringOop = stackValue(3, interpreterProxy->interpreterState);
	if (!(isBytes(aStringOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	if (isOopImmutable(aStringOop, interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrNoModification, interpreterProxy->interpreterState);
	}
	start = stackIntegerValue(2, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	stop = stackIntegerValue(1, interpreterProxy->interpreterState);
	if (failed(interpreterProxy->interpreterState)) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	tableOop = stackValue(0, interpreterProxy->interpreterState);
	if (!(isBytes(tableOop, interpreterProxy->interpreterState))) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	aString = firstIndexableField(aStringOop, interpreterProxy->interpreterState);
	if (!((start >= 1)
		 && (stop <= (sizeOfSTArrayFromCPrimitive(aString, interpreterProxy->interpreterState))))) {
		return primitiveFailFor(PrimErrBadIndex, interpreterProxy->interpreterState);
	}
	table = firstIndexableField(tableOop, interpreterProxy->interpreterState);
	if ((sizeOfSTArrayFromCPrimitive(table, interpreterProxy->interpreterState)) < 256) {
		return primitiveFailFor(PrimErrBadArgument, interpreterProxy->interpreterState);
	}
	for (i = (start - 1); i < stop; i += 1) {
		aString[i] = (table[aString[i]]);
	}
	methodReturnReceiver(interpreterProxy->interpreterState);
	return 0;
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
		arrayValueOf = interpreterProxy->arrayValueOf;
		byteSizeOf = interpreterProxy->byteSizeOf;
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		isBytes = interpreterProxy->isBytes;
#if IMMUTABILITY
		isOopImmutable = interpreterProxy->isOopImmutable;
#else
#if !defined(isOopImmutable)
		isOopImmutable = 0;
#endif
#endif
		methodArgumentCount = interpreterProxy->methodArgumentCount;
		methodReturnInteger = interpreterProxy->methodReturnInteger;
		methodReturnReceiver = interpreterProxy->methodReturnReceiver;
		pop = interpreterProxy->pop;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
		sizeOfSTArrayFromCPrimitive = interpreterProxy->sizeOfSTArrayFromCPrimitive;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "MiscPrimitivePlugin";
void* MiscPrimitivePlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "primitiveCompareString\000\002", (void*)primitiveCompareString},
	{(void*)_m, "primitiveCompressToByteArray\000\377", (void*)primitiveCompressToByteArray},
	{(void*)_m, "primitiveConvert8BitSigned\000\002", (void*)primitiveConvert8BitSigned},
	{(void*)_m, "primitiveDecompressFromByteArray\000\000", (void*)primitiveDecompressFromByteArray},
	{(void*)_m, "primitiveFindFirstInString\000\002", (void*)primitiveFindFirstInString},
	{(void*)_m, "primitiveFindSubstring\000\002", (void*)primitiveFindSubstring},
	{(void*)_m, "primitiveIndexOfAsciiInString\000\002", (void*)primitiveIndexOfAsciiInString},
	{(void*)_m, "primitiveStringHash\000\001", (void*)primitiveStringHash},
	{(void*)_m, "primitiveTranslateStringWithTable\000\001", (void*)primitiveTranslateStringWithTable},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

EXPORT(signed char) primitiveCompareStringAccessorDepth = 2;
EXPORT(signed char) primitiveConvert8BitSignedAccessorDepth = 2;
EXPORT(signed char) primitiveDecompressFromByteArrayAccessorDepth = 0;
EXPORT(signed char) primitiveFindFirstInStringAccessorDepth = 2;
EXPORT(signed char) primitiveFindSubstringAccessorDepth = 2;
EXPORT(signed char) primitiveIndexOfAsciiInStringAccessorDepth = 2;
EXPORT(signed char) primitiveStringHashAccessorDepth = 1;
EXPORT(signed char) primitiveTranslateStringWithTableAccessorDepth = 1;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
