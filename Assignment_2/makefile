CC=g++
SOURCES=main.cpp request.cpp resource.cpp
OBJECTS=main.o request.o resource.o
TARGET=assignment_2

all: $(TARGET) clean
$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -c $(SOURCES)

clean:
	rm -rf $(OBJECTS)
