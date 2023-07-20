#include "header.h"

int PARENT(int index)
{
    return (int)floor(index/2.0);
}

int LEFT(int index)
{
    return 2*index;
}

int RIGHT(int index)
{
    return 2*index + 1;
}

int LEVEL(int index) /* returns the level of the index inside the tree */
{
    return (int)floor(log10(index)/log10(2));
}

int MaxIndex(int A[], int p, int i, int l, int r) /* returns the index of the largest value between the 4 nodes */
{
    int largest;

    largest = i;

    if (p>=1 && A[p] > A[i]) largest = p;
    
    if (l <= A[0] && A[l] > A[largest]) largest = l;

    if (r <= A[0] && A[r] > A[largest]) largest = r;

    return largest;
}

int MinIndex(int A[], int p, int i, int l, int r) /* returns the index of the smallest value between the 4 nodes */
{
    int smallest;

    smallest = i;

    if (p>=1 && A[p] < A[i]) smallest = p;
    
    if (l <= A[0] && A[l] < A[smallest]) smallest = l;

    if (r <= A[0] && A[r] < A[smallest]) smallest = r;

    return smallest;
}

void Heapify(int A[], int index)
{
    int l,r,p,largest,smallest,temp;

    l = LEFT(index);
    r = RIGHT(index);
    p = PARENT(index);
    
    if (LEVEL(index)%2 == 0) /* even depth */
    {
        largest = MaxIndex(A,p,index,l,r);
        temp = A[largest];
        A[largest] = A[index];
        A[index] = temp;

        smallest = MinIndex(A,p,index,l,r);
        temp = A[smallest];
        A[smallest] = A[p];
        A[p] = temp;

        if (smallest != index && smallest != p) Heapify(A,smallest);
    }
    else /* odd depth */
    {
        largest = MaxIndex(A,p,index,l,r);
        temp = A[largest];
        A[largest] = A[p];
        A[p] = temp;

        smallest = MinIndex(A,p,index,l,r);
        temp = A[smallest];
        A[smallest] = A[index];
        A[index] = temp;

        if (largest != index && largest != p) Heapify(A,largest);
    }
    
}

void BuildHeap(int A[])
{
    int i;

    if (A[0] < 2) return; /* A[0] we store the length of the array and if the array smaller then 2 we have no reason to build it */

    for ( i = (int)floor(A[0]/2); i > 1; i--) Heapify(A,i); /* we skip the leafs */
    
}

int HeapExtractMax(int A[])
{
    int max;

    if (A[0] < 1)
    {
        printf("\nheap underflow\n");
        return -99999;
    }

    max = A[1];
    A[1] = A[A[0]]; /* last number in the array replaces the maximum */
    A[0]--;

    if (A[0] >= 2) Heapify(A,2); /* left son */
    if (A[0] >= 3) Heapify(A,3); /* right son */

    return max;
}

int HeapExtractMin(int A[])
{
    int min,i;

    if (A[0] < 1)
    {
        printf("\nheap underflow\n");
        return -99999;
    }

    if (A[0] == 1) i = 1; /* we have only the root so he is the minimum */
    else if (A[0] == 2) i = 2; /* we have only one son so he is the minimum */
    else if (A[2] < A[3]) i = 2; /* we have two sons so one of them is the minimum */
    else i = 3;
    
    min = A[i];
    A[i] = A[A[0]]; /* last number in the array replaces the minimum */
    A[0]--;

    if (A[0] >= LEFT(i)) Heapify(A,LEFT(i));
    if (A[0] >= RIGHT(i)) Heapify(A,RIGHT(i));

    return min;
}

void HeapInsert(int A[], int key)
{
    int i;

    A[0]++;
    i = A[0];
    A[i] = key;

    HeapFix(A,i);
}

void HeapFix(int A[],int index)
{
    int temp,p,pp; /* p = parent pp = parent of parent */

    p = PARENT(index);
    pp = PARENT(p);

    if (LEVEL(index)%2 == 0) /* even depth */
    {
        while (index > 1 && A[pp] < A[index]) /* Goes up to his place*/
        {
            temp = A[index];
            A[index] = A[pp];
            A[pp] = temp;
            index = pp;
            p = PARENT(index);
            pp = PARENT(p);
        }
        
        if (index > 1 && A[p] > A[index]) /* the value maybe not bigger then his granfather but smaller then his dad so we need to replace them */
        {
            temp = A[index];
            A[index] = A[p];
            A[p] = temp;
            index = p;
            HeapFix(A,index); /* after the replace he still might be not the smallest */
        }
    }
    else /* odd depth */
    {
        while (index > 3 && A[pp] > A[index]) /* Goes up to his place*/
        {
            temp = A[index];
            A[index] = A[pp];
            A[pp] = temp;
            index = pp;
            p = PARENT(index);
            pp = PARENT(p);
        }

        if (index > 1 && A[p] < A[index]) /* the value maybe not smaller then his granfather but bigger then his dad so we need to replace them */
        {
            temp = A[index];
            A[index] = A[p];
            A[p] = temp;
            index = p;
            HeapFix(A,index); /* after the replace he still might be not the biggest */
        }
    }
}

int HeapMaximum(int A[]) /* returns max value in heap */
{
    if (A[0] < 1) return A[0];
    else return A[1];
}

int HeapMinimum(int A[]) /* returns min value in heap */
{
    if (A[0] < 1) return A[0];
    else if (A[0] == 1) return A[1]; /* we have only the root so he is the minimum */
    else if (A[0] == 2) return A[2]; /* we have only one son so he is the minimum */
    else if (A[2] < A[3]) return A[2]; /* we have two sons so one of them is the minimum */
    else return A[3];
}

void HeapDelete(int A[],int index)
{
    if (LEVEL(index)%2 == 0) /* even depth */
    {
        A[index] = HeapMaximum(A) + 1;
        HeapFix(A,index);
        HeapExtractMax(A);
    }
    else /* odd depth */
    {
        A[index] = HeapMinimum(A) - 1;
        HeapFix(A,index);
        HeapExtractMin(A);
    }  
}

void HeapShow(int A[]) /* prints the heap to the screen */
{
    int i,level = 0;

    printf("\n");

    for ( i = 1; i <= A[0]; i++)
    {
        if (LEVEL(i) != level)
        {
            printf(" |");
            level = LEVEL(i);
        }

        printf(" %d", A[i]);
    }
    
    printf("\n\n");
}
