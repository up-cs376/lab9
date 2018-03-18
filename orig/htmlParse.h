// this is an include file for htmlParse.c

#include <stdio.h>

// five types of tags
// - START, as in <myTag>
// - END, as in </myTag>
// - VOID, as in <myTag/>
// - NOMORE, indicating that end of file was reached
// - ERROR, indicating that a parse error occured
typedef enum {START, END, VOID, NOMORE, ERROR} tagType;

// returns a printable version of the given tagType value
extern char* tagTypeToString(tagType tt);

// reads html tags from input, printing them
extern void listHtml(FILE* input);

// last line of file
