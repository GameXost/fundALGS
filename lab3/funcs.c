#include <stdbool.h>
#include "additional.h"
#include <math.h>
#include <stdio.h>

int for_m(float *nums, bool *res){
	if ((int)nums[1] == 0){
		return INVALID_NUMBER_INPUT;
	}
	if ((int)nums[0] % (int)nums[1] == 0){
		*res = true;
		return OK;
	}
	*res = false;
	return OK;
}

float max(float a, float b){
	if (a - b > 0){
		return a;
	}
	return b;
}

int for_t(float *nums, bool *res){
	float e = nums[0];
	float a = nums[1];
	float b = nums[2];
	float c = nums[3];
	if (a <= 0 || b <= 0 || c <= 0 || e < 0) {
		return INVALID_NUMBER_INPUT;
	}
	if ((a + b <= c || a + c <= b || b + c <= a)){
		*res = false;
		return OK; 
	}
	float maxFloat = max(a, max(b, c));
	float sumSquare = a * a + b * b + c * c - maxFloat * maxFloat;
	if ( fabs(maxFloat * maxFloat - sumSquare) < e ) {
		*res = true;
		return OK;
	} 
	*res = false;
	return OK;
}


int for_q(float *nums, float res[6][2], int *cnt){
	float e = nums[0];
	float a = nums[1];
	float b = nums[2];
	float c = nums[3];

	if (e < 0) {
		return INVALID_NUMBER_INPUT;
	}
	for (int i = 1; i <= 3; i ++){
		for (int j = 1; j <= 3; j++){
			if (j == i) {
				continue;
			}
			for(int k = 1; k <= 3; k++){
				if (k == j || k == i){
					continue;
				}
				float a = nums[i];
				float b = nums[j];
				float c = nums[k];
				float disc = b * b - 4 * a * c;
				if(fabs(a) < e){
					continue;
				}
				if (disc < -e){
					continue;
				} else if (fabs(disc) < e){
					float x = -b / (2 * a);
					res[*cnt][0] = x;
					res[*cnt][1] = 0;
					(*cnt)++;
				} else {
					float x1 = (-b + sqrt(disc)) / (2 * a);
					float x2 = (-b - sqrt(disc)) / (2 * a);
					res[*cnt][0] = x1;
					res[*cnt][1] = x2;
					(*cnt)++;
				}
			}
		}
	}
	return OK;
}