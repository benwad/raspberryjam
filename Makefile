CC=clang++
CFLAGS=-c -Wall
LDFLAGS=-lportaudio -lasound
SOURCES=main.cpp Synth.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raspberrysynth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
