.PHONY: clean fclean all re

NAME = ft_retro
SRC = main.cpp \
	Map.cpp \
	Entity.cpp \
	Enemy.cpp \
	Missile.cpp \
	Player.cpp

OBJ = $(SRC:%.cpp=%.o)
FLAGS = -Wall -Wextra -Werror
LDFLAGS	= -lncurses

CC = c++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LDFLAGS) $^ -o $@
	@echo "==> Program [$@] compiled"

%.o: %.cpp
	@$(CC) $(FLAGS) -c $^
	@echo "==> [$<] compiled"

clean:
	@rm -f $(OBJ)
	@echo "==> Objects removed"
fclean: clean
	@rm -f $(NAME)
	@echo "==> Program [$(NAME)] removed"

re: fclean all
 
