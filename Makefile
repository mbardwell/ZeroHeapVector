CXX = g++
CXXSTANDARD = c++20
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=$(CXXSTANDARD) -O2
BUILD ?= release

ifeq ($(BUILD),debug)
	CXXFLAGS += -fstack-usage -fsanitize=address
endif

ifdef STACK_SIZE
CXXFLAGS += -Wstack-usage=$(STACK_SIZE)
endif
ifdef CAPACITY
CXXFLAGS += -DCAPACITY=$(CAPACITY)
endif

SOURCES =
OBJECTS = $(SOURCES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	EXAMPLE = example.exe
else
	EXAMPLE = example
endif
EXAMPLE_SOURCES = example.cpp
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:.cpp=.o)

all: $(EXAMPLE)

%.o: %.cpp
	@echo "\033[0;32mCompiling into object(s)\033[0m"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXAMPLE): $(EXAMPLE_OBJECTS)
	@echo "\033[0;32mCompiling into executable(s)\033[0m"
	$(CXX) $(CXXFLAGS) -o $@ $^

stats: $(EXAMPLE)
	@echo "\033[0;32mStats\033[0m"
	@echo "Text, initialized data & uninitialized data segments" && size $(EXAMPLE_OBJECTS)
	@# Output the stack usage. Requires -fstack-usage to be enabled.
	@echo "Stack usage: " && grep "test" $(EXAMPLE_SOURCES:.cpp=.su)

static: $(EXAMPLE)
	@echo "\033[0;32mStatic Analysis\033[0m"
	clang-tidy $(EXAMPLE_SOURCES) --
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --std=$(CXXSTANDARD) --language=c++ $(EXAMPLE_SOURCES)
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --simulate-cache=yes --collect-systime=yes ./$(EXAMPLE)

clean:
	@echo "\033[0;32mCleaning\033[0m"
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(EXAMPLE) $(EXAMPLE_SOURCES:.cpp=.su)
