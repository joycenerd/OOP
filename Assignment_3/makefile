CC=g++
SOURCES=main.cpp node.cpp packet.cpp
OBJECTS=main.o node.o packet.o
TARGET=assignment_3

all: $(TARGET) clean
$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -std=c++11 -c $(SOURCES)
clean:
	rm -rf $(OBJECTS)