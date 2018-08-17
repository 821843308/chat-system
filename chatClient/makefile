.PHONY:all
all:chat_client

chat_client: *.cpp *.h ../chatWindow/chatWindow.cpp ../chatWindow/chatWindow.h ../comm/data.*
	g++ $^ -o  $@ -lpthread -lncurses -ljson

.PHONY:
clean:
	rm -f chat_client




