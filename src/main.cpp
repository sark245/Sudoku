//Created by Kira

#include<bits/stdc++.h>
using namespace std;

#define IOS cin.sync_with_stdio(0);cin.tie(0); cout.tie(0);

bool ans;
int row[9], col[9], box[3][3];

//Assuming a 9x9 board for this problem.

void printSudoku(vector<vector<int>> v){
	cout<<endl;
	for(int i = 0; i < 9;i++){
		if(i % 3 == 0){
			cout<<"-------------------------\n";
		}
		for(int j = 0; j < 9; j++){
			if(j %  3 == 0)cout<<"| ";
			cout<<v[i][j]<<' ';
		}
		cout<<'|'<<endl;
	}
	cout<<"-------------------------\n";

}
void revert(int x, int y, int val){
	row[x] ^= (1 << val);
	col[y] ^= (1 << val);
	box[x/3][y/3] ^= (1 << val);
}
bool isValid(vector<vector<int>>&mat, int x, int y, int val){
	if(row[x] & (1 << val))return false;
	if(col[y] & (1 << val))return false;
	if(box[x/3][y/3] & (1 << val))return false;
	revert(x, y, val);
	return true;
}


bool backtrack(vector<vector<int>>&res){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(res[i][j] == 0){
				for(int k = 1; k <= 9; k++){
					if(isValid(res, i, j, k)){
						res[i][j] = k;
						if(backtrack(res))return true;
						res[i][j] = 0;
						revert(i, j, k);
					}
				}
				return false;
			}
		}
	}
	return true;
}

vector<vector<int>> getResult(vector<vector<int>> &sudoku){
	memset(row, 0, sizeof row);
	memset(col, 0, sizeof col);
	memset(box, 0, sizeof box);

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(sudoku[i][j] != 0){
				revert(i, j, sudoku[i][j]);
			}
		}
	}

	vector<vector<int>> result = sudoku;
	ans = backtrack(result);
	return result;
}


int main(){
   IOS

	vector<vector<int>> sudoku = {
		{0,  0,  1,  0,  7,  0,  0,  5,  0},
		{0,   7, 0,   4,  0,  2,  9,  0,  0},
		{8,  0,  0,  0,  0,  0,  0,  0,  6},
		{0,  4,  0,   5,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  0,  8},
		{0,  0,  7,  0,  6,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  7,  3,  0,  0},
		{9,  0,  5,  0,  8,  0,  0,  0,  1},
		{0,  3,  0,  9,  0,  0,  0,  6,  0}
	};
	cout<<"The original puzzle: ";
	printSudoku(sudoku);
	vector<vector<int>> res = getResult(sudoku);
	if(ans){
		cout<<"The solution is: ";
		printSudoku(res);
	}else{
		cout<<"Invalid puzzle!!";
	}
}

