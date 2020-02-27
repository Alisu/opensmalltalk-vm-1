#pragma once

#include "parameters.h"

int initPharoVM(char* image, char** vmParams, int vmParamCount, char** imageParams, int imageParamCount, struct foo * self);
void runInterpreter(struct foo * self);

