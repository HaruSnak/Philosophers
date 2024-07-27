NAME = philo
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -fsanitize=leak
OBJ_DIR = obj/
SRC_DIR = srcs/

SRC_1 = srcs/philo.c \

SRC_2 =	srcs/body/conditions.c \
        srcs/body/routine.c \
        srcs/errors/errors.c \
        srcs/errors/verification.c \
        srcs/tools/utils.c \
            
OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}

.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

${NAME}: ${OBJ_1} ${OBJ_2}
	@echo "Compiling $(NAME)..."
	@${CC} ${FLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME}
	@echo "$(NAME) compiled successfully."

all: ${NAME}

clean:
	@echo "Cleaning object files..."
	@${RM} ${OBJ_1} ${OBJ_2}
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning executable..."
	@${RM} ${NAME}
	@echo "Executable cleaned."

re: fclean all

.PHONY: all clean fclean re