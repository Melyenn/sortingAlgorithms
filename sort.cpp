#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include "shellsort_knuth.cpp"
#include "flashsort.cpp"

using namespace std;

template <class T>
void Swap(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// This function generates a random array
void GenerateRandomData(int *a, int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// This function generates a sorted array (ascending order)
void GenerateSortedData(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// This function generates a reverse-sorted array (descending order)
void GenerateReverseData(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// This function generates a nearly-sorted array
void GenerateNearlySortedData(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}

	srand((unsigned int) time(NULL));
	
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		Swap(a[r1], a[r2]);
	}
}

void GenerateData(int *a, int n, int dataType)
{
	switch (dataType)
	{
	case 0:	
        printf("Random Data \n");
		GenerateRandomData(a, n);
		break;
	case 1:	
        printf("Sorted Data \n");
		GenerateSortedData(a, n);
		break;
	case 2:	
        printf("Reverse Data \n");
		GenerateReverseData(a, n);
		break;
	case 3:	
        printf("Nearly Sorted Data \n");
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

int GenerateSize(int dataType)
{
	switch (dataType)
	{
	case 0:	
        return 10000;
	case 1:	
		return 30000;
	case 2:	
		return 50000;
	case 3:	
		return 100000;
    case 4:	
		return 300000;
	case 5:	
		return 500000;
	default:
		printf("Error: unknown data type!\n");
        return -1;
	}
}


void deallocate(int *a) {
    delete[] a;
}
 

void print(int n, int *a) {
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

void selectionSort(int n, int *a) {
    for (int i = 0; i < n - 1; i++) {
        int pos_min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[pos_min]) {
                pos_min = j;
            }
        if (pos_min != i) swap(a[pos_min], a[i]);
    }
}

void insertionSort(int n, int *a) {
    for (int i = 0; i < n; i++) {
        int tmp = a[i];
        int j = i;
        while (j > 0 && tmp < a[j - 1]) {
            a[j] = a[j - 1];
            j--;

        }
        a[j] = tmp;
    }
}

//it is the updated version of the insection sort
void shellSort(int n, int *a) {
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int tmp = a[i], j = i;
            while (j  >= gap && a[j - gap] > tmp)  {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = tmp;
        }
        gap /= 2;
    }
}

void bubbleSort(int n, int *a) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                swap(a[j], a[i]);
            }
        }
    }
}

void max_heap(int n, int *a, int i) {
    int parent = i;
    int left_child = i*2 + 1;
    int right_child = i*2 + 2;
    if ( left_child < n && a[parent] < a[left_child]) {
        parent = left_child;
    }
    if (right_child < n && a[parent] < a[right_child]) {
        parent = right_child;
    }

    if (i != parent) {
        swap(a[i], a[parent]);
        max_heap(n, a, parent);
    }
}

void build_heap(int n, int *a) {
    for (int i = n/2 - 1; i >= 0; i--)
        max_heap(n, a, i);
}

void heapSort(int n, int *a) {
    build_heap(n, a);
    int i = 0;
    while(n > 1) {
        swap(a[0], a[--n]);
        max_heap(n, a, 0);
    }
}

// void merge(int pos_begin1, int pos_end1, int *a, int pos_begin2, int pos_end2) {
//     int *c = new int[pos_end2 - pos_begin1 + 1];
//     int i = pos_begin1, j = pos_begin2, n1 = pos_end1, n2 = pos_end2, pos = 0;
//     while (i <= n1 && j <= n2) {
//         if (a[i] < a[j])
//             c[pos++] = a[i++];
//         else 
//             c[pos++] = a[j++];
//     }
//     if (i <= n1) {
//         for (int k = i; k <= n1; k++) 
//             c[pos++] = a[k];
//     }
//     if (j <= n2) {
//         for (int k = j; k <= n2; k++)
//             c[pos++] = a[k];
//     }
//     for (int k = pos_begin1; k <= pos_end2; k++) {
//         a[k] = c[k - pos_begin1];
//     }
    
//     delete[] c;
// }

// void divide_and_conquer(int pos_begin, int pos_end, int *a) {
//     if (pos_end - pos_begin <= 1) {
//         if (a[pos_end] < a[pos_begin]) 
//             swap(a[pos_end], a[pos_begin]);
//         return;
//     }
//     else {
//         int pos = (pos_end + pos_begin) / 2;
//         divide_and_conquer(pos_begin, pos, a);
//         divide_and_conquer(pos + 1, pos_end, a);
//         merge(pos_begin, pos, a, pos + 1, pos_end);
//     }
// }

// void mergeSort(int n, int *a) {
//     divide_and_conquer(0, n - 1, a); 
// }


