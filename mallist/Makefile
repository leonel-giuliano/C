CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# Source files
SRC = mallist.c

# Object files
OBJ = $(SRC:.c=.o)

# Target names
STATIC_LIB = libmallist.a
DYNAMIC_LIB = libmallist.dll

all: $(STATIC_LIB) $(DYNAMIC_LIB)

# Rule for static library
$(STATIC_LIB): $(OBJ)
	ar rcs $@ $(OBJ)

# Rule for dynamic library
$(DYNAMIC_LIB): $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

# Rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(STATIC_LIB) $(DYNAMIC_LIB)
