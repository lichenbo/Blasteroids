IDIR=include
CC=cl
CFLAGS=/I$(IDIR)

ODIR=obj
LDIR=lib
LIBS=allegro-5.0.10-monolith-md.lib
LFLAGS=$(LDIR)/$(LIBS)

SOURCES=blasteroids.cpp spaceship.cpp asteroid.cpp flying.cpp blast.cpp
OBJECTS=$(SOURECS:.cpp=.obj)
EXECUTABLE=blasteroids.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS)
blasteroids: blasteroids.obj
