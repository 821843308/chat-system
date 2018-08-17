
.PHONY:all
all:chat_server

chat_server:chat_server.cpp udp_server.cpp udp_server.h ../data_pool/data_pool.cpp ../data_pool/data_pool.h
	g++ -o $@ $^ -lpthread -ljson

.PHONY:clean
clean:
	rm -f chat_server
