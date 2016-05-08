Raspberry Jam
=============

Software for a synthesizer using a Raspberry Pi and PortAudio for synthesis and an Arduino for parameter input.

Classes
------

- **Synth**: The sound-generating class. Contains a WriteFrames function which is used as the PortAudio callback.
- **ADSR**: An ADSR envelope generator.
- **FilterButterworth24db**: A 24db resonant low-pass filter class.
- **ArduinoInput**: A class for handling serial input from an Arduino, turning it into numeric values and passing it off to the WorkQueue.
- **WorkQueue**: A thread-safe producer/consumer queue for passing values from **ArduinoInput** to the **Synth** class (running on separate threads).
