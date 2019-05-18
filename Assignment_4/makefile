CC=g++
SOURCES=main.cpp rp.cpp
OBJECTS=main.o rp.o
TARGET=assignment_4

all: $(TARGET) clean
$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -std=c++11 -c $(SOURCES)
clean:
	rm -rf $(OBJECTS)