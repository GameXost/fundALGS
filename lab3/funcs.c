#include <stdbool.h>
#include "additional.h"
#include <math.h>


int for_m(int *nums, bool *res){

	if (nums[1] == 0 || nums[0] == 0){
		return INVALID_NUMBER_INPUT;
	}
	if (nums[0] % nums[1] == 0){
		*res = true;
		return OK;
	}
	*res = false;
	return OK;
}

float max(const float a,const float b, const float e){
	if (a - b > e){
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
	if ((a + b <= e + c || a + c <= e + b || b + c <= e + a)){
		*res = false;
		return OK; 
	}
	float maxFloat = max(a, max(b, c, e), e);
	float sumSquare = a * a + b * b + c * c - maxFloat * maxFloat;
	if ( fabs(maxFloat * maxFloat - sumSquare) < e ) {
		*res = true;
		return OK;
	} 
	*res = false;
	return OK;
}


int for_q(float a, float b, float c, float e, float res[6][2], int *cnt){
	bool isDuplicate = false;
	float disc = b * b - 4 * a * c;
	
	if(fabs(a) < e){
		return OK;
	}
	if (disc < -e){
		return OK;
	} else if (fabs(disc) < e){
		float x = -b / (2 * a);
		if (fabs(x) < e){
			x = 0.0;
		}
		//check for duplicates
		for(int prev = 0; prev < *cnt; prev++ ){
			if (isnan(res[prev][1]) && fabs(res[prev][0] - x) < e){
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate){
			res[*cnt][0] = x;
			res[*cnt][1] = NAN;
			(*cnt)++;
		}
	} else {
		float x1 = (-b + sqrt(disc)) / (2 * a);
		float x2 = (-b - sqrt(disc)) / (2 * a);
		if (fabs(x1) < e) {
			x1 = 0.0;
		}
		if (fabs(x2) < e){
			x2 = 0.0;
		}

		//check for duplicates
		for(int prev = 0; prev < *cnt; prev++){
			if ((fabs(res[prev][0] - x1) < e && fabs(res[prev][1] - x2) < e) || 
				(fabs(res[prev][0] - x2) < e && fabs(res[prev][1] - x1) < e)){
					isDuplicate = true;
					break;
			}
		}
		if (!isDuplicate){
			res[*cnt][0] = x1;
			res[*cnt][1] = x2;
			(*cnt)++;
		}
	}
	return OK;
}


int for_qq(float *nums, float res[6][2], int *cnt){
	float e = nums[0];
	if (e < 0) {
		return INVALID_NUMBER_INPUT;
	}
	float a = nums[1];
	float b = nums[2];
	float c = nums[3];
	
	float arrayOne[3] = {a, b, c};
	float arrayTwo[3] = {c, b, a};
	for (int i = 0; i < 3; i++){
		float a1 = arrayOne[(0 + i) % 3];
		float b1 = arrayOne[(1 + i) % 3];
		float c1 = arrayOne[(2 + i) % 3];

		for_q(a1, b1, c1, e, res, cnt);


		float a2 = arrayTwo[(0+i) % 3];
		float b2 = arrayTwo[(1 + i) % 3];
		float c2 = arrayTwo[(2 + i) % 3];

		for_q(a2, b2, c2, e, res, cnt);

	}
	return OK;

}
