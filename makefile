CC = gcc
CFLAGS = -g `pkg-config --cflags gtk+-3.0`
TARGET = program.exe
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC = main.c functions.c 
# Default rule (called when you type 'make')
compile: $(TARGET)

# Rule to compile the target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)
#Run Program
run:
	./$(TARGET)