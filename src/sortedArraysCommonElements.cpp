 /*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int len(char *str){
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

int validtionOfDate1(char* dob1){
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

int whoIsOlder1(char* dob1, char* dob2, int low, int high){
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

int isOlder1(char *dob1, char *dob2) {
	int l1 = len(dob1);
	int l2 = len(dob2);

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
		if (validtionOfDate1(dob1) == -1 || validtionOfDate1(dob2) == -1){
			return -1;
		}
		else{
			//After validation
			int res1 = whoIsOlder1(dob1, dob2, 6, 10);
			if (res1 == 0){
				int res2 = whoIsOlder1(dob1, dob2, 3, 5);
				if (res2 == 0){
					int res3 = whoIsOlder1(dob1, dob2, 0, 2);
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

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A != NULL && B != NULL){
		struct transaction* res = (struct transaction*)malloc(sizeof(struct transaction) * 3);
		int i, j, ptr = 0, temp = 0;
		for (i = 0; i < ALen; i++){
			for (j = 0; j < BLen; j++){
				if (isOlder1(A[i].date, B[j].date) == 0){
					res[i] = A[i];
					temp = 1;
				}
				else if (isOlder1(A[i].date, B[i].date) == 1){
					break;
				}
			}
		}
		if (temp == 0){
			return NULL;
		}
		return res;

	}
	return NULL;
}