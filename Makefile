CC=g++
CFLAGS=-c -Wall -std=c++11 -g
LDFLAGS=-lportaudio -lportmidi -lasound
SOURCES=main.cpp Synth.cpp ADSR.cpp FilterButterworth24db.cpp ArduinoInput.cpp LFO.cpp MidiInput.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raspberrysynth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
