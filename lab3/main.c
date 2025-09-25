#include "additional.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

	float *nums = malloc(sizeof(float) * (argc - 2));
	if (nums == NULL) {
		handleError(MEMORY_ALLOCATION_ERROR);
		return MEMORY_ALLOCATION_ERROR;
	}

	char flag;
	int cnt = 0;

	ReturnCode status = validate(argc, argv, &flag, nums);
	if (status != OK) {
		handleError(status);
		free(nums);
		return status;
	}

	float res[6][2];
	bool resFlag;
	switch (flag){
		case 'q':
			status = for_q(nums, res, &cnt);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}

			for (int i = 0; i < cnt; i++){
				if (isnan(res[i][1])){
					printf("here only one solution: %0.3f\n", res[i][0]);
					continue;
				}
				printf("solutions: %0.3f %0.3f\n", res[i][0], res[i][1]);
			}

			if (cnt == 0){
				printf("zero solutions found\n");
			}

			break;
			
		case 'm':

			status = for_m(nums, &resFlag);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}

			if (resFlag == true){
				printf("yoy it's true, %d is divided by %d\n", (int)nums[0], (int)nums[1]);
				break;
			} else {
				printf("no, %d cant be devided by %d\n", (int)nums[0], (int)nums[1]);
				break;
			}
		case 't':
			status = for_t(nums, &resFlag);
			if (status != OK){
				handleError(status);
				free(nums);
				return status;
			}
			if (resFlag == true){
				printf("yoy 3 numbers:  %.3f, %.3f, %.3f might be of a rectangular triangle\n", nums[1], nums[2], nums[3]);
				break;
			} else{
				printf("no, numbers %.3f, %.3f, %.3f cant be a rect triangle\n", nums[1], nums[2], nums[3]);
				break;
			}
		default:
			handleError(INVALID_FLAG_INPUT);
			free(nums);
			return INVALID_FLAG_INPUT;
	}
	free(nums);
	return OK;
}