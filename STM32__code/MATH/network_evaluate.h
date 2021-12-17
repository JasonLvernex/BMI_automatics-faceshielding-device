// network_evaluate.h
#ifndef __NETWORK_EVALUATE_H
#define __NETWORK_EVALUATE_H


#pragma once

#include <math.h>

/*
 * since the network outputs thrust on each motor,
 * we need to define a struct which stores the values
*/
typedef struct control_t_n {
	float thrust_0;
	float thrust_1;
	float thrust_2;
	float thrust_3;
} control_t_n;

float networkEvaluate(const float* state_array);

#endif

