#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;
double distance(vector<int> x, vector<int> y) {
    int n = x.size();
    int m = y.size();
    vector<vector<int>> DTW(n, vector<int>(m, -1));
    // Use the given state transition function to fill in the cost matrix. -- diagonal calculation
    // Clear the left and bottom border first.
    DTW[0][0] = abs(x[0] - y[0]);
    for (int i = 1; i < n; ++i)
        DTW[i][0] = abs(x[i] - y[0]) + DTW[i - 1][0];
    for (int j = 1; j < m; ++j)
        DTW[0][j] = abs(x[0] - y[j]) + DTW[0][j - 1];
    // traverse diagonally as a snake
    int i = 1, j = 1;
    int dir = 1;
    bool flag = false;
    while (true) {
        DTW[i][j] = abs(x[i] - y[j]) + min(min(DTW[i][j - 1], DTW[i - 1][j]), DTW[i - 1][j - 1]);
        if (!flag && (j == 1 || j == m - 1)) {  
            if (i + 1 == n) ++j;
            else ++i; 
            dir *= -1; flag = true; 
        }
        else if (!flag && (i == 1 || i == n - 1)) {
            if (j + 1 == m) ++i;
            else ++j; 
            dir *= -1; flag = true; 
        }
        else {
            if (i == n - 1 && j == m - 1) break;
            i = i + dir; j = j - dir; flag = false; 
        }
    }

    vector<int> d;
    //Identify the warping path. (n - 1,m - 1) -> (0,0)
    i = n - 1; j = m - 1;
    while (i >= 0 && j >= 0) {
        d.push_back(DTW[i][j]);

        if (i == 0) { j = j - 1; continue; }
        else if (j == 0) { i = i - 1; continue; }

        if (DTW[i - 1][j - 1] <= DTW[i][j - 1]) {
            if (DTW[i - 1][j - 1] <= DTW[i - 1][j]) { i = i - 1; j = j - 1; }
            else i = i - 1;
        }
        else if (DTW[i][j - 1] <= DTW[i - 1][j]) j = j - 1;
        else i = i - 1;
    }

    double ans = 0;
    //Calculate th time normalized distance
    for (auto di : d) ans += di;
    return ans / d.size();
}

int main(){
	vector<int> X,Y;
	//test case 1
	X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
	cout<<distance(X,Y)<<endl;
	//test case 2
	X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
	cout<<distance(X,Y)<<endl;
	//Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	return 0;
}
