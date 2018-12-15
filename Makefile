

all: testplot.abs

testplot.abs: testplot.bin
	bin2abs $^ 0200 > $@

testplot.bin: testplot.o 
	pdp11-aout-objcopy -O binary $^ $@

testplot.o: plot.c crt0.s
	pdp11-aout-gcc -Os -m10  -Ttext 100 -msoft-float  -nostartfiles  -nodefaultlibs  -nostdlib   $^  -o testplot.o

clean:
	@rm -f testplot.bin testplot.o testplot.abs