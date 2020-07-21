CC := clang
LIBFLAGS := -std=c11 -Os -fshort-enums -nostdlib
TESTFLAGS := -std=c11 -Os -fshort-enums

LIBFLAGS += -DINCLUDE_LOOKUP_TABLE	# disable to save 2 MB at runtime

clean:
	rm -f test utf8.o

prof: prof.c utf8.o
	${CC} ${TESTFLAGS} $^ -o $@
	time ./prof

test: test.c utf8.o	
	${CC} ${TESTFLAGS} $^ -o $@

utf8.o: utf8.c
	${CC} ${LIBFLAGS} -c $< -o $@ 