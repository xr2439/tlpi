CC  = gcc
EXE = tee
LIB = ../../lib
OBJ = tee.o

all:$(OBJ) $(LIB)/libmylib.a
	$(CC) -o $(EXE) $(OBJ) -L$(LIB) -lmylib

%.o:%.c
	$(CC) -c $^ -o $@ -I$(LIB)

$(LIB)/libmylib.a:
	cd $(LIB) && make

.PHONY: all clean cleantest test

test:
	@$(MAKE) all
	@$(MAKE) cleantest
	@mkdir test
	@echo ""
	echo "Hello" | ./tee test/hello.txt
	@echo ""
	echo "World" | ./tee test/hello.txt
	@echo ""
	echo "Hello World" | ./tee -a test/hello.txt
	@echo ""
	@echo "The content of test/hello.txt should be:"
	@echo "World"
	@echo "Hello World"
	@echo ""
	cat ./test/hello.txt

cleantest:
	rm -rf test

clean:
	$(MAKE) cleantest
	rm -rf $(OBJ) $(EXE)
