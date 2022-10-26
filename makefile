CC = g++
CPPFLAGS = -std=c++11 -g -Wall
DEPS = driver.h party.h stack.h queue.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

app: driver.o party.o stack.o queue.o
	$(CC) -o app driver.o party.o stack.o queue.o

.PHONY: clean
clean:
	$(info -- cleaning up  --)
	rm -f *.o
	rm -f app
