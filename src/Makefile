GCC= g++

GCCFLAG= -std=c++0x

# Gdal
GDALDIR = /sw/geosoft/gdal-1.11.2-fgdb
GDALLIB := -L$(GDALDIR)/lib -lgdal

# Target rules
All: RandomField

RandomField.o: main.c
	$(GCC) -o $@ -c $< 
io.o: io.c
	$(GCC) -I. -I$(GDALDIR)/include -o $@ -c $< 
field.o: field.c
	$(GCC) $(GCCFLAG) -o $@ -c $< 
RandomField: RandomField.o io.o field.o
	$(GCC) $(GCCFLAG) -o ../$@ $+ $(GDALLIB)
clean:
	rm -f *.o ../RandomField
