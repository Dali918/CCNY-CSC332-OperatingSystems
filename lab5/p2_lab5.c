#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


const int students = 10;
const int chapters = 2;
const int hwks = 2;
const char *file = "quiz_grades.txt"; // file name


void director(int grades[students][chapters * hwks]) {


   //file reading
   FILE *fp;
   // reading value
   int   values = 0;
   // Open file
   fp = fopen(file, "r");
   if (fp == NULL) {
       printf("File can not be opened.");
       exit(0);
   }
   // File will open
   else {


       // reading each value in the file
       for (int i = 0; i < students; i++){
           for (int j = 0; j < (chapters * hwks); j++) {
               char value[10] = "";
               char str;
               while(fscanf(fp, "%c", &str) != EOF){
                   if (isdigit(str)){
                       strncat(value, &str, 1);
                   }
                  else{
                      break;
                   }
               }
               grades[i][j] = atoi(value);
           }
       }
   }
   fclose(fp);
}


void worker(int grades[students][chapters * hwks], int c, int h) {


   // the total
   float sum = 0.0;
   // max value
   int max = 0;
   // checks for the max
   int total = c * hwks;
   for (int i = 0; i < 10; i++) {
       sum += grades[i][total + h];
       if (max < grades[i][(total )+ h]) {
           max = grades[i][(total )+ h];
       }
   }
 
   // average
   printf("Average grades for Homework %d in Chapter %d: %0.2f\n", h + 1, c + 1, sum / 10);
   exit(0);
}


// manager class
void manager(int grades[students][chapters * hwks], int c) {
   for (int homework = 0; homework < hwks; homework++) {
       if (fork() == 0) {
           worker(grades, c, homework);
       }
       wait(NULL); // ends the process
   }
   exit(0); // exit the process
}


// main class
int main(int argc, char *argv[]) {
   int grades[students][chapters * hwks];


   director(grades);
   for (int i = 0; i < chapters; i++) {
       if (fork() == 0) {
           // manager class from 0
           manager(grades, i);
       }
       wait(NULL);
   }
   exit(0);
}
