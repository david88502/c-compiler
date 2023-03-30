#include <stdio.h>
#include <stdlib.h>
#define DATASIZE 1001

void shortLanguage(char *command_pointer, char *input) {
  int bracket_flag;
  char command;
  char data[DATASIZE] = {0};
  char *dp; /* data pointer */
  /* Move dp to middle of the data array */
  dp = &data[DATASIZE / 2];

  while (command = *command_pointer++)
    switch (command) {
    case '>': /* Move data pointer to next address */
      dp++;
      break;
    case '<': /* Move data pointer to previous address */
      dp--;
      break;
    case '+': /* Increase value at current data cell by one */
      (*dp)++;
      break;
    case '-': /* Decrease value at current data cell by one */
      (*dp)--;
      break;
    case '.': /* Output character at current data cell */
      printf("%c", *dp);
      break;
    case ',': /* Accept one character from input pointer ip and
                 advance to next one */
      *dp = *input++;
      break;
    case '[': /* When the value at current data cell is 0,
                 advance to next matching ] */
      if (!*dp) {
        for (bracket_flag = 1; bracket_flag; command_pointer++)
          if (*command_pointer == '[')
            bracket_flag++;
          else if (*command_pointer == ']')
            bracket_flag--;
      }
      break;
    case ']': /* Moves the command pointer back to matching
                 opening [ if the value of current data cell is
                 non-zero */
      if (*dp) {
        /* Move command pointer just before ] */
        command_pointer -= 2;
        for (bracket_flag = 1; bracket_flag; command_pointer--)
          if (*command_pointer == ']')
            bracket_flag++;
          else if (*command_pointer == '[')
            bracket_flag--;
        /* Advance pointer after loop to match with opening [ */
        command_pointer++;
      }
      break;
    }
  /* Adding new line after end of the program */
  printf("\n");
}

int main(int argc, char *argv[]) {

  FILE *fp;
  char *command_input;
  long file_size;

  if (argc < 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", argv[1]);
    return 1;
  }

  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  command_input = (char *)malloc(file_size * sizeof(char));
  if (command_input == NULL) {
    printf("Error allocating memory\n");
    return 1;
  }

  fread(command_input, sizeof(char), file_size, fp);
  fclose(fp);

  // printf("Contents of file %s:\n%s", argv[1], hello_world_code);
  char *input = "";
  shortLanguage(command_input, input);
  free(command_input);
  return 0;
}