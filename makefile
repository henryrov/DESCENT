ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

test/calculator: token.o expression.o descent.o test/calculator.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm
	./test/calculator

install: token.o expression.o descent.o
	ar rcs libdescent.a $^
	mv libdescent.a $(PREFIX)/lib/
	cp descent.h $(PREFIX)/include/

uninstall:
	rm $(PREFIX)/lib/libdescent.a $(PREFIX)/include/descent.h

token.o: token.c
	$(CC) $(CFLAGS) -c -o $@ $<

expression.o: expression.c
	$(CC) $(CFLAGS) -c -o $@ $<

descent.o: descent.c
	$(CC) $(CFLAGS) -c -o $@ $<

test/calculator.o: test/calculator.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) test/calculator test/calculator.o token.o expression.o
