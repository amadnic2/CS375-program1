#include<chrono>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>


using namespace std;

//memoization table
vector<vector<int>> memo;


//Recursive Top-down LCS (with memoiazation)
int LCS(string first, string second, int i, int j) {
	//base case
	if (i == 0 || j == 0) return 0;

	//check memo mem table
	if(memo[i][j] > -1) return memo[i][j];

  //else calculate solution, and store it in the table
	//last characters are equal
	if (first[i] == second[j]) {
		memo[i][j] =  1 + LCS(first, second, i-1, j-1);
	}
	//case: xi != yi so you take the longest of xi-1 and y or yj-1 and x
	else {
		memo[i][j] = max(LCS(first, second, i-1, j), LCS(first, second, i, j-1));
	}

	return memo[i][j];
}

int main(int argc, char *argv[]) {
	//start clock
	auto begin = chrono::high_resolution_clock::now();

	//to store strings in question
	string str_1, str_2;

	//open input files, save strings, close files
	ifstream file_1(argv[1]);
	ifstream file_2(argv[2]);

	getline(file_1, str_1);
	getline(file_2, str_2);

	file_1.close();
	file_2.close();

	//initialize memoization table with -1s
	for (int i = 0; i < str_1.length() + 1; i++) {
		vector<int> t;
		for (int j = 0; j < str_2.length() + 1; j++) {
			t.push_back(-1);
		}
		memo.push_back(t);
	}

	//output file
	ofstream op;
	op.open(argv[3]);

	//call LCS
	int LCS_length = LCS(str_1, str_2, str_1.length(), str_2.length());
	op << LCS_length << endl;

	//stop clock, write to output
	auto end = chrono::high_resolution_clock::now();

	op <<"Run time: "<< std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << endl;

	//close the output file
	op.close();

	return 0;
}
