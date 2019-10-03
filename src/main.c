#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <pharoClient.h>
#include <pharo.h>

#define MAX_THREADS 1

int loadAndExecuteVM(VM_PARAMETERS* parameters){
	if(!initPharoVM(parameters->imageFile, parameters->vmParams, parameters->vmParamsCount, parameters->imageParams, parameters->imageParamsCount)){
		logError("Error opening image file: %s\n", parameters->imageFile);
		exit(-1);
	}
	runInterpreter();
}

int runThread(void* parameters){
	loadAndExecuteVM((VM_PARAMETERS*) parameters);
}


int main(int argc, char* argv[]){
    WORD   dwThreadIdArray;
	HANDLE  hThreadArray[MAX_THREADS];

	VM_PARAMETERS* parameters;
	char buffer[4096+1];

	parameters = (VM_PARAMETERS*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
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
	//osCogStackPageHeadroom();

	hThreadArray[0] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            runThread,       // thread function name
            parameters,          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray);

	if (hThreadArray[0] == NULL) 
        {
          // ErrorHandler(TEXT("CreateThread"));
           ExitProcess(3);
        }

	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	CloseHandle(hThreadArray[0]);
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
