#include "additional.h"
#include <stdio.h>
#include <stdlib.h>

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
				if (res[i][1] == 0){
					printf("%f\n", res[i][0]);
					continue;
				}
				printf("%f %f\n", res[i][0], res[i][1]);
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
				printf("yoy it's true, %d divides by %d\n", (int)nums[0], (int)nums[1]);
				break;
			} else {
				printf("no\n");
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
				printf("yoy 3 rest numbers mught be a lengths of a prymopug triangle %f, %f, %f \n", nums[1], nums[2], nums[3]);
				break;
			} else{
				printf("no\n");
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