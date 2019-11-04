#include "pharo.h"
#include "parameters.h"
#include <getopt.h>
#include <unistd.h>
#include "debug.h"

void printVersion();
void printUsage();

int endsWithImage( char *string )
{
  string = strrchr(string, '.');

  if( string != NULL )
    return( strcmp(string, ".image") );

  return( -1 );
}

int * findImageNameIndex(int argc, char* argv[], VM_OVERALL_PARAMETERS* parameters){

	int * result = malloc(sizeof(int) * 2);
	int j= 0;
	//The first parameters is the executable name
	for(int i=1; i < argc; i ++){
		if(strcmp(argv[i], "--") == 0 || endsWithImage(argv[i])==0){
			if(j==2){
				//pritnf("No more than 2 images is supported at the moment: \n");
				break;
			}
			result[j]= i;
			j++;
		}
	}

	// I didn't find any images.
	if (j==0){
		result[0]= argc;
	}

	parameters->numberOfImage = j;

	return result;
}

void splitVMAndImageParameters(int argc, char* argv[], VM_OVERALL_PARAMETERS* parameters){

	int* imageNameIndex = findImageNameIndex(argc, argv, parameters);
	int numberParametersVM = imageNameIndex[0];
	int numberImageParameters = argc - imageNameIndex[parameters->numberOfImage-1] - 1;

 	if(numberImageParameters < 0)
		numberImageParameters = 0;
	
	parameters->vmparameters = (VM_PARAMETERS *) malloc(sizeof(VM_PARAMETERS)*parameters->numberOfImage);
	
	//We get the image file name
	for(int i = 0; i<parameters->numberOfImage; i++){
		if(imageNameIndex[i] == argc || strcmp("--", argv[imageNameIndex[i]]) == 0){
			parameters->vmparameters[i].imageFile = DEFAULT_IMAGE_NAME;
			parameters->vmparameters[i].isDefaultImage = true;
			parameters->vmparameters[i].hasBeenSelectedByUser = false;
		}else{
			parameters->vmparameters[i].imageFile = argv[imageNameIndex[i]];
			parameters->vmparameters[i].isDefaultImage = false;
			parameters->vmparameters[i].hasBeenSelectedByUser = false;
		}
	

		//Copy image parameters
		parameters->vmparameters[i].imageParams = malloc(sizeof(void*) * numberImageParameters);
		parameters->vmparameters[i].imageParamsCount = numberImageParameters;
		for(int j=0; j < numberImageParameters; j++){
			parameters->vmparameters[i].imageParams[j] = argv[imageNameIndex[parameters->numberOfImage-1] + j + 1];
		}

		//Copy vm parameters
		//We have to guarantee that the VM parameters includes --headless
		//As it is checked by the image.

		parameters->vmparameters[i].vmParams = malloc(sizeof(void*) * (numberParametersVM +1));
		parameters->vmparameters[i].vmParamsCount = numberParametersVM + 1;
		for(int j=0; j < numberParametersVM; j++){
			parameters->vmparameters[i].vmParams[j] = argv[j];
		}
		parameters->vmparameters[i].vmParams[numberParametersVM] = "--headless";
	}
}


void logParameters(VM_PARAMETERS* parameters){
	char buffer[4096];

	logDebug("ImageFile: %s", parameters->imageFile);
	logDebug("Is default Image: %d", parameters->isDefaultImage);
	logDebug("Has been selected: %d", parameters->hasBeenSelectedByUser);

	logDebug("vmParamsCount: %d", parameters->vmParamsCount);

	buffer[0] = 0;
	for(int i=0; i < parameters->vmParamsCount; i++){
		strcat(buffer, parameters->vmParams[i]);
		strcat(buffer, " ");
	}

	logDebug("vmParams: %s", buffer);

	logDebug("imageParamsCount: %d", parameters->imageParamsCount);

	buffer[0] = 0;
	for(int i=0; i < parameters->imageParamsCount; i++){
		strcat(buffer, parameters->imageParams[i]);
		strcat(buffer, " ");
	}

	logDebug("imageParams: %s", buffer);
}

