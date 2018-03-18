#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "htmlParse.h"
#include "TagList.h"

// prototypes for static (private) functions
static int gobbleAlphaNums(FILE* input, char* nameBuffer);
static TagList* createHtmlList(FILE* input);
static tagType nextTag(FILE *input, char* nameBuffer);

// reads html tags from input, printing them
void listHtml(FILE* input) {
  // create the list of tags, read from input
  TagList* strings = createHtmlList(input);

  // print each tag, including its type
  TagList* sl;
  for (sl = strings; sl != NULL; sl = sl->next) {
    printf("%s: %s\n", tagTypeToString(sl->type), sl->name);
  }
}

// returns a printable version of the given tagType value
char* tagTypeToString(tagType tt) {
  switch (tt) {
  case START:
    return "START";
    break;
  case END:
    return "END";
    break;
  case VOID:
    return "VOID";
    break;
  case NOMORE:
    return "NOMORE";
    break;
  case ERROR:
    return "ERROR";
    break;
  default:
    return "\?\?\?";
    break;
  }
}

// reads an html file, extracts its tags, and creates a list of those tags
static TagList* createHtmlList(FILE* input) {
  // buffer for reading tag name
  char buffer[2000];

  // list to return, initialized to NULL
  TagList* rtnVal = NULL;

  // spot at end of list for next insertion
  TagList** insertSpot = &rtnVal;

  // whether an error was found
  int errorFound = 0;

  // as long as no error is found (and not at end of file), keep searching
  // for html-tags
  while (!errorFound) {
    // attempt to read a tag
    tagType tt = nextTag(input, buffer);

    // if end of file, return our list; otherwise, if an error occured,
    // then mark as error as having occured, set the tag name to be
    // a dummy name indicating an error
    if (tt == NOMORE) {
      return rtnVal;
    }
    else if (tt == ERROR) {
      strcpy(buffer, ">ERROR<");
      errorFound = 1;
    }

    // copy the buffer-value into a newly allocated string
    char *newString = malloc(strlen(buffer)+1);
    strcpy(newString, buffer);

    // append the element to the end of our list
    *insertSpot = newTagList(newString, tt, *insertSpot);
    insertSpot = &(*insertSpot)->next;

    // if an error was detected, abort the loop early
    if (errorFound) {
      return rtnVal;
    }
  }
}

// reads a single tag from input; writes the tag name into the nameBuffer;
// returns the tag type
static tagType nextTag(FILE *input, char* nameBuffer) {

  // current character we're reading
  int ch;

  // null out the nameBuffer, in case we return early (e.g., with an error)
  *nameBuffer = '\0';

  // keep skipping characters until we find a '<'
  for (;;) {
    ch = getc(input); // read character
    if (ch < 0) return NOMORE; // EOF => return "no more"
    if (ch == '<') break; // end loop when find '>'
  }

  // read the next character; if it's a '/', then read as many alphaNums
  // as we can; then return
  ch = getc(input);
  if (ch == '/') {
    // end-tag
    if (gobbleAlphaNums(input, nameBuffer)) {
      // alphanums found: return "end" tag
      return END;
    }
    else {
      // no alphanums found: return "error"
      return ERROR;
    }
  }

  // push back character into input stream
  ungetc(ch, input);

  // read as many alphanums as we can; then return apprpropriate tag
  // based on whether the next character is a '/'
  if (gobbleAlphaNums(input, nameBuffer)) {
    // found some alphanums
    ch = getc(input);
    if (ch == '/') {
      // next character is a '/': return "void" tag
      return VOID;
    }
    else {
      // next character is not a '/': return "start" tag
      return START;
    }
  }
  else {
    // no alphanums found: return "error"
    return ERROR;
  }
}
  
// Reads as many alphanums into a buffer as it can. Returns true iff
// at least one alphanum was found.
//
// WARNING: no buffer-overflow checking is done
static int gobbleAlphaNums(FILE* input, char* nameBuffer) {

  // location for writing next character
  char *spot = nameBuffer;

  // character read
  int ch;

  // loop until end of file, or until a non-alphanum is found
  for (;;) {

    // read character
    ch = getc(input);

    // if alphanum found, append to current string; otherwise
    // break out of loop
    if (isalnum(ch)) {
      *spot = ch;
      spot++;
    }
    else {
      break;
    }

    // write terminating null character
    *spot = '\0';
  }

  // if we had read an actual character (a non-alphanum), push it back
  // into the input stream
  if (ch >= 0) {
    ungetc(ch, input);
  }

  // return true iff we wrote at least one character to the buffer
  return spot != nameBuffer;
}
