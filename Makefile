CC = gcc
SRC = $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)
LIB = lib/libcontainers.so
BIN = test
CFLAGS = -Wall -Wextra -Werror -pedantic -fPIC

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -O3 -c $< -o $@

$(LIB): $(OBJ)
	$(CC) $(OBJ) -shared -o $(LIB)

$(BIN): $(LIB)
	$(CC) src/test.c -o $(BIN) -Llib -lcontainers -Iinclude -Wl,-rpath,lib

.PHONY: clean install
clean:
	@rm $(OBJ)
	@rm $(LIB)
	@rm $(BIN)
install:
	@cp -r include/containers /home/leaf/.local/include
	@cp $(LIB) /home/leaf/.local/lib
