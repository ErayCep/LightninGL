CC = g++
LIBS = -lGL -lglfw 
INCLUDES = ./include/glad.o
OBJS = ./src/main.cpp
OUTPUT = ./build/output

all: $(OBJS) 
	$(CC) $(OBJS) $(INCLUDES) $(LIBS) -o $(OUTPUT)
	$(OUTPUT)

clean:
	rm -f $(OUTPUT)
