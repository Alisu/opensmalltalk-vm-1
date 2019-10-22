#include "pharo.h"
#include "pharoClient.h"
#include <pthread.h>

#if defined(__GNUC__) && ( defined(i386) || defined(__i386) || defined(__i386__)  \
			|| defined(i486) || defined(__i486) || defined (__i486__) \
			|| defined(intel) || defined(x86) || defined(i86pc) )
static void fldcw(unsigned int cw)
{
    __asm__("fldcw %0" :: "m"(cw));
}
#else
#   define fldcw(cw)
#endif

#if defined(__GNUC__) && ( defined(ppc) || defined(__ppc) || defined(__ppc__)  \
			|| defined(POWERPC) || defined(__POWERPC) || defined (__POWERPC__) )
void mtfsfi(unsigned long long fpscr)
{
    __asm__("lfd   f0, %0" :: "m"(fpscr));
    __asm__("mtfsf 0xff, f0");
}
#else
#   define mtfsfi(fpscr)
#endif

int loadPharoImage(char* fileName);

EXPORT(int) initPharoVM(char* image, char** vmParams, int vmParamCount, char** imageParams, int imageParamCount){
	initGlobalStructure();

	//Unix Initialization specific
	fldcw(0x12bf);	/* signed infinity, round to nearest, REAL8, disable intrs, disable signals */
    mtfsfi(0);		/* disable signals, IEEE mode, round to nearest */


    ioInitTime();

    ioVMThread = ioCurrentOSThread();
	ioInitExternalSemaphores();

	aioInit();

	setPharoCommandLineParameters(vmParams, vmParamCount, imageParams, imageParamCount);

	return loadPharoImage(image);
}

EXPORT(void) runInterpreter(){
	interpret();
}

 struct image_size{
    size_t imageSize;
    pthread_mutex_t mutex;
};

int loadPharoImage(char* fileName){
    static struct image_size is = {0, PTHREAD_MUTEX_INITIALIZER};

    if(pthread_mutex_lock(&is.mutex) == 0){
        FILE* imageFile = NULL;
        size_t debugVar1 = 0;

        /* Open the image file. */
        imageFile = fopen(fileName, "rb");
         if(!imageFile){
            perror("Opening Image");
            return false;
        }

        if(is.imageSize == 0){

            /* Get the size of the image file*/
            fseek(imageFile, 0, SEEK_END);
             is.imageSize = ftell(imageFile);
            fseek(imageFile, 0, SEEK_SET);

            debugVar1 = readImageFromFileHeapSizeStartingAt(imageFile, 0, 0, 0);
            printf("Allocation: %d \n",debugVar1);
            fclose(imageFile);
        }
        else{
             /* We try to load the same image another time after the first one here */
            size_t old_image_size = is.imageSize;
            debugVar1 =readImageFromFileHeapSizeStartingAt(imageFile, 0, 0, is.imageSize);
            printf("Allocation: %d \n",debugVar1);
            fclose(imageFile);
        }
    }
   pthread_mutex_unlock(&(is.mutex));
   
    char* fullImageName = alloca(FILENAME_MAX);
	fullImageName = getFullPath(fileName, fullImageName, FILENAME_MAX);

    setImageName(fullImageName);

    return true;
}
