
PLOTHEADERS=File03.h File04.h File05.h File06.h File07.h File08.h File09.h File10.h File11.h File12.h File13.h File14.h File15.h

all: $(PLOTHEADERS)

tekfast2c: tekfast2c.c
	cc -o $@ $<


%.h: %.bin tekfast2c
	./tekfast2c < $< > $@

