CC=vc +kick13
GCC=gcc
LD=vlink
CFLAGS=-O2 -+ -I$(NDK_INC) -c -D__VBCC__ -c99
VBCC_LIBS=-L$(VBCC)/targets/m68k-kick13/lib
LDFLAGS=-lamiga -lvc -nostdlib

.PHONY : clean check
.SUFFIXES : .o .c .asm

OBJS=startup.o romtag.o libinit.o libfuncs.o file_list.o dos_compat.o dos13.o filereq.o

all: sofia.library

test: file_list_test dos_compat_test
	./file_list_test
	./dos_compat_test

clean:
	rm -f *.o sofia.library file_list_test dos_compat_test

sofia.library: $(OBJS)
	$(LD) $(VBCC_LIBS) $(LDFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $^ -c -o $@

filereq_demo: file_list.o dos_compat.o dos13.o filereq.o filereq_demo.o
	$(CC) $^ -o $@ -lamiga -lauto

file_list_test: file_list.c test/file_list_test.c chibi_test/chibi.c
	$(GCC) $^ -o $@


dos_compat_test: dos_compat.c test/dos_compat_test.c chibi_test/chibi.c
	$(GCC) $^ -o $@
