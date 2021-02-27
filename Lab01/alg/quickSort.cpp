#include "permutation.h"

void QuickSort(int* a, int n){
    int pivot = a[n-1]; int i = 0;
    for(int j = 0; j <= n-2; ++j){
        if(a[j]<pivot){
            swap(a[i],a[j]);
            ++i;
        }
        ++steps;
    }
    swap(a[i],a[n-1]);
    ++steps;
    if(i>0) QuickSort(a,i);
    if(i<n-1) QuickSort(a+i+1,n-i-1);
}

int main(){
    for(int n = 1; n<=20; ++n){
        int* a = new int[n];
        for(int i = 0; i<n; ++i) a[i] = i+1;
        double res = permutation(a,n,QuickSort);
        std::cout << n << '\t' << res << '\n';
        delete[] a;
    }
    return 0;
}