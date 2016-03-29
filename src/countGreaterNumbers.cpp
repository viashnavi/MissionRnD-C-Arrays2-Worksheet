/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int lengthOfStr(char *str){
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

int validtion_Of_Date(char* dob1){
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

int who_Is_Older(char* dob1, char* dob2, int low, int high){
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

int is_Older(char *dob1, char *dob2) {
	int l1 = lengthOfStr(dob1);
	int l2 = lengthOfStr(dob2);

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
		if (validtion_Of_Date(dob1) == -1 || validtion_Of_Date(dob2) == -1){
			return -1;
		}
		else{
			//After validation
			int res1 = who_Is_Older(dob1, dob2, 6, 10);
			if (res1 == 0){
				int res2 = who_Is_Older(dob1, dob2, 3, 5);
				if (res2 == 0){
					int res3 = who_Is_Older(dob1, dob2, 0, 2);
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


int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
		int i;
		int count = 0;
		for (i = 0; i < len; i++){
			if (is_Older(date,Arr[i].date) == 1){
				count++;
			}
		}
		return count;
}
