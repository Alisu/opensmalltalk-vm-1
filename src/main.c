#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pharoClient.h>
#include <pharo.h>

int runThread(void* p){

	VM_PARAMETERS *parameters = (VM_PARAMETERS*)p;

	if(!initPharoVM(parameters->imageFile, parameters->vmParams, parameters->vmParamsCount, parameters->imageParams, parameters->imageParamsCount)){
		logError("Error opening image file: %s\n", parameters->imageFile);
		exit(-1);
	}
	//runInterpreter();
}

int main(int argc, char* argv[], char** env){

	installErrorHandlers();

	setProcessArguments(argc, argv);
	setProcessEnvironmentVector(env);

	VM_PARAMETERS parameters;
	char buffer[4096+1];

	parseArguments(argc, argv, &parameters);

	logInfo("Opening Image: %s\n", parameters.imageFile);

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

	pthread_attr_t tattr [2];
	pthread_t thread_id [2];

	 for (int i= 0; i<2; i++){
		pthread_attr_init(&tattr);

		size_t size;
		pthread_attr_getstacksize(&tattr[i], &size);

		//printf("%ld\n", size);

   	 	if(pthread_attr_setstacksize(&tattr[i], size*4)){
			perror("Thread attr");
   	 	}

		if(pthread_create(&thread_id[i], &tattr[i], runThread, &parameters)){
			perror("Thread creation");
		}

 	}
	for (i = 0; i < 2; i++)
   	{
      	pthread_join (thread_id [i], NULL);
   	}
}

void printVersion(){
	printf("%s\n", getVMVersion());
	printf("Built from: %s\n", getSourceVersion());
}