//mergesort dung 2 mang phu
void merge(int l, int m, int r, int *a, int *tmp) {
    for (int i = l; i < r; i++)
        tmp[i - l] = a[i];
    int pos_i = 0, pos_j = m - l, pos = l;
    while (pos_i < (m - l) && pos_j < (r - l)) {
        if (tmp[pos_i] < tmp[pos_j]) {
            a[pos++] = tmp[pos_i++];
        }
        else {
            a[pos++] = tmp[pos_j++];
        }
    }
    while (pos_i < (m - l)) {
        a[pos++] = tmp[pos_i++];
    }
    while (pos_j < (r - l)) {
        a[pos++] = tmp[pos_j++];
    }
}

void mergeSortHelp(int l, int r, int *a, int *tmp) {
    int left = l, right = r;
    if (left < right - 1) {
        int mid = left + (right - left ) / 2;
        mergeSortHelp(l, mid, a, tmp);
        mergeSortHelp(mid, r, a, tmp);
        merge(left, mid, right, a, tmp);
    }
}

void mergeSort(int n, int *a) {
    int *tmp = new int [n];

    mergeSortHelp(0, n, a, tmp);
    delete[] tmp;
}
//merge mang phu voi mang chinh


void median_of_three(int pos_begin, int pos_end, int *a) {
    int medium_pos = (pos_end + pos_begin)/2;
    if (a[pos_begin] > a[medium_pos]) {
        swap(a[pos_begin], a[medium_pos]);
    }
    if (a[pos_begin] > a[pos_end]) {
        swap(a[pos_begin], a[pos_end]);
    }
    if (a[medium_pos] > a[pos_end]) {
        swap(a[medium_pos], a[pos_end]);
    } 
    swap(a[medium_pos], a[pos_begin]);
}

int partition(int *a, int pos_begin, int pos_end) {
    median_of_three(pos_begin, pos_end, a);
    int pivot = a[pos_begin];
    int min = pos_begin;
    for (int j = pos_begin + 1; j <= pos_end; j++) {
        if (a[j] < pivot) {
            swap(a[++min], a[j]);
        }
    }
    swap(a[min], a[pos_begin]);
    return  min;
}

void quickSortHelp(int *a, int pos_begin, int pos_end)
{
    if (pos_begin < pos_end) {
        int pi = partition(a, pos_begin, pos_end);
        quickSortHelp(a, pos_begin, pi - 1);
        quickSortHelp(a, pi + 1, pos_end);
    }
}

void quickSort(int n, int *a) {
    quickSortHelp(a, 0, n - 1);
}

//Radix sort tự làm

// int n_lose_ith_digit(int n, int i) {
//     while (i--){
//         n /= 10;
//         if (n == 0) break;
//     }
//     return (n);
// }

// void radixSort(int n, int *a) {
//     int ith_digit = 0;
//     vector<int>bucket[10];
//     while (true) {
//         bool check_stop_condition = true;

//         for (int i = 0; i < n; i++) {
//             int so = n_lose_ith_digit(a[i], ith_digit);
//             if (so >= 10) check_stop_condition = false;
//             so = so % 10;
//             bucket[so].push_back(a[i]);
//         }

//         int pos = 0;
//         for (int i = 0; i < 10; i++) {
//             for (int j = 0; j < bucket[i].size(); j++) {
//                 a[pos++] = bucket[i][j];
//             }
//             bucket[i].clear();
//         }
//         if (check_stop_condition == true) break;
//         ith_digit++;
//     }
// }


int getMax(int n, int *a) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    return max;
}

void countSort(int *a, int n, int exp, int *ans) {
    int i, bucket[10] = {0};
    for (int i = 0; i < n; i++)
        bucket[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        bucket[i] += bucket[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        ans[bucket[(a[i] / exp) % 10]--] = a[i];
    }
    for (int i = 0; i < n; i++) 
        a[i] = ans[i];
}

void radixSort(int n, int *a) {
    int max = getMax(n, a);
    int *ans = new int [n];
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(a, n, exp, ans);
}

void countingSort(int n, int *a) {
    int max = getMax(n, a);
    int* bucket = new int[max + 1]();
    for (int i = 0; i < n; i++) {
        bucket[a[i]]++;
    }
    int pos = 0;
    for (int i = 0; i <= max; i++) {
        while (bucket[i]--) {
            a[pos++] = i;
        }
    }
}  

int binarySearch(int left, int right, int val, int *a) {
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (a[mid] > val) {
            right = mid - 1;
        }
        else if (a[mid] <= val) {
            left = mid + 1;
        }
    }
    return left;
}

void binaryInsertionSort(int n, int *a) {
    for (int i = 1; i < n; i++) {
        int pos = binarySearch(0, i - 1, a[i], a);
        int tmp = a[i];
        for (int j = i; j > pos; j--)
            a[j] = a[j - 1];
        a[pos] = tmp;
    }
}

