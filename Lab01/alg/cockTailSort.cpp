#include "permutation.h"

void CockTailSort(int* a, int n){
    int i = 0, j = n-1; bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int k = i; k<=j-1; ++k){
            if(a[k]<a[k+1]){
                swap(a[k],a[k+1]);
                sorted = false;    
            }
            ++steps;
        }
        --j;
        for(int k = j; k>=i+1; --k){
            if(a[k-1]<a[k]){
                swap(a[k-1],a[k]);
                sorted = false;
            }
            ++steps;
        }
        ++i;
    }
}

int main(){
    for(int n = 1; n<=20; ++n){
        int* a = new int[n];
        for(int i = 0; i<n; ++i) a[i] = i+1;
        steps = 0;
        double res = permutation(a,n,CockTailSort);
        std::cout << n << '\t' << res << '\n';
        delete[] a;
    }
    return 0;
}