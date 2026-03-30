CC      = gcc
CFLAGS  = -Wall -Wextra -I include -g
LDFLAGS = -fsanitize=address
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:src/%.c=build/%.o)
TARGET  = build/main

all: $(TARGET)

run: all 
	./build/main

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/