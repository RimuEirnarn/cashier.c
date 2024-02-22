CFLAGS := -w -Wincompatible-pointer-types-discards-qualifiers -O3 -Wint-conversion

all: main clean-object

main: main.o

.PHONY: clean clean-object
clean: clean-object
	-rm main

clean-object:
	-rm *.o
