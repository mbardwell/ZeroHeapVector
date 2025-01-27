CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23

LIBRARY = libstack_vector.a
SOURCES =
OBJECTS = $(SOURCES:.cpp=.o)

EXAMPLE = example
EXAMPLE_SOURCES = example.cpp
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:.cpp=.o)

all: $(LIBRARY) $(EXAMPLE)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

$(EXAMPLE): $(EXAMPLE_OBJECTS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(LIBRARY) $(EXAMPLE)
