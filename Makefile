CC = gcc
TARGET = demo
OBiJECTS = $(TARGET).o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(TARGET).c -lunistring

clean:
	$(RM) $(TARGET) 
