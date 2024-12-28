
CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = hashset.c
OBJ = $(SRC:.c=.o)
LIB = libhashset.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)

install:
	@echo "Installing library..."
	@mkdir -p /usr/local/include
	@mkdir -p /usr/local/lib
	@cp hashset.h /usr/local/include/
	@cp $(LIB) /usr/local/lib/
	@echo "Library installed successfully!"

uninstall:
	@echo "Uninstalling library..."
	@rm -f /usr/local/include/hashset.h
	@rm -f /usr/local/lib/$(LIB)
	@echo "Library uninstalled successfully!"
