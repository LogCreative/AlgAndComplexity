#include<iostream>

int steps;
double averagestep;
long long int permucount;

void output(int *a, int n){
    for(int l = 0; l<n; ++l) std::cout<<a[l]<<' ';
    std::cout<<'\n';
}

void swap(int& a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// Generate permutation by swaping
void permutation(int a[], int n, int cur, void (*pf)(int*a, int n)){
    if(cur==n){
        steps = 0;
        int* b = new int[n];
        for(int i = 0;i<n;  ++i) b[i] = a[i];
        (*pf)(b,n); // The array is broken when it is put into the function.
        averagestep = averagestep * (1.0 * permucount / (permucount + 1)) + 1.0 * steps / (permucount + 1);     // avoid overflow
        ++permucount;
        delete[] b;
    }
    else for(int i = cur; i < n; i++) {
		swap(a[cur], a[i]);
		permutation(a, n, cur+1, *pf);
		swap(a[cur], a[i]);
	}
}

double permutation(int*a, int n, void (*pf)(int*a, int n)){
    averagestep = 0;
    permucount = 0;
    permutation(a,n,0,*pf);
    return averagestep;
}