NAME1 = server
NAME2 = client
SRC_DIR	=	src

SRC1 = 	server \
			server_utils

SRC2 = client \
		client_utils

SRC1B = server_bonus \
			server_utils_bonus
SRC2B = client_bonus \
			client_utils_bonus
			
OBJ1 = ${addprefix $(SRC_DIR)/,$(SRC1:=.o)}
OBJ2 = ${addprefix $(SRC_DIR)/,$(SRC2:=.o)}
OBJ1B = ${addprefix $(SRC_DIR)/,$(SRC1B:=.o)}
OBJ2B = ${addprefix $(SRC_DIR)/,$(SRC2B:=.o)}
Header = src/client.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME1): ${OBJ1}
	${CC} ${OBJ1} -o ${NAME1}

$(NAME2): ${OBJ2}
	${CC} ${OBJ2} -o ${NAME2}	

all: ${NAME1} ${NAME2}

bonus: all
	${CC} ${OBJ1B} -o ${NAME1}
	${CC} ${OBJ2B} -o ${NAME2}

clean:
	rm -f ${OBJ1}
	rm -f ${OBJ2}
	rm -f ${OBJ1B}
	rm -f $(OBJ2B)

fclean: clean
	rm -f ${NAME1} ${NAME2}

re: fclean all

.PHONY: all bonus clean fclean re
