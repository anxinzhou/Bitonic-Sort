#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

template<typename T>
void __bitonic_sort(vector<T> &arr, int start_index, int end_index, int sort_direction);

template<typename T>
void compare_and_swap(T &a, T &b, int sort_direction) {
    if (sort_direction == 0) {
        if (a > b) std::swap(a, b);
    } else {
        if (a < b) std::swap(a, b);
    }
}


template<typename T>
void generate_bitonic_sequence(vector<T> &arr, int start_index, int end_index, int sort_direction) {
    int level = log2(end_index - start_index);  //
    for (int i = 1; i < level; i++) {
        int gap = pow(2, i);
        for (int j = start_index; j < end_index; j += gap) {
            __bitonic_sort(arr, j, j + gap, ((j-start_index)/gap % 2) ^ sort_direction);
        }
    }
}

template<typename T>
void bitonic_swap(vector<T> &arr, int start_index, int end_index, int sort_direction) {
    if (start_index + 1 >= end_index) return;
    int mid = (start_index + end_index) / 2;
    for (int i = start_index; i < mid; i++) {
        compare_and_swap(arr[i], arr[mid + i - start_index], sort_direction);
    }
    bitonic_swap(arr, start_index, mid, sort_direction);
    bitonic_swap(arr, mid, end_index, sort_direction);
}

template<typename T>
void __bitonic_sort(vector<T> &arr, int start_index, int end_index, int sort_direction) {
    generate_bitonic_sequence(arr, start_index, end_index, sort_direction);
    bitonic_swap(arr, start_index, end_index, sort_direction);
}

template<typename T>
void bitonic_sort(vector<T> &arr, int sort_direction) {
    __bitonic_sort(arr, 0, arr.size(), sort_direction);
}

void test_bitonic_sort_template() {
    vector<string> arr(1024);
    for(int i=0;i<arr.size();i++) {
        arr[i] = to_string(rand()%1000);
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    bitonic_sort(arr, 1);
    for(int i=0;i<arr.size();i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main() {
    test_bitonic_sort_template();
    return 1;
}