void shakerSortHelp(int pos_begin, int pos_end, int *a) {
    if (pos_begin >= pos_end) return;
    int i = pos_begin;
    while (i < pos_end - 1) {
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
        }
        i++;
    }
    i = pos_end - 1;
    while (i > pos_begin) {
        if (a[i] < a[i - 1]) {
            swap(a[i], a[i - 1]);
        }
        i--;
    }
    shakerSortHelp(pos_begin + 1, pos_end - 1, a);
}

void shakerSort(int n, int *a) {
    shakerSortHelp(0, n, a);
}

void GenerateSort(int *a, int n, int dataType)
{
	switch (dataType)
	{
	case 0:	
		selectionSort(n, a);
        break;
	case 1:	
		insertionSort(n, a);
        break;
	case 2:	
		shellSort(n, a);
		break;
    case 3:
        bubbleSort(n, a);
        break;
    case 4:
        heapSort(n, a);
        break;
    case 5:
        mergeSort(n, a);
        break;
    case 6:
        quickSort(n, a);
        break;
    case 7:
        radixSort(n, a);
        break;
    case 8:
        countingSort(n, a);
        break;
    case 9: 
        binaryInsertionSort(n, a);
        break;
    case 10:
        shakerSort(n, a);
        break;
    case 11:
        flashSort(n, a);
        break;
	default:
		printf("Error: unknown data type!\n");
	}
}

void SortName(int dataType)
{
	switch (dataType)
	{
	case 0:	
		cout << "Selection Sort - ";
        break;
	case 1:	
		cout << "Insertion Sort - ";
        break;
	case 2:	
		cout << "Shell Sort - ";
        break;
    case 3:
        cout << "Bubble Sort - ";
        break;
    case 4:
        cout << "Heap Sort - ";
        break;
    case 5:
        cout << "Merge Sort - ";
        break;
    case 6:
        cout << "Quick Sort - ";
        break;
    case 7:
        cout << "Radix Sort - ";
        break;
    case 8:
        cout << "Counting Sort - ";
        break;
    case 9:
        cout << "Binary Insertion Sort - ";
        break;
    case 10:
        cout << "Shaker Sort - ";
        break;
    case 11:
        cout << "Flash Sort - ";
        break; 
	default:
		printf("Error: unknown data type!\n");
	}
}

void copyArray(int n, int *a, int *a1) {
    for (int i = 0; i < n; i++)
        a1[i] = a[i];
}


int main() {

    //do thoi gian: ref: https://chidokun.github.io/2015/03/cpp-measure-execution-time/#:~:text=C%C3%B3%20th%E1%BB%83%20xem%20v%C3%AD%20d%E1%BB%A5%20m%E1%BA%ABu%20sau%3A%20int,%3C%3C%28float%29%28end-begin%29%2FCLOCKS_PER_SEC%3C%3C%20%22%20s%22%20%3C%3Cendl%3B%20return%200%20%3B%20%7D
    
    // clock_t begin = clock();
    // clock_t end = clock();
    // cout << "Time run: " << (float)(end - begin)/CLOCKS_PER_SEC/1000 << " ms" << "\n";

    //do thoi gian so sanh ctime - chrono : ref: https://stackoverflow.com/questions/36095323/what-is-the-difference-between-chrono-and-ctime

    //do thoi gian su dung chrono: ref: https://www.geeksforgeeks.org/chrono-in-c/

        // chrono::time_point<chrono::system_clock> start, end;
        
        // start = chrono::system_clock::now();
        // //code can do
        // end = chrono::system_clock::now();
        // chrono::duration<double, milli> elapsed_ms = end - start;
        // time_t end_time = chrono::system_clock::to_time_t(end);
   
    for (int i = 0; i < 4; i++) { // data order
        for (int j = 5; j < 6; j++) { // data size
            int n = GenerateSize(j);
            // n = 50;
            if (n == -1) break;
            int *a = new int [n];
            GenerateData(a, n, i);
            // print(n, a);
            cout <<  n << " ------------- \n";
            for (int k = 0; k < 12; k++) { //sorting
                if (k != 6 && k != 11) continue;

                int *a1 = new int[n];
                copyArray(n, a, a1);

                chrono::time_point<chrono::system_clock> start, end;
        
                start = chrono::system_clock::now();
                //code can do
                GenerateSort(a1, n, k);
                end = chrono::system_clock::now();
                chrono::duration<double, milli> elapsed_ms = end - start;
                // time_t end_time = chrono::system_clock::to_time_t(end); // thoi gian dung
                SortName(k);
                cout << "Time run: " << elapsed_ms.count() << " ms \n";

                // print(n, a1);

                delete[] a1;
            }
            delete[] a;

        }
    }

    // int n = 10;
    // int *a = new int [n];
    // GenerateData(a, n, 0);
    // print(n, a);

    // mergeSort(n, a);
    // print(n, a);
    // delete[] a;


    return 0;

}
