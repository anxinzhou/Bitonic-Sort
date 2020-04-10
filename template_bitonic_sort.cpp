#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

template<typename T>
void compare_and_swap(T &a, T &b, int sort_direction) {
    if (sort_direction == 0) {
        if (a > b) std::swap(a, b);
    } else {
        if (a < b) std::swap(a, b);
    }
}

template<typename T>
void __bitonic_sort(vector<T> &arr, int start_index, int end_index, int sort_direction) {
    //up to bottom
    // Every time use __bitonic_sort, assume the sequence is already bitonic;
    // an recursive version, recursively swap upper part and bottom party, 
//    if (start_index + 1 >= end_index) return;
//    int mid = (start_index + end_index) / 2;
//    for (int i = start_index; i < mid; i++) {
//        compare_and_swap(arr[i], arr[mid + i - start_index], sort_direction);
//    }
//    __bitonic_sort(arr, start_index, mid, sort_direction);
//    __bitonic_sort(arr, mid, end_index, sort_direction);
    
//  an iterative version
    int ele = end_index - start_index;
    for(int j= ele; j>=2; j/=2) {
        for(int k=start_index;k<end_index;k+=j) {
            for(int i=k;i<k+j/2;i++) {
                compare_and_swap(arr[i], arr[j/2 + i], sort_direction);
            }
        }
    }
}

template<typename T>
void bitonic_sort(vector<T> &arr, int sort_direction) {
    // bottom to up
    // Every time use __bitonic_sort, assume the sequence is already bitonic;
    for (int j = 2; j <= arr.size(); j*=2) {
        for (int i = 0; i < arr.size(); i += j) {         // can use openmp accelerate this part
            __bitonic_sort(arr, i, i + j, (i/j % 2) ^ sort_direction);
        }
    }
}

void test_bitonic_sort_template(int N) {
    vector<string> arr(N);
    for(int i=0;i<arr.size();i++) {
        arr[i] = to_string(rand()%1000);
    }

    bitonic_sort(arr, 1);
    for(int i=0;i<arr.size();i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main() {
    test_bitonic_sort_template(1024);
    return 1;
}