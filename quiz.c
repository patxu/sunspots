#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include "quiz.h"

void quiz(){
  int correct = 0, incorrect = 0;
  char choice = 'y';
  char answer, c;
  int pos, total;

  FILE* file = fopen("config/quiz.txt", "r");
  fscanf(file, "Total: %d\n", &total);

  for (pos = 1; choice != 'n' && pos <= total; pos++){
    printf("\nQuestion (%d/%d):\n", pos, total);
    //answer = printQuestion(file, pos);

    c = fgetc(file);
    if (pos > 1) c = fgetc(file); //get rid of weird extra line
    do{
      printf("%c", c);
    }while ((c = fgetc(file)) != '\n');
    answer = fgetc(file); //get the answer

    printf("\n> ");
    choice = getchar(); //ask for user input
    if (choice == answer){
      printf("Correct!\n");
      correct++;
    }
    else {
      printf("Incorrect- the answer is actually [%c]\n", answer);
      incorrect++;
    }
    if (choice != '\n')
      while (getchar() != '\n'); //eat up the rest of their input

    printf("Would you like to continue? [y/n]\n");
    choice = getchar(); //ask for user input
    if (choice != '\n')
      while (getchar() != '\n'); //eat up the rest of their input
  }

  printf("\nCorrect: %d | Incorrect: %d\n", correct, incorrect);
  if (correct > 0 && incorrect == 0)
    printf("Wow, nice job! You got them all correct!\n");
  printf("Thanks for taking the quiz.\n");

  fclose(file);
}
