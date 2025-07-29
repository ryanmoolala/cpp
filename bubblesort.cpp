#include <iostream>

using namespace std;

void bubblesort(int *arr, int size) {
    for (int i = 0; i < size; i++) 
    {
        for (int i = 1; i < size; i++) 
            {
                if (arr[i] < arr[i-1]) {
                    int temp = arr[i-1];
                    arr[i-1] = arr[i];
                    arr[i] = temp;  
                }
            }
    }
}

int main() {
    cout << "Performing bubble sort" << endl;
    int arr[11] {3,2,5,4,0,6,1,7,10,9,8};
    //size of gives size of array in BYTES
    bubblesort(arr, sizeof(arr)/sizeof(arr[0]));

    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}