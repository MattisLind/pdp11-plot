### Tektronix Fast graphics demo plots

These plot files were copied from [the Github repo of Monty McGraw](https://github.com/mmcgraw74/Tektronix-4051-4052-4054-Program-Files/tree/master/FastGraphics4051).

The format of the files are three byte tuples specifying the X and Y 10 bit coordinates and the type of movement. Either Move or Line.

The format is 7 bit so the MSB is not used. 

First byte contains the three top bits of each coordinate and the command.
Bit 0-2 is the Y coordinate bits 7-9
bit 3-6 is the X coordinate bits 7-9
bit 7 is the command bit. If 1 it is a move operation and if 0 it is a line (draw) operation.

Second byte contain the x coordinate.
Bits 0-6 is mappad to the x coordinat bits 0-6.

Thrid byte contain the y coordinate.
Bits 0-6 is mapped to the y corrdinate bits 0-6.

This give a format that can be easily parsed and drawn on any device. The tool is used to create C source code header files from the binary files.

```
tekfast2c < <input binary file> > <output C header file>
```

 