# Declaration of variables
CC = gcc
CC_FLAGS = -w
LIBS_FLAGS = $$(pkg-config --cflags --libs gtk+-3.0)
 
# File names
EXEC = mickye
SOURCES = $(wildcard src/**/*.c src/*.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS_FLAGS) -o $(EXEC)
 
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $(LIBS_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)