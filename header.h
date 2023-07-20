#ifndef HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ARRY_SIZE 128

void InputFile(int arr[]);
void Msg(int arr[]);

int PARENT(int index);
int LEFT(int index);
int RIGHT(int index);
int LEVEL(int index);
int MaxIndex(int A[], int p, int i, int l, int r);
int MinIndex(int A[], int p, int i, int l, int r);
void Heapify(int A[], int index);
void BuildHeap(int A[]);
int HeapExtractMax(int A[]);
int HeapExtractMin(int A[]);
void HeapInsert(int A[], int key);
void HeapFix(int A[],int index);
int HeapMaximum(int A[]);
int HeapMinimum(int A[]);
void HeapDelete(int A[],int index);
void HeapShow(int A[]);

#endif