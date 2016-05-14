CC=g++
CFLAGS=-c -Wall -std=c++11 -g
LDFLAGS=-lportaudio -lportmidi
SOURCES=main.cpp Synth.cpp ADSR.cpp FilterButterworth24db.cpp ArduinoInput.cpp LFO.cpp MidiInput.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raspberrysynth

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D __platform_mac__
endif
ifneq ($(filter arm%,$(UNAME_P)),)
	CFLAGS += -D __platform_rpi__
	LDFLAGS += -lasound
	LDFLAGS += -pthread
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
