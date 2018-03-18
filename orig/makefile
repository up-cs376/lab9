# -*- MakeFile -*-
# vim:ft=make:

OFILES = main.o TagList.o htmlParse.o
CC = gcc
CFLAGS = -g

htmlParse: $(OFILES)
	gcc -o htmlParse $(OFILES)

main.o: main.c htmlParse.h TagList.h
	gcc -c main.c

htmlParse.o: htmlParse.c htmlParse.h TagList.h
	gcc -c htmlParse.c

TagList.o: TagList.c htmlParse.h TagList.h
	gcc -c TagList.c

clean:
	rm $(OFILES) htmlParse
