#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void heap_sort(int arr[], int n);
void heapify(int arr[], int n, int i);
void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i >= 1; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int main() {
    int arr[] = {5, 3, 8, 4, 2, 7, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Test Merge Sort
    clock_t start = clock();
    merge_sort(arr, 0, n - 1);
    clock_t end = clock();
    printf("Merge Sort: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    // Test Heap Sort
    int arr2[] = {5, 3, 8, 4, 2, 7, 1, 6};
    start = clock();
    heap_sort(arr2, n);
    end = clock();
    printf("Heap Sort: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    // Test Quick Sort
    int arr3[] = {5, 3, 8, 4, 2, 7, 1, 6};
    start = clock();
    quick_sort(arr3, 0, n - 1);
    end = clock();
    printf("Quick Sort: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}