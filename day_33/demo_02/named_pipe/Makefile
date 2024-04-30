.PHONY:all

all:pipe_client pipe_server

pipe_client:pipe_client.cc
	g++ -o $@ $^ -std=c++11

pipe_server:pipe_server.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
	rm -f pipe_client pipe_server
