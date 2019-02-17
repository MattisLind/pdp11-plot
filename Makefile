
CC=cc

ALL=R2D2-plot-unix DeathStar-plot-unix Wizzard-plot-unix TekBug-plot-unix Snoopy-plot-unix Nurd-plot-unix MickeyMouse-plot-unix LaserGun-plot-unix Grinch-plot-unix Dragon-plot-unix CheshireCat-plot-unix Bump-plot-unix

SRC=main.c bresenham.c debug-plot.c

HERSHEYSRC=Hershey-main.c bresenham.c debug-plot.c

all: $(ALL)


%: $(HERSHEYSRC)  %.h
	$(CC) -DUNIX  -o $@ $(HERSHEYSRC) -DPLOTFILE_H='"$(word 4, $^)"'	

%-plot-unix: $(SRC)  %.h
	$(CC) -DUNIX  -o $@ $(SRC) -DPLOTFILE_H='"$(word 4, $^)"'	


clean:
	@rm -f  $(ALL)