.PHONY:all

all:hello_r hello_w

hello_r:hello_r.c	
	gcc -o $@ $^

hello_w:hello_w.c	
	gcc -o $@ $^

clean:
	rm -f hello_w hello_r
