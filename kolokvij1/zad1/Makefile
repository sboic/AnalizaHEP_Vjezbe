CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Generator.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

generate: generate.o Generator.o
	$(CC) $(LDFLAGS) -o generate generate.o Generator.o

clean:
	rm -rf *.o generate