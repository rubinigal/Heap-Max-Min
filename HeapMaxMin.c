#include "header.h"

int main()
{
    int arr[MAX_ARRY_SIZE] = {0};

    InputFile(arr);
    Msg(arr);

    return 0;
}

void InputFile(int arr[]) /* filling the array from the file */
{
    FILE *arry;
    int i;

    if ((arry = fopen("Array Data.txt", "r")) == NULL) /* openning the file */
    {
        fprintf(stderr, "\nArray Data file could not be opened\n");
        exit(1);
    }

    for ( i = 1; i < MAX_ARRY_SIZE && fscanf(arry, "%d", &arr[i]) != EOF; i++) /* filling the array from the file */
    {
        arr[0]++;
    }

    fclose(arry);
}

void Msg(int arr[]) /* managing output/input */
{
    int mode,num;

    printf("Press 1 to build the heap, 0 for exit\n");
    scanf("%d", &mode);

    if (mode == 1) BuildHeap(arr);
    else if (mode == 0) exit(0);
    else
    {
        printf("The input number is outside the range, try again\n");
        Msg(arr);
    }

    for (;;)
    {
        printf("Press 1 to show the heap, 2 to extract the maximum key, 3 to extract the minimum key, 4 to insert a new key, 5 to delete a key, 0 for exit\n");
        scanf("%d", &mode);

        if (mode == 1) HeapShow(arr);
        else if (mode == 2) printf("\n%d\n",HeapExtractMax(arr));
        else if (mode == 3) printf("\n%d\n",HeapExtractMin(arr));
        else if (mode == 4) 
        {
            printf("Enter the new key:\n");
            scanf("%d", &num);
            HeapInsert(arr, num);
        }
        else if (mode == 5)
        {
            printf("Enter the index of the key you want to delete:\n");
            scanf("%d", &num);
            if (num > arr[0] || num < 1) /* checking if the index in range of array */
            {
                printf("Your index does not exists\n");
                continue;
            }
            HeapDelete(arr, num);
        }
        else if (mode == 0) exit(0);
        else continue;   
    }
}