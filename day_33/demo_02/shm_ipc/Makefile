.PHONY:all
all:shm_server shm_client

shm_server:shm_server.cpp
	g++ -o $@ $^ -std=c++11

shm_client:shm_client.cpp
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f shm_server shm_client