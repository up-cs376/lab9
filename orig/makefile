# -*- MakeFile -*-
# vim:ft=make:

OFILES = main.o TagList.o htmlParse.o
CC = gcc
CFLAGS = -g

htmlParse: $(OFILES)
main.o: htmlParse.h TagList.h
htmlParse.o: htmlParse.h TagList.h
TagList.o: htmlParse.h TagList.h

clean:
	/bin/rm -f $(OFILES) htmlParse
