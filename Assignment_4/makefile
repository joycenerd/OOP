CC=g++
SOURCES=main.cpp rp.cpp packet.cpp gfgpacket.cpp fr.cpp gfg.cpp
OBJECTS=main.o rp.o packet.o gfgpacket.o fr.o gfg.o
TARGET=assignment_4

all: $(TARGET) clean
$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -std=c++11 -c $(SOURCES)
clean:
	rm -rf $(OBJECTS)