/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int len2(char *str){
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

int validtionOfDate2(char* dob1){
	int y1 = (dob1[9] - '0') + ((dob1[8] - '0') * 10);
	if (dob1[3] == '1' && dob1[4] >'2'){
		return -1;
	}
	else{
		if (dob1[0] >= '3'){
			return -1;
		}
		else if ((y1 % 4 == 0) && (dob1[3] == '0' && dob1[4] == '2')){
			if (dob1[0] == '3'){
				return -1;
			}
		}
		else if ((y1 % 4 != 0) && (dob1[3] == '0' && dob1[4] == '2')){
			if ((dob1[0] == '3') || (dob1[0] == '2' && dob1[1] == '9')){
				return -1;
			}
		}
		else{
			if (dob1[3] == '0'){
				if (dob1[4] == '1' || dob1[4] == '3' || dob1[4] == '5' || dob1[4] == '7' || dob1[4] == '8'){
					if (dob1[0] == '3' && dob1[1] >= '2'){
						return -1;
					}
				}
				else{
					if (dob1[0] == '3' && dob1[1] >= '1'){
						return -1;
					}
				}
			}
			else{
				if (dob1[4] == '1'){
					if (dob1[0] == '3' && dob1[1] >= '1'){
						return -1;
					}
				}
				else{
					if (dob1[0] == '3' && dob1[1] >= '2'){
						return -1;
					}
				}
			}
		}
	}
	return 1;
}

int whoIsOlder2(char* dob1, char* dob2, int low, int high){
	int i;
	for (i = low; i < high; i++){
		if (dob1[i] < dob2[i]){
			return 1;
		}
		else if (dob1[i] > dob2[i]){
			return 2;
		}
	}
	return 0;
}

int isOlder2(char *dob1, char *dob2) {
	int l1 = len2(dob1);
	int l2 = len2(dob2);

	//validation 1
	if (l1 == 10 && l2 == 10){
		//validation2
		for (int i = 0; i < 10; i++){
			if (i != 2 && i != 5){
				if ((dob1[i] >= '0' && dob1[i] <= '9') && (dob2[i] >= '0' && dob2[i] <= '9')){
					//24-07-2000
					continue;
				}
				return -1;

			}
		}

		//validation3
		if (validtionOfDate2(dob1) == -1 || validtionOfDate2(dob2) == -1){
			return -1;
		}
		else{
			//After validation
			int res1 = whoIsOlder2(dob1, dob2, 6, 10);
			if (res1 == 0){
				int res2 = whoIsOlder2(dob1, dob2, 3, 5);
				if (res2 == 0){
					int res3 = whoIsOlder2(dob1, dob2, 0, 2);
					if (res3 == 0){
						return 0;
					}
					return res3;
				}
				return res2;
			}
			return res1;
		}
	}
	else{
		return -1;
	}
	return 0;
}

struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A != NULL && B != NULL){
		struct transaction* res = (struct transaction*)malloc(sizeof(struct transaction) * (ALen+BLen));
		int i = 0, j = 0, ptr = 0, temp = 0;
		while ((i < ALen) && (j<BLen)){
			if (isOlder2(A[i].date, B[j].date) == 1){
				res[ptr++] = A[i];
				i++;
			}
			else{
				res[ptr++] = B[j];
				j++;
			}
		}
		if (i == ALen){
			for (int k = j; k < BLen; k++){
				res[ptr++] = B[k];
			}
		}
		else if (j == BLen){
			for (int k = i; k < ALen; k++){
				res[ptr++] = A[k];
			}
		}
		return res;
	}
	return NULL;
}