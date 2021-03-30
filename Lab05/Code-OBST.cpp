#include <iostream>
using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

int root[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2];//Record the expected cost of the subtree
double w[n + 2][n + 2];//Record the probability sum of the subtree

double get_expected_cost(int i, int j) {
    if (e[i][j] != MAX) return e[i][j];
    int minr = i;
    double mine = MAX;
    for (int r = i; r <= j; ++r) {
        double tmp = get_expected_cost(i, r - 1) + get_expected_cost(r + 1, j) + w[i][j];
        if (tmp <= mine) {
            minr = r;
            mine = tmp;
        }
    }
    root[i][j] = minr;
    e[i][j] = mine;
    return mine;
}

void optimal_binary_search_tree(double *p,double *q,int n)
{

    // Initialize w
    for (int i = 1; i <= n; ++i) {
        w[i][i] = p[i] + q[i - 1] + q[i];
        for (int j = i + 1; j <= n; ++j)
            w[i][j] = w[i][j - 1] + p[j] + q[j];
    }
    
    // Initialize e
    for (int i = 0; i <= n+1;++i)
        for (int j = 0; j <= n+1; ++j)
            if (j == i - 1) e[i][j] = q[j];
            else e[i][j] = MAX;    // Uninitialized

    // Initialize root
    for (int i = 0; i <= n+1; ++i)
        for (int j = 0; j <= n+1; ++j)
            if (j == i - 1) root[i][j] = j;
            else root[i][j] = -1;   // Uninitialized

    //The result is stored in e.
    get_expected_cost(1, n);
}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/
void construct_optimal_bst(int i,int j, int rt, int loc)
{
//You can adjust the number of input parameters
    bool dummy = false;
    if (j == i - 1) dummy = true;

    cout << (dummy ? "d" : "k") << root[i][j];
    switch (loc) {
    case 0: cout << " is the root" << endl; break;
    case -1: cout << " is the left child of k" << rt << endl; break;
    case 1: cout << " is the right child of k" << rt << endl; break;
    }

    if (dummy) return;
    construct_optimal_bst(i, root[i][j] - 1, root[i][j], -1);
    construct_optimal_bst(root[i][j] + 1, j, root[i][j], 1);
}

int main()
{
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1,n,root[1][n],0);
}
