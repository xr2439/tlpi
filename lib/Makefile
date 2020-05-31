CC = gcc
OBJ = error_functions.o get_num.o
LIB = mylib.a

all:$(OBJ)
	ar rcs lib$(LIB) $^

%.o:%.c
	$(CC) -c $^ -o $@

.PHONY:clean

clean:
	rm -rf $(OBJ) *.a
