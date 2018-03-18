// A linked list of html-tags.
// - name of the tag
// - type of the tag
// - next-field

    #ifndef  	 TAGLIST_H   	

        #define TAGLIST_H

#include "htmlParse.h"

// definition of TagList struct
typedef struct TagList {
  char* name; // name of tag
  tagType type; // type of tag
  struct TagList* next; // next-field
} TagList;

// constructor-function for tag-list: returns a pointer to a newly
// allocated and initialized tag-list node
extern TagList* newTagList(char *name, tagType type, TagList *next);

#endif    // end of conditional expression



// the last line of the file


