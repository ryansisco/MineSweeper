#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

//FUNCTIONS
bool is_pos_int(int);
void goodbye();
void print_data(int, int, int);
void make_hidden_map2(char**, int, int, int);
int make_hidden_map3(char**, int, int, int, int, int);
int make_hidden_map4(char**, int, int, int, int, int);
void menu(char**, char**, int, int, int);
void user_board(char**, char**, int, int, int, int, int, int);
void cout_board(char**, char**, int, int, int);
void new_board(char**, int, int, int);
void gameover(char**, char**);
void main_alt();
void winner_search(char**, char**, int, int, int);
void recursion(char**, int, int, int);





/*********************************************************************************
* Function: main
* Description: runs through functions
* Parameters: int, char*
* Pre-Conditions: 3 positive integers entered with command lines -c -m - r
* Post-Conditions: none
* Line Count: 19
*********************************************************************************/
int main() {
	int rows, columns, mines;
	cout << "How Many Rows?" << endl;
	cin >> rows;
	if (!(is_pos_int(rows))) {
		goodbye();
	}
	cout << "How Many Columns?" << endl;
	cin >> columns;
	if (!(is_pos_int(columns))) {
		goodbye();
	}
	cout << "How Many Mines?" << endl;
	cin >> mines;
	if (!(is_pos_int(mines))) {
		goodbye();
	}

	print_data(rows, mines, columns);
}





/*********************************************************************************
* Function: is_pos_int
* Description: tests for positive integers
* Parameters: int
* Pre-Conditions: none
* Post-Conditions: true or false
* Line Count: 4
*********************************************************************************/
bool is_pos_int(int input) {
	int input1 = input;
	if (input1 > 0) {
		return true;
	}
	return false;
}





/*********************************************************************************
* Function: goodbye
* Description: prints an error and exits
* Parameters: none
* Pre-Conditions: none
* Post-Conditions: none
* Line Count: 3
*********************************************************************************/
void goodbye() {
	cout << "ERROR" << endl;
	cout << "Invalid Option" << endl;
	exit(1);
}





/*********************************************************************************
* Function: print_data
* Description: prints the ammount of rows, columns, and mines
* Parameters: int, int, int
* Pre-Conditions: must be positive integers
* Post-Conditions: none
* Line Count: 18
*********************************************************************************/
void print_data(int rows, int mines, int columns) {
	if (mines > (columns*rows)) {
		cout << "Too Many Mines!!!" << endl;
		goodbye();
	}
	cout << endl;
	cout << "______________" << endl;
	cout << rows << " rows" << endl;
	cout << columns << " columns" << endl;
	cout << mines << " mines" << endl;
	cout << "______________" << endl;
	cout << endl;
	char **myArray = new char*[rows];
	for (int i = 0; i < rows; ++i) {
		myArray[i] = new char[columns];
	}
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int q = 0; q < columns; q++) {
			myArray[i][q] = '0';
		}
	}
	recursion(myArray, rows, columns, mines);

}





/*********************************************************************************
* Function: recursion
* Description: randomly places mines, loops if the same random number is used
* Parameters: char** , int, int, int
* Pre-Conditions: positive integers, must fit inside array
* Post-Conditions: none
* Line Count: 9
*********************************************************************************/
void recursion(char** myArray, int rows, int columns, int mines) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int q = 0; q < columns; q++) {
			if (myArray[i][q] == '*') {
				count++;
			}
		}
	}
	if (count == mines) {
		make_hidden_map2(myArray, rows, columns, mines);
	}
	myArray[rand() % rows][rand() % columns] = '*';
	recursion(myArray, rows, columns, mines);
}





/*********************************************************************************
* Function: make_hidden_map2
* Description: fills the array with numbers in relation to mines
* Parameters: char **, int, int, int
* Pre-Conditions: positive numbers, within range of array
* Post-Conditions: none
* Line Count: 10
*********************************************************************************/
void make_hidden_map2(char** myArray, int rows, int columns, int mines) {
	int num = 0, i = 0, q = 0, num1 = 0, num2 = 0;
	for (i = 0; i < rows; i++) {
		for (q = 0; q < columns; q++) {
			num = 0, num1 = 0, num2 = 0;
			if (myArray[i][q] != '*') {
				num1 = make_hidden_map3(myArray, rows, columns, num, i, q);
				num2 = make_hidden_map4(myArray, rows, columns, num1, i, q);
				char num_check = 48 + num2;
				myArray[i][q] = num_check;
			}
		}
	}

	new_board(myArray, rows, columns, mines);


}





