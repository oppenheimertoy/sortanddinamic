#include <iostream>
#include<algorithm>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include<chrono>

#define DIV 1048576
#define WIDTH 7

typedef DWORDLONG dg;

using namespace std;
using namespace std::chrono;

int get_RandomNumber(int min, int max);
dg Mem_info();
int Memory_Check(dg mem, dg size);
void Array_Init(int *arr,int n);
void Array_Init(int* arr, int n, int del);
void Array_Print(int *arr, int n);
void Quick_sort(int* arr, int left, int delta); 
void Bubble_Sort(int* arr, int n);
void NewFunction();
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int n,check,k; 
    int* arr1 = NULL;
    dg x,perem;
    cout << "Enter n(sizeof array): ";
    cin >> n;
    perem = static_cast<dg>(n); 
    x = Mem_info();
    check=Memory_Check(x, perem);
    if (check == 1) {
        arr1 = (int*) malloc(n * sizeof(int));

        if (!arr1) {
            cout << "Error";
            return 0;
        }
        Array_Init(arr1, n);
        cout << "Source array: " << endl;
        Array_Print(arr1, n);
        auto start = high_resolution_clock::now();
        Bubble_Sort(arr1, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time spent: "<< duration.count() << " microseconds" << endl;
        cout << "New array: " << endl;
        Array_Print(arr1, n);
    }
    else {
        cout << "Not enough memory!";
        return 0;
    }
    cout << "Enter k(amount of new elements): ";
    cin >> k;
    int delta = k + n;
    perem = static_cast<dg>(delta); 
    x = Mem_info();
    check = Memory_Check(x, perem);
    if (check == 1) {
        int *arr2 = (int*)realloc(arr1, delta * sizeof(int)); 
        if (!arr2) {
            cout << "Error";
            return 0;
        }
        Array_Init(arr2, n, delta);
        cout << "Source array: " << endl;
        Array_Print(arr2, delta);
        auto start = high_resolution_clock::now();
        Quick_sort(arr2, 0, delta - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time spent: " << duration.count() << " microseconds" << endl;
        cout << "New array: " << endl;
        Array_Print(arr2, delta);
        free(arr2);
    }
    else {
        cout << "Not enough memory!";
        free(arr1);
        return 0;
    }
    return 0;
    
}
int get_RandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
dg Mem_info()
{
    MEMORYSTATUSEX statex;
    dg mem;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    cout << "There are " << statex.ullAvailPhys / DIV<< " MB of free physical memory" << endl;
    mem = statex.ullAvailPhys;
    return mem;
} 
int Memory_Check(dg mem, dg size) {
    if ((size * 4) > mem) {
        return -1;
    }
    if (!(size * sizeof(int) > mem)) {
        return 1;
    }
    return 0;
}
void Array_Init(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = get_RandomNumber(1, 10);
    }
}
void Array_Print(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void Array_Init(int* arr, int n, int del) {
    for (int i = n; i < del; ++i) {
        arr[i] = get_RandomNumber(1, 50);
    }
}
void Bubble_Sort(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        bool check = true;
        for (int j = 0; j < n - 1; ++j) {
            if (arr[j] > arr[j + 1])
            {
                check = false;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (check) {
            break;
        }
    }
}
void Quick_sort(int* arr, int left, int right) {
    int lborder = left;
    int rborder = right;
    int elem = arr[(lborder + rborder) / 2];
    while (lborder <= rborder)
    {
        while (arr[lborder] < elem) {
            lborder++;
        }
        while (arr[rborder] > elem) {
            rborder--;
        }
        if (lborder <= rborder)
        {
            swap(arr[lborder], arr[rborder]);
            rborder--;
            lborder++;
        }
    }
    if (rborder > left) {
        Quick_sort(arr, left, rborder);
    }
            
    if (lborder < right) {
        Quick_sort(arr, lborder, right);
    }
}


