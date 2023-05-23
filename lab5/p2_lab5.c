#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


#define NUM_STUDENTS 10
#define NUM_CHAPTERS 2
#define NUM_HOMEWORKS 2
#define FILENAME "quiz_grades.txt"

// Function to read grades from the file
void readGrades(int grades[NUM_STUDENTS][NUM_CHAPTERS * NUM_HOMEWORKS])
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("File could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        for (int j = 0; j < (NUM_CHAPTERS * NUM_HOMEWORKS); j++)
        {
            char value[10] = "";
            char c;
            while (fscanf(file, "%c", &c) != EOF)
            {
                if (isdigit(c))
                {
                    strncat(value, &c, 1);
                }
                else
                {
                    break;
                }
            }
            grades[i][j] = atoi(value);
        }
    }

    fclose(file);
}

// Function to calculate average grade and maximum grade for a specific chapter and homework
void calculateWorker(int grades[NUM_STUDENTS][NUM_CHAPTERS * NUM_HOMEWORKS], int chapter, int homework)
{
    float sum = 0.0;
    int max = 0;
    int total = chapter * NUM_HOMEWORKS;

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        int grade = grades[i][total + homework];
        sum += grade;

        if (grade > max)
        {
            max = grade;
        }
    }

    printf("Average grade for Homework %d in Chapter %d: %.2f\n", homework + 1, chapter + 1, sum / NUM_STUDENTS);
    exit(EXIT_SUCCESS);
}

// Function to coordinate calculation for each chapter and homework
void calculateManager(int grades[NUM_STUDENTS][NUM_CHAPTERS * NUM_HOMEWORKS], int chapter)
{
    for (int homework = 0; homework < NUM_HOMEWORKS; homework++)
    {
        if (fork() == 0)
        {
            calculateWorker(grades, chapter, homework);
        }
        wait(NULL);
    }
    exit(EXIT_SUCCESS);
}

int main()
{
    int grades[NUM_STUDENTS][NUM_CHAPTERS * NUM_HOMEWORKS];

    // Read grades from the file
    readGrades(grades);

    for (int chapter = 0; chapter < NUM_CHAPTERS; chapter++)
    {
        if (fork() == 0)
        {
            // Coordinate calculation for each chapter
            calculateManager(grades, chapter);
        }
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}