int isConsole(){
#if WIN64
	return GetStdHandle(STD_INPUT_HANDLE) != NULL;
#else
	return false;
#endif
}

void processImageFileName(VM_OVERALL_PARAMETERS* parameters){
	for(int i = 0; i<parameters->numberOfImage; i++){
		if(parameters->vmparameters[i].isDefaultImage){
			if(!fileExists(parameters->vmparameters[i].imageFile)){
				if(!openFileDialog("Choose image file", "", "image", &(parameters->vmparameters[i].imageFile), DEFAULT_IMAGE_NAME)){
					printUsage();
					exit(1);
				}

				parameters->vmparameters[i].hasBeenSelectedByUser = true;
			}
		}
		//If there are no parameters, we are next to the launch of the VM, we need to add the interactive flag
		//As we always have two parameters (the --headless)
		if(parameters->vmparameters[i].vmParamsCount == 2 && parameters->vmparameters[i].imageParamsCount == 0 && !isConsole()){
			parameters->vmparameters[i].imageParams = malloc(sizeof(void*));
			parameters->vmparameters[i].imageParamsCount = 1;
			parameters->vmparameters[i].imageParams[0] = "--interactive";
		}
	}
}

void printUsage(){
	printf("Usage: %s [<option>...] [<imageName> [<argument>...]]\n", VM_NAME);
	printf("       %s [<option>...] -- [<argument>...]\n", VM_NAME);
	printf("\n");
	printf("Common <option>s:\n");
	printf("  --help                 print this help message, then exit\n");
	printf("  --headless             run in headless (no window) mode (default: true)\n");
	printf("  --logLevel=<level>     Sets the log level (ERROR, WARN, INFO or DEBUG)\n");
	printf("  --version              print version information, then exit\n");
	printf("\n");
	printf("Notes:\n");
	printf("\n");
	printf("  <imageName> defaults to `Pharo.image'.\n");
	printf("  <argument>s are ignored, but are processed by the Pharo image.\n");
	printf("  Precede <arguments> by `--' to use default image.\n");
}

typedef void (*OPTION_PROCESS_FUNCTION)(char*);

void processLogLevelOption(char* value){

	int intValue = 0;

	intValue = strtol(value, NULL, 10);

	if(intValue == 0){
		printf("Invalid option for logLevel: %s\n", value);
		printUsage();
		exit(1);
	}

	logLevel(intValue);
}

void processHelpOption(char* value){
	printUsage();
	exit(0);
}

void processPrintVersionOption(char* value){
	printVersion();
	exit(0);
}

static struct option long_options[] = {
	{"headless", no_argument, 0,  0 },
	{"help", no_argument, 0,  0 },
	{"logLevel", required_argument, 0, 0},
	{"version", no_argument, 0, 0},
	{0, 0, 0,  0 }
};

static OPTION_PROCESS_FUNCTION optionHandlers[] = {0, processHelpOption, processLogLevelOption, processPrintVersionOption};

void processVMOptions(VM_PARAMETERS* parameters){

	int option_index = 0;
	char r;
	OPTION_PROCESS_FUNCTION processFunction;


	while((r = getopt_long(parameters->vmParamsCount, parameters->vmParams, "", long_options, &option_index))!=-1){
		// We have an invalid option
		if(r == '?'){
			printUsage();
			exit(1);
		}

		if(optionHandlers[option_index])
			optionHandlers[option_index](optarg);
	}
}

void parseArguments(int argc, char* argv[], VM_OVERALL_PARAMETERS* parameters){
	char* fullPath;

	splitVMAndImageParameters(argc, argv, parameters);

	//I get the VM location from the argv[0]
	fullPath = alloca(FILENAME_MAX);
	fullPath = getFullPath(argv[0], fullPath, FILENAME_MAX);
	setVMPath(fullPath);

	processImageFileName(parameters);

	processVMOptions(parameters);

	logParameters(parameters);
}
