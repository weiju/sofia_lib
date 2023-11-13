CC	= vc +kick13
CFLAGS = -Iinclude -I$(NDK_INC)

all: test_sofialib sofialib_demo

clean:
	rm -f *.o test_sofialib

test_sofialib: test_sofialib.c
	$(CC) $(CFLAGS) -lauto -lamiga -o $@ $^

sofialib_demo: sofialib_demo.c
	$(CC) $(CFLAGS) -lauto -lamiga -o $@ $^

