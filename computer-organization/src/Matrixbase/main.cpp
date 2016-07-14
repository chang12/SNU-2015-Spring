#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <omp.h>

#include "function.hpp"

using namespace std;

int main()
{
	srand(time(NULL));

	vector<vector<float>> A;
	vector<vector<float>> B;

	//int set_num = 6 - 1;

	//int set_size[9][3] = { { 128, 128, 1024 }, { 1024, 128, 128 }, { 128, 1024, 128 }, { 512, 512, 512 }, { 1024, 1024, 1024 },
	//{ 16384, 512, 512 }, { 2048, 2048, 2048 }, { 1024, 65536, 128 }, { 4096, 4096, 4096 } };

	//generate_matrix(set_size[set_num][0], set_size[set_num][1], "A.txt");
	//generate_matrix(set_size[set_num][1], set_size[set_num][2], "B.txt");

	read_matrix(A, "A.txt");
	read_matrix(B, "B.txt");

	// Prepare transpose of Matrix B for better cache use
	vector<vector<float>> B_trans;
	B_trans.resize(B[0].size());
	for (int a = 0; a < B[0].size(); a++){
		B_trans[a].resize(B.size(), 0);
		for (int b = 0; b < B.size(); b++){
			B_trans[a][b] = B[b][a];
		}
	}

	if (A[0].size() != B.size())
	{
		cout << "Matrix dimension error" << endl;
		return -1;
	}
	else
	{
		vector<vector<float>> C;
		C.resize(A.size());
		for (int a = 0; a < A.size(); a++)
		{
			C[a].resize(B[0].size(), 0);
		}

		int i, j, k;
		int ii, jj;
		int i_max = A.size();
		int j_max = B[0].size();
		int k_max = B.size();

		cout << "Start Matrix Multiplication" << endl;
		cout << "[ " << A.size() << " x " << A[0].size() << " ] x [ " << B.size() << " x " << B[0].size() << " ] = [ " << C.size() << " x " << C[0].size() << " ]" << endl;
		chrono::system_clock::time_point StartTime = chrono::system_clock::now();
		//---------------Matrix Multiplication---------------//

		omp_set_num_threads(4);
#pragma omp parallel for private(j,k,ii,jj)
		for (i = 0; i < i_max; i += 32)
		{
			for (j = 0; j < j_max; j += 32)
			{
				for (k = 0; k < k_max; k += 32)
				{
					for (ii = i; ii < i + 32; ii++){
						for (jj = j; jj < j + 32; jj++){
							/*for (kk = k; kk < k+32; kk++){
							C[ii][jj] += A[ii][kk] * B_trans[jj][kk];
							}*/
							C[ii][jj] += A[ii][k] * B_trans[jj][k];
							C[ii][jj] += A[ii][k + 1] * B_trans[jj][k + 1];
							C[ii][jj] += A[ii][k + 2] * B_trans[jj][k + 2];
							C[ii][jj] += A[ii][k + 3] * B_trans[jj][k + 3];
							C[ii][jj] += A[ii][k + 4] * B_trans[jj][k + 4];
							C[ii][jj] += A[ii][k + 5] * B_trans[jj][k + 5];
							C[ii][jj] += A[ii][k + 6] * B_trans[jj][k + 6];
							C[ii][jj] += A[ii][k + 7] * B_trans[jj][k + 7];
							C[ii][jj] += A[ii][k + 8] * B_trans[jj][k + 8];
							C[ii][jj] += A[ii][k + 9] * B_trans[jj][k + 9];
							C[ii][jj] += A[ii][k + 10] * B_trans[jj][k + 10];
							C[ii][jj] += A[ii][k + 11] * B_trans[jj][k + 11];
							C[ii][jj] += A[ii][k + 12] * B_trans[jj][k + 12];
							C[ii][jj] += A[ii][k + 13] * B_trans[jj][k + 13];
							C[ii][jj] += A[ii][k + 14] * B_trans[jj][k + 14];
							C[ii][jj] += A[ii][k + 15] * B_trans[jj][k + 15];
							C[ii][jj] += A[ii][k + 16] * B_trans[jj][k + 16];
							C[ii][jj] += A[ii][k + 17] * B_trans[jj][k + 17];
							C[ii][jj] += A[ii][k + 18] * B_trans[jj][k + 18];
							C[ii][jj] += A[ii][k + 19] * B_trans[jj][k + 19];
							C[ii][jj] += A[ii][k + 20] * B_trans[jj][k + 20];
							C[ii][jj] += A[ii][k + 21] * B_trans[jj][k + 21];
							C[ii][jj] += A[ii][k + 22] * B_trans[jj][k + 22];
							C[ii][jj] += A[ii][k + 23] * B_trans[jj][k + 23];
							C[ii][jj] += A[ii][k + 24] * B_trans[jj][k + 24];
							C[ii][jj] += A[ii][k + 25] * B_trans[jj][k + 25];
							C[ii][jj] += A[ii][k + 26] * B_trans[jj][k + 26];
							C[ii][jj] += A[ii][k + 27] * B_trans[jj][k + 27];
							C[ii][jj] += A[ii][k + 28] * B_trans[jj][k + 28];
							C[ii][jj] += A[ii][k + 29] * B_trans[jj][k + 29];
							C[ii][jj] += A[ii][k + 30] * B_trans[jj][k + 30];
							C[ii][jj] += A[ii][k + 31] * B_trans[jj][k + 31];
						}
					}
				}
			}
		}

		//---------------Matrix Multiplication---------------//
		chrono::system_clock::time_point EndTime = chrono::system_clock::now();
		chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(EndTime - StartTime);
		cout << "Matrix Multiplication done" << endl;
		cout << "Time : " << micro.count() << endl;

		write_matrix(C, "C.txt");

		getchar();
		return 0;
	}
}