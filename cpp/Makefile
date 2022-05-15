CC = clang++
CFLAGS = -Wall
EXEC_NAME = wordle
INCLUDES = -ISFML-2.5.1/include
LIBS = -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
OBJ_FILES = main.o dictionary.o
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)
	$(shell) export LD_LIBRARY_PATH=SFML-2.5.1/lib && ./$(EXEC_NAME)

run : all

clean:
	rm $(OBJ_FILES)
fclean: clean
	rm $(EXEC_NAME)
re: fclean all

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<