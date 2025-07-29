#include <iostream>

using namespace std;

void insertionsort(int *arr, int size) {
    //cout << size << endl;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 and arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }

}

int main() {
    cout << "Performing insertion sort" << endl;
    int arr[11] {3,2,5,4,0,6,1,7,10,9,8};
    //size of gives size of array in BYTES
    insertionsort(arr, sizeof(arr)/sizeof(arr[0]));

    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}