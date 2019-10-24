#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pharoClient.h>
#include <pharo.h>
#define MAX_THREADS 2

int runThread(void* p){

	VM_PARAMETERS *parameters = (VM_PARAMETERS*)p;

	if(!initPharoVM(parameters->imageFile, parameters->vmParams, parameters->vmParamsCount, parameters->imageParams, parameters->imageParamsCount)){
		logError("Error opening image file: %s\n", parameters->imageFile);
		exit(-1);
	}
	
	runInterpreter();
}

extern void setMyCurrentThread(DWORD thread, size_t index);

int main(int argc, char* argv[], char** env){

	installErrorHandlers();

	setProcessArguments(argc, argv);
	setProcessEnvironmentVector(env);


	VM_PARAMETERS* parameters;
	char buffer[4096+1];

	// Allocate memory for thread data.
	parameters = (VM_PARAMETERS *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
    sizeof(VM_PARAMETERS));

    if( parameters == NULL )
    {
        // If the array allocation fails, the system is out of memory
        // so there is no point in trying to print an error message.
        // Just terminate execution.
        ExitProcess(2);
    }


	parseArguments(argc, argv, parameters);

	logInfo("Opening Image: %s\n", parameters->imageFile);

	//This initialization is required because it makes awful, awful, awful code to calculate
	//the location of the machine code.
	//Luckily, it can be cached.
	osCogStackPageHeadroom();

	getcwd(buffer, sizeof(buffer));
	logDebug("Working Directory %s", buffer);


	LOG_SIZEOF(int);
	LOG_SIZEOF(long);
	LOG_SIZEOF(long long);
	LOG_SIZEOF(void*);
	LOG_SIZEOF(sqInt);
	LOG_SIZEOF(sqLong);
	LOG_SIZEOF(float);
	LOG_SIZEOF(double);
       
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS]; 

    // Create 2 worker threads.

    for( int i=0; i<MAX_THREADS; i++ )
    {
    	DWORD  dwThread;	
 		hThreadArray[i] = CreateThread( 
            NULL,                   // default security attributes
            4000000,                      // use default stack size  
            runThread,       		// thread function name
            parameters,          	// argument to thread function 
            0,                      // use default creation flags 
            &dwThread);
		setMyCurrentThread(dwThread , i);
		dwThreadIdArray[i]=dwThread;

        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL) 
        {
           //ErrorHandler(TEXT("CreateThread"));
           ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for(int i=0; i<MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
	}
    if(parameters != NULL)
     {
        HeapFree(GetProcessHeap(), 0, parameters);
        parameters = NULL;    // Ensure address is not reused.
    }	
}

void printVersion(){
	printf("%s\n", getVMVersion());
	printf("Built from: %s\n", getSourceVersion());
}
