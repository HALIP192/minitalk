OBJ_DIR	=	obj
SRC_DIR	=	src

SOURCES = 	server \
			client \
			client_utils
			
OBJ = ${addprefix $(OBJ_DIR)/,$(SOURCES:=.o)}
Header = src/client.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(OBJ_DIR) server client

$(OBJ_DIR):
	mkdir -p $@

bonus: server client

server: obj/server.o
	$(CC) -o $@ $<

client:
	$(CC) -o $@ src/client.c src/client_utils.c

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f server client

re: fclean all

.PHONY: all bonus clean fclean re
