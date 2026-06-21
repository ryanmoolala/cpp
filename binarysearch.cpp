#include <iostream>

using namespace std;
bool binarysearch(int* arr, int size, int find) {
    int l = 0, r = size-1;
    while (l <= r) {
        int mid = l + (r-l)/2;
        if (arr[mid] == find) {
            cout << arr[mid] << endl;
            return true;
        } else if (find < arr[mid]) {
            r = mid-1;
        } else {
            l = mid + 1;
        }
    }
    cout << "not found" << endl;
    return false;
}
int main() {
    int arr[20] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    bool found = binarysearch(arr, sizeof(arr)/sizeof(arr[0]), 2);
    cout << found << endl;
    return 0;
}