np: start_p.o projection.o setdata.o coords.o  wrapper.o regexfile.o recurse.o pool.o node.o  node2.o hashlist.o hashlist2.o hashalgo.o community.o distribute.o relpath.o queue.o
	gcc -o np start_p.o projection.o setdata.o coords.o  wrapper.o regexfile.o recurse.o pool.o node.o node2.o hashlist.o hashlist2.o hashalgo.o community.o distribute.o relpath.o queue.o -I /usr/include/include/ -L /usr/lib64/ -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm  -lstdc++ -ljpeg

start_p.o: start_p.c
	gcc -c start_p.c -I /usr/include/include/ -L /usr/lib64/ -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm  -lstdc++ -ljpeg

projection.o : projection.c
	gcc -c projection.c -I /usr/include/include/ -L /usr/lib64/ -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm  -lstdc++ -ljpeg

setfile.o: setdata.c community.c
	gcc -c setdata.c community.c

community.o: community.c 
	gcc -c community.c

coords.o: coords.c
	gcc -c coords.c

recurse.o: recurse.c 
	gcc -c recurse.c

wrapper.o:wrapper.c wrapper.h
	gcc -c wrapper.c wrapper.h

regexfile.o:regexfile.c regexfile.h node.h
	gcc -c regexfile.c regexfile.h node.h

pool.o: pool.c pool.h
	gcc -c pool.c pool.h

node.o: node.c node.h
	gcc -c node.c node.h

node2.o: node2.c node2.h
	gcc -c node2.c node2.h

hashlist.o: hashlist.c 
	gcc -c hashlist.c

hashalgo.o: hashalgo.c
	gcc -c hashalgo.c


distribute.o: distribute.c
	gcc -c distribute.c

relpath.o: relpath.c
	gcc -c relpath.c

queue.o: queue.c
	gcc -c queue.c

Install:
	cp np /bin
Clean:
	rm -f *.gch *.o
