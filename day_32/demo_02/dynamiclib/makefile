libmylib.so:mystdio.o cal.o
	gcc -share -o $@ $^

%.o:%.c
	gcc -c -fPIC $<

.PHONY:clean
clean:
	rm -rf myexe *.o mylib.tgz log1.txt

.PHONY:output
output:
	mkdir -p mylib/include
	mkdir -p mylib/lib

	cp ./*.h mylib/include
	cp ./libmylib.so mylib/lib

	tar czf mylib.tgz mylib
