// TagList functions

#include <stdlib.h>
#include "TagList.h"

// constructor-function for tag-list: returns a pointer to a newly
// allocated and initialized tag-list node
TagList* newTagList(char *name, tagType type, TagList *next) {
  // allocate
  TagList*  rtnVal = malloc(sizeof(TagList));

  // initialize from parameters
  rtnVal->name = name;
  rtnVal->type = type;
  rtnVal->next = next;

  // return pointer
  return rtnVal;
}
