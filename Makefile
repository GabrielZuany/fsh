CC = gcc
CFLAGS = -Wall -g
EXEC = main
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/code/*.c)

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)
clean:
	rm -f $(EXEC)
