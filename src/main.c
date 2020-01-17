#include <stdio.h>
#include <stdlib.h>

#include <pharoClient.h>
#include <pharo.h>
#include <sys/queue.h>

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


extern void setMyCurrentThread(pthread_t thread, size_t index);
extern void setNumberOfImage (int numberImages);
extern void initializeAllGlobalsStruct(int numberImages);
extern pthread_t * getThreadsID(void);

int main(int argc, char* argv[]){

	VM_OVERALL_PARAMETERS parameters;

	parseArguments(argc, argv, &parameters);

	//logInfo("Opening Image: %s\n", parameters.imageFile);

	//This initialization is required because it makes awful, awful, awful code to calculate
	//the location of the machine code.
	//Luckily, it can be cached.
	osCogStackPageHeadroom();

	int numberOfImage = parameters.numberOfImage;
	initializeAllGlobalsStruct(numberOfImage);

	setMyCurrentThread(pthread_self(), 0);
	runThread(&parameters.vmparameters[0]);
	
	pthread_t * thread_id = getThreadsID();

	int * threadReturn; 

	for(int i = 0; i < 	getNumberOfImage(); i++){
		pthread_join(thread_id[i], &threadReturn);
		logInfo("Thread %d returned with: %d", i, *threadReturn);
	}
}

void printVersion(){
	printf("%s\n", getVMVersion());
	printf("Built from: %s\n", getSourceVersion());
}
