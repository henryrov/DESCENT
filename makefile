ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

.PHONY: all clean

all: src/descent.o

fuzz: src/token.c src/expression.c src/descent.c src/test/fuzz.cpp
	clang -g -fsanitize=address,fuzzer $^ -o src/test/$@
	./src/test/fuzz -max_len=1000

tests: src/token.o src/expression.o src/descent.o src/test/tests.o
	$(CC) $(LDFLAGS) -o src/test/$@ $^ -lm -lcunit
	./src/test/tests

calculator: src/token.o src/expression.o src/descent.o src/test/calculator.o
	$(CC) $(LDFLAGS) -o src/test/$@ $^ -lm
	./src/test/calculator

install: src/token.o src/expression.o src/descent.o
	ar rcs src/libdescent.a $^
	mv src/libdescent.a $(PREFIX)/lib/
	cp src/descent.h $(PREFIX)/include/

uninstall:
	rm $(PREFIX)/lib/libdescent.a $(PREFIX)/include/descent.h

src/token.o: src/token.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/expression.o: src/expression.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/descent.o: src/descent.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/test/calculator.o: src/test/calculator.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/test/tests.o: src/test/tests.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) src/test/tests src/test/fuzz src/test/calculator src/test/tests.o src/test/calculator.o src/token.o src/expression.o src/descent.o