/*********************************************************************************
* Function: make_hidden_mp3
* Description: extension of make_hidden_mp2 in order to meet line limit
* Parameters: char**, int, int, int, int, int
* Pre-Conditions: positive integers, in range of array
* Post-Conditions: num must be a positive integer
* Line Count: 13
*********************************************************************************/
int make_hidden_map3(char** myArray, int rows, int columns, int num, int i, int q) {
	if (i > 0) {
		if ((myArray[i - 1][q] == '*'))
			num++;
	}
	if (i < rows - 1) {
		if (myArray[i + 1][q] == '*')
			num++;
	}
	if (q < columns - 1) {
		if (myArray[i][q + 1] == '*')
			num++;
	}
	if (q > 0) {
		if (myArray[i][q - 1] == '*')
			num++;
	}
	return num;
}





/*********************************************************************************
* Function: make_hidden_mp4
* Description: extension of make_hidden_mp2 in order to meet line limit
* Parameters: char**, int, int, int, int, int
* Pre-Conditions: positive integers, in range of array
* Post-Conditions: num1 must be a positive integer
* Line Count: 13
*********************************************************************************/
int make_hidden_map4(char** myArray, int rows, int columns, int num1, int i, int q) {
	if ((q > 0) && (i>0)) {
		if (myArray[i - 1][q - 1] == '*')
			num1++;
	}
	if ((i < rows - 1) && (q < columns - 1)) {
		if (myArray[i + 1][q + 1] == '*')
			num1++;
	}
	if ((i < rows - 1) && (q>0)) {
		if (myArray[i + 1][q - 1] == '*')
			num1++;
	}
	if ((i > 0) && (q < columns - 1)) {
		if (myArray[i - 1][q + 1] == '*')
			num1++;
	}
	return num1;
}





/*********************************************************************************
* Function: menu
* Description: shows a menu to the user
* Parameters: char**, char**, int, int, int
* Pre-Conditions: arrays must be the same size, positive integers
* Post-Conditions: none
* Line Count: 18
*********************************************************************************/
void menu(char** myArray, char** myStringArray, int rows, int columns, int mines) {
	int choice = 0, x, y;
	cout << "1. Flag" << endl;
	cout << "2. Open" << endl;
	cin >> choice;
	if (choice == 1) {
		cout << "Enter X Location" << endl;
		cin >> x;
		cout << "Enter Y Location" << endl;
		cin >> y;

	}
	if (choice == 2) {
		cout << "Enter X Location" << endl;
		cin >> x;
		cout << "Enter Y Location" << endl;
		cin >> y;

	}
	if ((is_pos_int(x)) && (is_pos_int(y))) {
		user_board(myArray, myStringArray, rows, columns, choice, x, y, mines);
	}
	else {
		goodbye();
	}
}





/*********************************************************************************
* Function: new_board
* Description: creates an array that will be shown to the user
* Parameters: char**, int, int, int
* Pre-Conditions: must be positive integers within range of array
* Post-Conditions: none
* Line Count: 8
*********************************************************************************/
void new_board(char** myArray, int rows, int columns, int mines) {
	char **myStringArray = new char*[rows];
	for (int i = 0; i < rows; ++i) {
		myStringArray[i] = new char[columns];
	}
	int i, q;
	for (i = 0; i < rows; i++) {
		for (q = 0; q < columns; q++) {
			myStringArray[i][q] = ' ';
		}
	}
	cout_board(myArray, myStringArray, rows, columns, mines);
}





