#include <iostream>

using namespace std;

void merge(int *arr, int left, int middle, int right) {
    int firstArraySize = middle - left + 1;
    int secondArraySize = right - middle;
    int firstArray[firstArraySize];
    int secondArray[secondArraySize];

    for (int i = 0; i < firstArraySize; i++) {
        firstArray[i] = arr[left + i];
    }

    for (int j = 0; j < secondArraySize; j++) {
        secondArray[j] = arr[middle+j+1];
    }
    
    int i = 0, j = 0, k = left;
    while (i < firstArraySize && j < secondArraySize) {
        if (firstArray[i] < secondArray[j]) {
            arr[k++] = firstArray[i++];
        } else {
            arr[k++] = secondArray[j++];
        }
    }
    while (i < firstArraySize) arr[k++] = firstArray[i++];
    while (j < secondArraySize) arr[k++] = secondArray[j++];
}

void mergesort(int *arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = (left + right) / 2;
    mergesort(arr, left, middle);
    mergesort(arr, middle+1, right);
    merge(arr, left, middle, right);
}

int main() {
    cout << "Performing merge sort" << endl;
    int arr[11] {3,2,5,4,0,6,1,7,10,9,8};
    mergesort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}