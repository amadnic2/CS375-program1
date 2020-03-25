#include<chrono>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>


using namespace std;

int main(int argc, char *argv[]) {

	//start clock
	auto begin = chrono::high_resolution_clock::now();

	// strings that we solve LCS for
	string str_1, str_2

	//open files
	ifstream file_1(argv[1]);
	ifstream file_2(argv[2]);

	//save strings from input files and close files (they are no longer needed)
	getline(file_1, str_1);
	getline(file_2, str_2);

	file_1.close();
	file_2.close();

	//We use two matrixes, one to represent the values of the table and another to represent the direction of the arrows
	int V_mat[str_1.length()+1][str_2.length()+1];
	string D_mat[str_1.length()+1][str_2.length()+1];

	//output file
	ofstream op;
	op.open(argv[3]);

//loop through matrices
	for (int row = 0; row < str_1.length() + 1; row++) {
		for (int column = 0; column < str_2.length() + 1; column++) {

			//initialization of 0th rows and columns
			if (row == 0 || column == 0) {
				V_mat[row][column] = 0;
			}

			//forming the rest of the matrix
			else {

				// case: xi = yi. We use "d" to indicate "diagonal"
				if (str_1[row-1] == str_2[column-1]) {
					D_mat[row][column] = "d";
					V_mat[row][column] = (V_mat[row-1][column-1])+1;
				}

				//case xi != yi we choose the best of |x| -1 and y or |y| -1 and x. "u" indicates up and "l" indicates left
				else {
					if (V_mat[row-1][column] >= V_mat[row][column-1]) {
						D_mat[row][column] = "u";
						V_mat[row][column] = V_mat[row-1][column];
					}
					else {
						D_mat[row][column] = "l";
						V_mat[row][column] = V_mat[row][column-1];

					}
				}
			}
		}

	}

	//starting positions in traversal of d_matrix
  int x_len = str_1.length(), y_len = str_2.length();

	//print matrix if length <= 10
	if (str_1.length() <= 10 && str_2.length() <= 10) {

		for (int i = 0;  i <= str_1.length(); i++) {
			for (int j = 0; j <= str_2.length(); j++) {
				op << V_mat[i][j] << " ";
			}
			op << endl;
		}

		//string variable to store some longest common subsequence.
		string LCS;
		//Traversal of d_matrix to find a lcs
		while (1) {
			if (D_mat[x_len][y_len] == "d") {
				LCS = str_1[x_len-1] + LCS;
				x_len--;
				y_len--;
			}
			else if (D_mat[x_len][y_len] == "u") {
				x_len--;
			}
			else if (D_mat[x_len][y_len] == "l") {
				y_len--;
			}
			else {
				break;
			}
		}

		op << LCS << endl;
	}

  //print bottom right entry (length)
	else {
		op << V_mat[x_len][y_len] << endl;
	}

	//stop clock
	auto end = chrono::high_resolution_clock::now();
	op << "Runtime: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << " ms" << endl;

  //close output file
	op.close();
	return 0;
}
