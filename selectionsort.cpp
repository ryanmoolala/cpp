#include <iostream>

using namespace std; 

void selectionsort(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        int value = arr[i];
        int index = -1; 
        for (int j = i+1; j < size; j++) {
            if (arr[j] < value) {
                index = j;
                value = arr[j];
            }
        }
        if (index != -1) {
            int temp = arr[i];
            arr[i] = value;
            arr[index] = temp;
        }
    }
}

int main() {
    cout << "Performing selection sort" << endl;
    int arr[11] {3,2,5,4,0,6,1,7,10,9,8};
    //size of gives size of array in BYTES
    selectionsort(arr, sizeof(arr)/sizeof(arr[0]));

    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}