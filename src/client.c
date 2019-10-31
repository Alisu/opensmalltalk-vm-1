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

struct isParametersSet{
    size_t initialized;
    pthread_mutex_t mutex;
};

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
    /*
    TODO handle correctly this function for threaded interpreter
    
    static struct isParametersSet ips = {0, PTHREAD_MUTEX_INITIALIZER};
    if(pthread_mutex_lock(&ips.mutex) == 0){
        if(ips.initialized==0){*/
	        setPharoCommandLineParameters(vmParams, vmParamCount, imageParams, imageParamCount);
            /*ips.initialized++;
        }
    }
    pthread_mutex_unlock(&(ips.mutex));*/
	return loadPharoImage(image);
}

EXPORT(void) runInterpreter(){
	interpret();
}

int loadPharoImage(char* fileName){
    size_t imageSize = 0;
    FILE* imageFile = NULL;

    /* Open the image file. */
    imageFile = fopen(fileName, "rb");
    if(!imageFile){
    	perror("Opening Image");
        return false;
    }

    /* Get the size of the image file*/
    fseek(imageFile, 0, SEEK_END);
    imageSize = ftell(imageFile);
    fseek(imageFile, 0, SEEK_SET);

    readImageFromFileHeapSizeStartingAt(imageFile, 0, 0);
    fclose(imageFile);

    setImageName(fileName);

    return true;
}
