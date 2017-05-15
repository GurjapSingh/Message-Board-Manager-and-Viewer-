all: a1 addauthor post post.c translator home

a1: fileParser.c
	gcc fileParser.c -Wall -ansi -g -o a1

addauthor: addauthor.o libstream.a
	gcc addauthor.o -o addauthor -lstream -L.

addauthor.o: addauthor.c stream.h stream.c
	gcc -Wall -ansi -c addauthor.c -o addauthor.o

post.c: a1 post.cc
	./a1 post.cc

libstream.a: stream.c stream.h
	gcc stream.c -std=c99 -o stream.o -c ;
	ar cr libstream.a stream.o

post: post.o stream.h stream.c
	gcc -Wall -ansi post.o -o post -lstream -L.

post.o: post.c stream.h
	gcc -Wall -ansi -c post.c -o post.o

translator: translator.c
	gcc translator.c -g -Wall -ansi  -o translator

db: db.c
	gcc db.c -ansi -g -o db.o -c;
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

home: db.c
	gcc db.c -std=c99 -g -o db.o -c -I/usr/local/Cellar/mysql/5.7.17/include;
	gcc db.o -o db -lmysqlclient -L/usr/local/Cellar/mysql/5.7.17/lib -lmysqlclient


clean:
	rm *.o;
	rm db;
	rm addauthor;
	rm translator;
	rm post;
	rm post.c;
	rm a1;
	rm libstream.a;
	rm *.html
