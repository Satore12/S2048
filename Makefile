LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -no-pie
CFLAGS=-c -I./headers -Wall -Wextra -Werror
CC=g++
SRC:=$(wildcard src/*.cpp)
OBJ:=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))

EXECUTABLE=S2048

all: $(SRC) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXECUTABLE)
	
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm $(OBJ) $(EXECUTABLE)
