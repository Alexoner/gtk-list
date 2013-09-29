CFLAGS= -g -Wall `pkg-config --cflags --libs gtk+-2.0`
CC=gcc

forest: forest.o linkedlist.o gui.o callback.o
	$(CC) $^ -o $@  $(CFLAGS)

forest.o: forest.c define.h
	$(CC) -c forest.c $(CFLAGS)
linkedlist.o:linkedlist.c define.h
	$(CC) -c linkedlist.c  $(CFLAGS)
gui.o: gui.c define.h
	$(CC) -c gui.c $(CFLAGS)
callback.o: callback.c define.h 
	$(CC) -c callback.c $(CFLAGS)
gtest:gtest.c
	$(CC) gtest.c -o gtest $(CFLAGS)

cjy-ks: cjy-ks.c
	$(CC) cjy-ks.c -o cjy-ks $(CFLAGS)

.PHONY:clean
clean:
	@echo "cleaning source tree"
	- rm  *.o

