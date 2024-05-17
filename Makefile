CC = gcc
TARGET = demo

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(TARGET).c $(LINKFLAGS) 

clean:
	$(RM) $(TARGET) 
