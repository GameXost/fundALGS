#include "additional.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//TODO: изменить циклы в Q, сравнение чисел 
int main(int argc, char *argv[]) {

	char flag;
	int cnt = 0;

	ReturnCode status = validate(argc, argv, &flag);
	if (status != OK) {
		handleError(status);
		return status;
	}

	float res[6][2];
	bool resFlag;
	switch (flag){
		case 'q':{

			float *nums = (float*)malloc(sizeof(float) * (argc - 2));
			if (nums == NULL) {
				handleError(MEMORY_ALLOCATION_ERROR);
				return MEMORY_ALLOCATION_ERROR;
			}
			for (int i = 0; i < argc - 2; i++){
				ReturnCode status = parseFloat(argv[i+2], &nums[i]);
				if (status != OK){
					free(nums);
					handleError(status);
					return INVALID_NUMBER_INPUT;
				}
			}
			status = for_qq(nums, res, &cnt);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}

			for (int i = 0; i < cnt; i++){
				if (isnan(res[i][1])){
					printf("here only one solution: %f\n", res[i][0]);
					continue;
				}
				printf("solutions: %f %f\n", res[i][0], res[i][1]);
			}

			if (cnt == 0){
				printf("zero solutions found\n");
			}
			free(nums);
			break;
		}


		case 'm':{
			int *nums = (int*)malloc(sizeof(int) * (argc - 2));
			if (nums == NULL) {
				handleError(MEMORY_ALLOCATION_ERROR);
				return MEMORY_ALLOCATION_ERROR;
			}
			for (int i = 0; i < argc - 2; i++){
				ReturnCode status = parseInt(argv[i+2], &nums[i]);
				if (status != OK){
					free(nums);
					handleError(status);
					return INVALID_NUMBER_INPUT;
				}
			}
			status = for_m(nums, &resFlag);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}

			if (resFlag == true){
				printf("yoy it's true, %d is divided by %d\n", (int)nums[0], (int)nums[1]);
			} else {
				printf("no, %d cant be devided by %d\n", (int)nums[0], (int)nums[1]);
			}
			free(nums);
			break;
		}

		
		case 't':{
			float *nums = (float*)malloc(sizeof(float) * (argc - 2));
			if (nums == NULL) {
				handleError(MEMORY_ALLOCATION_ERROR);
				return MEMORY_ALLOCATION_ERROR;
			}
			for (int i = 0; i < argc - 2; i++){
				ReturnCode status = parseFloat(argv[i+2], &nums[i]);
				if (status != OK){
					free(nums);\
					handleError(status);
					return INVALID_NUMBER_INPUT;
				}
			}
			status = for_t(nums, &resFlag);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}
			if (resFlag == true){
				printf("yoy 3 numbers:  %f, %f, %f might be of a rectangular triangle\n", nums[1], nums[2], nums[3]);
			} else{
				printf("no, numbers %f, %f, %f cant be a rect triangle\n", nums[1], nums[2], nums[3]);
			}
			free(nums);
			break;
		}
		default:
			handleError(INVALID_FLAG_INPUT);
			return INVALID_FLAG_INPUT;
	}
	return OK;
}