processbar: main.o processbar.o
	gcc -o $@ $^

main.o: main.c
	gcc -c main.c

processbar.o: processbar.c
	gcc -c processbar.c

.PHONY: clean
clean:
	rm -f processbar.o main.o processbar
