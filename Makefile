CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.86.0/include/ -I/opt/homebrew/Cellar/sfml/2.6.1/include/
LIBDIR = -L/opt/homebrew/Cellar/boost/1.86.0/lib/ -L/opt/homebrew/Cellar/sfml/2.6.1/lib/

# Your .hpp files
DEPS = Universe.hpp CelestialBody.hpp

# Your compiled .o files
OBJECTS = Universe.o CelestialBody.o

# The name of your program
PROGRAM = NBody

.PHONY: all clean lint

all: $(PROGRAM) test $(PROGRAM).a

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

test : test.o NBody.a
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(PROGRAM).a : $(OBJECTS)
	ar rcs $@ $^

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

#command

clean:
	rm *.o $(PROGRAM) test


lint:
	cpplint *.cpp *.hpp
