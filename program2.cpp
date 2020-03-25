#include<chrono>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>


using namespace std;

//Recursive LCS (No memoiozation)
int LCS(string first, string second, int i, int j) {
	//base case
	if (i > first.length() + 1 || j > second.length()  + 1) {
		return 0;
	}
	//case: xi = yi so you includ that character
	else if (first[i] == second[j]) {
		return 1 + LCS(first, second, i+1, j+1);
	}
	//case: xi != yi so you take the longest of xi-1 and y or yj-1 and x
	else {
		return max(LCS(first,second,i+1,j), LCS(first, second, i, j+1));
	}
}

int main(int argc, char *argv[]) {

	//start clock
	auto begin = chrono::high_resolution_clock::now();

	//Strings to hold input strings
	string str_1, str_2;

	//open input files, save strings, close files
	ifstream file_1(argv[1]);
	ifstream file_2(argv[2]);

	getline(file_1, str_1);
	getline(file_2, str_2);

	file_1.close();
	file_2.close();

	//output file
	ofstream op;
	op.open(argv[3]);

	//call recursive function and output length
	int LCS_length = LCS(str_1, str_2, 0, 0);
 	op << LCS_length << endl;

	//stop clock
	auto end = chrono::high_resolution_clock::now();

	//write time to output
	op <<"Runtime: "<< std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << " ms" << endl;

	//close output file
	op.close();
	return 0;
}
