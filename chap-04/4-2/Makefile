CC  = gcc
EXE = cp seek_io
LIB = ../../lib
CP_OBJ = cp.o
SEEK_OBJ = seek_io.o

all: cp seek_io

cp: $(CP_OBJ) $(LIB)/libmylib.a
	$(CC) -o $@ $(CP_OBJ) -L$(LIB) -lmylib

seek_io: $(SEEK_OBJ) $(LIB)/libmylib.a
	$(CC) -o $@ $(SEEK_OBJ) -L$(LIB) -lmylib

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
	echo "abc" > test/tfile
	./seek_io test/tfile s5000 wdef
	./seek_io test/tfile s100000 whij
	@echo ""
	cat test/tfile
	@echo ""
	./cp test/tfile test/tfile_cp
	@echo ""
	diff test/tfile test/tfile_cp
	@echo ""
	du test/*

cleantest:
	rm -rf test

clean:
	$(MAKE) cleantest
	rm -rf $(OBJ) $(EXE)
