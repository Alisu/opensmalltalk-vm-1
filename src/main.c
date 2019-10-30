#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include <pharoClient.h>
#include <pharo.h>


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

int main(int argc, char* argv[]){

	VM_PARAMETERS parameters;

	parseArguments(argc, argv, &parameters);

	logInfo("Opening Image: %s\n", parameters.imageFile);

	//This initialization is required because it makes awful, awful, awful code to calculate
	//the location of the machine code.
	//Luckily, it can be cached.
	osCogStackPageHeadroom();

	pthread_attr_t tattr;

	pthread_attr_init(&tattr);

	pthread_t thread_id[2];

	size_t size;
	pthread_attr_getstacksize(&tattr, &size);

	printf("%ld\n", size);

    if(pthread_attr_setstacksize(&tattr, size*4)){
		perror("Thread attr");
    }

	for(int i = 0; i < 2; i++){
		if(pthread_create(&thread_id[i], &tattr, runThread, &parameters)){
			perror("Thread creation");
		}
		setMyCurrentThread(thread_id[i], i);
	}

	for(int i = 0; i < 2; i++){
		pthread_join(thread_id[i], NULL);
	}
}

void printVersion(){
	printf("%s\n", getVMVersion());
	printf("Built from: %s\n", getSourceVersion());
}
