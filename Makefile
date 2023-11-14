CC	= vc +kick13
CFLAGS = -Iinclude -I$(NDK_INC)

all: sofialib_demo

clean:
	rm -f *.o sofialib_demo

sofialib_demo: sofialib_demo.c
	$(CC) $(CFLAGS) -lauto -lamiga -o $@ $^

