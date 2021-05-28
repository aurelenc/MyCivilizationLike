##
## github.com/aurelenc, 2021
## MyCivilizationLike
## File description:
## my_civlike
##

MAIN	=	src/main.c

SRC	=	src/my_civlike.c	\
		src/display/display_civ.c	\
		src/display/display_tiles.c	\
		src/events/camera.c	\
		src/events/events_civ.c	\
		src/init/init_civ.c	\
		src/world/load_save.c \

OBJ	=	$(MAIN:.c=.o) $(SRC:.c=.o)

NAME	=	my_civlike

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

CFLAGS	=	-I./include -Wshadow -Wextra -Wall

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

tests_run:
	$(MAKE) -C tests/
	./tests/tests_units_tests

debug:  CFLAGS += -g

debug:  fclean $(NAME);

.PHONY	:	all clean fclean re
