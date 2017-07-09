##
## Makefile for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
## 
## Made by Arthur Josso
## Login   <arthur.josso@epitech.eu>
## 
## Started on  Thu Mar  9 17:55:07 2017 Arthur Josso
## Last update Mon Apr  3 18:23:26 2017 rousse_i
##

CXX	=	g++

NAME	=	arcade

INC	=	./inc/

GLIBS	=	./libs/

GAMES	=	./games/

ECHO	=	/bin/echo -e

MAN	=	./doc/arcade.1.gz

CXXFLAGS	+=	-I$(INC) -Wall -W -Wextra -std=c++11

LDFLAGS	+=	-ldl

SRC	=	src/main.cpp \
		src/GraphixManager.cpp \
		src/GameManager.cpp \
		src/Arcade.cpp \
		src/Menu.cpp

OBJ	=	$(SRC:.cpp=.o)

all:	$(OBJ)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)
	make -C $(GAMES)

full:	all
	make -C $(GLIBS)

clean:
	@rm -f $(OBJ)
	make clean -C $(GLIBS)
	make clean -C $(GAMES)

fclean:	clean
	@rm -f $(NAME)
	make fclean -C $(GLIBS)
	make fclean -C $(GAMES)

re:	fclean all

man:
	@$(ECHO) "\033[1;32mCopying the man page for arcade into /usr/share/man/man1\033[00m"
	@cp $(MAN) /usr/share/man/man1


.PHONY:	all clean fclean re graph
