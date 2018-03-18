/*
 * prints the html tags in a document.
 *
 * Usage:
 *   htmlParse someFile.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "htmlParse.h"

// main function
int main(int argc, char* argv[]) {

  // check that there is exactly one argument (in addition to the command
  // name
  if (argc != 2) {
    fprintf(stderr, "Need exactly one argument.\n");
    return EXIT_FAILURE;
  }

  // attempt to open the file, giving an error message if unsuccessful
  FILE* input = fopen(argv[1], "r");
  if (input == NULL) {
    fprintf(stderr, "Could not open file %s.\n", argv[1]);
    return EXIT_FAILURE;
  }

  // list all the html tags in the file
  listHtml(input);

  // close the input file
  fclose(input);

  // we succeeded
  return EXIT_SUCCESS;
}


