
CC=cc

all: testplot.abs

testplot.abs: testplot.bin
	bin2abs $^ 0200 > $@

testplot.bin: testplot.o 
	pdp11-aout-objcopy -O binary $^ $@

# to get the rigt order in the binary crt0.s has to be the first file

testplot.o: crt0.s main.c bresenham.c pdp-xy11.c 
	pdp11-aout-gcc -Os -m10  -Ttext 80 -msoft-float  -nostartfiles  -nodefaultlibs  -nostdlib   $^  -o testplot.o


%.o:%.c
	$(CC) -c -o $@ $^

test_unix: main.c bresenham.c debug-plot.c
	$(CC) -DUNIX -o $@ $^
clean:
	@rm -f testplot.bin testplot.o testplot.abs test_unix