
CC=cc

test_unix: main.c bresenham.c debug-plot.c
	$(CC) -DUNIX -o $@ $^
clean:
	@rm -f  test_unix