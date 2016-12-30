# Which compiler
CC = gcc
INCLUDE = include
SOURCE = source

objects = Atom.o AVC1Atom.o AVCCAtom.o Descriptor.o DINFAtom.o DREFAtom.o ESDSAtom.o FileReader.o FREEAtom.o FTYPAtom.o HDLRAtom.o main.o MDATAtom.o MDHDAtom.o MDIAAtom.o METAAtom.o MINFAtom.o MOOVAtom.o MP4AAtom.o MP4Movie.o MVHDAtom.o SMHDAtom.o STBLAtom.o STCOAtom.o STSCAtom.o STSDAtom.o STSSAtom.o STSZAtom.o STTSAtom.o TKHDAtom.o TRAKAtom.o UDTAAtom.o URLAtom.o VMHDAtom.o

Mp4Parser: $(objects)
	$(CC) -I$(INCLUDE) -o $@ $^

%.o: $(SOURCE)/%.c
	$(CC) -c -I$(INCLUDE) -o $@ $<

clean:
	-rm Mp4Parser $(objects)