/*********************************************************************************
* Function: user_board
* Description: edits the array shown to the user by comparing to hidden array
* Parameters: char**, char**, int, int, int, int, int, int
* Pre-Conditions: integers must be in range of arrays, arrays are same size
* Post-Conditions: none
* Line Count: 17
*********************************************************************************/
void user_board(char** myArray, char** myStringArray, int rows, int columns, int choice, int x, int y, int mines) {
	if ((x > columns) || (y > rows)) {
		cout << "ERROR" << endl;
		cout << "Out Of Range" << endl;
		cout_board(myArray, myStringArray, rows, columns, mines);
	}
	if (choice == 1) {
		myStringArray[rows - y][x - 1] = '!';
	}
	if (choice == 2) {
		myStringArray[rows - y][x - 1] = myArray[rows - y][x - 1];
		if (myStringArray[rows - y][x - 1] == '*') {
			for (int i = 0; i < rows; i++) {
				for (int q = 0; q < columns; q++) {
					cout << "[" << myArray[i][q] << "]";
				}
				cout << endl;
			}
			cout << "YOU LOSE" << endl;
			gameover(myArray, myStringArray);
		}
	}

	winner_search(myArray, myStringArray, rows, columns, mines);
	cout_board(myArray, myStringArray, rows, columns, mines);
}





/*********************************************************************************
* Function: cout_board
* Description: prints out the array in the correct shape
* Parameters: char**, char**, int, int, int
* Pre-Conditions: integers must be in range of arrays, arrays are same size
* Post-Conditions: none
* Line Count: 16
*********************************************************************************/
void cout_board(char** myArray, char**myStringArray, int rows, int columns, int mines) {
	int i, q;
	int rows_temp = rows;
	for (i = 0; i < rows; i++) {
		if (rows_temp > 9) {
			cout << rows_temp;
		}
		if (rows_temp <= 9) {
			cout << rows_temp << " ";
		}
		for (q = 0; q < columns; q++) {
			cout << "[" << myStringArray[i][q] << "]";
		}
		rows_temp = rows_temp - 1;
		cout << endl;
	}
	cout << "   ";
	for (i = 0; i < columns; i++) {
		cout << i + 1 << "  ";

	}
	cout << endl;
	menu(myArray, myStringArray, rows, columns, mines);
}





/*********************************************************************************
* Function: gameover
* Description: deallocates memory and prompts for a restart
* Parameters: char**, char**
* Pre-Conditions: none
* Post-Conditions: none
* Line Count: 13
*********************************************************************************/
void gameover(char** myArray, char** myStringArray) {

	delete[] myStringArray;
	delete[] myArray;
	cout << "______________" << endl;
	cin.ignore();
	cout << "Do You Want To Play Again?(yes = 1, no = 0)" << endl;
	int ans;
	cin >> ans;
	if (ans == 1) {
		cin.ignore();
		cin.clear();
		main_alt();
	}
	else {
		exit(1);
	}
}





/*********************************************************************************
* Function: main_alt
* Description: alternate main, gets user input without command lines
* Parameters: none
* Pre-Conditions: all arrays should be deleted
* Post-Conditions: none
* Line Count: 14
*********************************************************************************/
void main_alt() {
	int rows, columns, mines;
	cout << "How Many Rows?" << endl;
	cin >> rows;
	if (!(is_pos_int(rows))) {
		goodbye();
	}
	cout << "How Many Columns?" << endl;
	cin >> columns;
	if (!(is_pos_int(columns))) {
		goodbye();
	}
	cout << "How Many Mines?" << endl;
	cin >> mines;
	if (!(is_pos_int(mines))) {
		goodbye();
	}

	print_data(rows, mines, columns);
}





/*********************************************************************************
* Function: winner_search
* Description: checks if the board has been cleared without tripping any mines
* Parameters: char**, char**, int, int, int
* Pre-Conditions: integers must be in range of arrays, arrays are same size
* Post-Conditions: none
* Line Count: 17
*********************************************************************************/
void winner_search(char** myArray, char** myStringArray, int rows, int columns, int mines) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int q = 0; q < columns; q++) {
			if (myStringArray[i][q] != ' ') {
				count++;
			}
		}
	}
	int flag = 0;
	for (int i = 0; i < rows; i++) {
		for (int q = 0; q < columns; q++) {
			if (myStringArray[i][q] == '!') {
				flag++;
			}
		}
	}
	if ((count == rows*columns) && (flag == mines)) {
		for (int i = 0; i < rows; i++) {
			for (int q = 0; q < columns; q++) {
				cout << "[" << myArray[i][q] << "]";
			}
			cout << endl;
		}
		cout << "YOU WON!!!" << endl;
		gameover(myArray, myStringArray);
	}
}