CC = clang++
CFLAGS = -Wall
EXEC_NAME = wordle
INCLUDES = -ISFML-2.5.1/include
LIBS = -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
OBJ_FILES = main.o dictionary.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	SFMLURL = https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-linux-gcc-64-bit.tar.gz
endif
ifeq ($(UNAME_S),Darwin)
	SFMLURL = https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-macOS-clang.tar.gz
endif

SFMLFOLDER = SFML-2.5.1/

all: $(SFMLFOLDER) $(EXEC_NAME)
	$(shell) export LD_LIBRARY_PATH=SFML-2.5.1/lib && ./$(EXEC_NAME)

$(SFMLFOLDER):
	echo "Installing SFML lib.."; \
	wget $(SFMLURL) -O SFML.tar.gz; \
	tar -xvf SFML.tar.gz; \
	rm SFML.tar.gz; \
	echo "SFML lib done"; \

run : all

clean:
	rm -f $(OBJ_FILES)
fclean: clean
	rm -f $(EXEC_NAME)
re: fclean all

cleanlib: fclean
	rm -rf SFML-2.5.1/

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
