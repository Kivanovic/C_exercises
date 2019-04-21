#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


//===================================================================
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Array;


//===================================================================
static Array CreateArray()
{
    Array ar;
    ar.size = 0;
    ar.capacity = sizeof(int) * 32;
    ar.data = malloc(ar.capacity);
    return ar;
}


//===================================================================
static void ClearArray(Array* ar)
{
    ar->size = 0;
    ar->capacity = sizeof(int) * 32;

    if (ar->data != NULL)
        free(ar->data);

    ar->data = malloc(ar->capacity);
}


//===================================================================
static void AddArray(Array* ar, int value)
{
    if (ar->size == ar->capacity) {
        ar->capacity += ar->capacity;
        ar->data = realloc(ar->data, ar->capacity);
    }

    memcpy(ar->data+ar->size, &value, sizeof(int));
    ar->size += 1;
}


//===================================================================
static bool Contains(Array* array, int value)
{
    for (size_t i=0; i<array->size; ++i)
        if (array->data[i] == value)
            return true;
    return false;
}


//===================================================================
static void ClearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


//===================================================================
static bool AskIfContinue()
{
    while (true)
    {
        printf("Do you wanna play again?[1/0]: ");
        int rep;
        if (scanf(" %d", &rep) != 1) {
            puts("Invalid input!\n\n");
            continue;
        }

        if (rep == 1) {
            ClearScreen();
            return true;
        } else if (rep == 0) {
            return false;
        } else {
            printf("Select 1 or 0 to answer!\n\n");
            continue;
        }
    }
}


//===================================================================
int main()
{
    srand((unsigned)time(NULL));
    int num = rand() % 101;

    int tries = 1;
    Array guessed = CreateArray();

    while (true)
    {
        printf("----------------------------------\n");
        printf("Guess a number between 0 and 100: ");
        int guess;
        if (scanf(" %d", &guess) != 1) {
            puts("Invalid input!\n\n");
            continue; }

        if (Contains(&guessed, guess)) {
            printf("You have already guessed %d!\n\n", guess);
            continue;
        }

        if (guess == num)
        {
            printf("\nCongratultions! You guessed the number %d!\n", guess);

            if (tries == 1)
                printf("You guessed in your first try!\n\n");
            else
                printf("You tried %d times!\n\n", tries);

            if (AskIfContinue()) {
                num = rand() % 101;
                tries = 1;
                ClearArray(&guessed);
                continue;
            } else break;
        }
        else if (num < guess)
        {
            printf("The secret number is lesser than %d.\n\n", guess);
            AddArray(&guessed, guess);
            tries += 1;
            continue;
        }
        else if (num > guess)
        {
            printf("The secret number is greater than %d.\n\n", guess);
            AddArray(&guessed, guess);
            tries += 1;
            continue;
        }
    }

    free(guessed.data);
    return 0;
}
