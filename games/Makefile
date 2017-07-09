##
## Makefile for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
## 
## Made by Arthur Josso
## Login   <arthur.josso@epitech.eu>
## 
## Started on  Thu Mar  9 17:55:07 2017 Arthur Josso
## Last update Thu Apr  6 16:56:18 2017 rousse_i
##

CXX	=	g++

SNAKE	=	lib_arcade_snake.so

PACMAN	=	lib_pc.so

QIX	=	lib_arcade_qix.so

SF	=	lib_arcade_solarfox.so

ZE	=	libzelda.so

EX	=	libexample.so

INC	=	./../inc

INC2	=	./include/

CXXFLAGS	+=	-I$(INC) -I$(INC2) -Wall -W -Wextra -std=c++11 -fpic

LDFLAGS	+=	-shared

CMSRC =		sources/GameStarter.cpp	\
		sources/AGame.cpp

SKSRC	=	sources/GameSnake.cpp

PCSRC	=	sources/GamePacMan.cpp \
		sources/GamePacManGhost.cpp

QXSRC	=	sources/GameQix.cpp

SFSRC	=	sources/GameSolarFox.cpp

ZESRC	=	sources/GameZelda.cpp

EXSRC	=	sources/GameExample.cpp

CMOBJ	=	$(CMSRC:.cpp=.o)

SKOBJ	=	$(SKSRC:.cpp=.o)

PCOBJ	=	$(PCSRC:.cpp=.o)

QXOBJ	=	$(QXSRC:.cpp=.o)

SFOBJ	=	$(SFSRC:.cpp=.o)

ZEOBJ	=	$(ZESRC:.cpp=.o)

EXOBJ	=	$(EXSRC:.cpp=.o)

all:	$(CMOBJ) $(SKOBJ) $(PCOBJ) $(QXOBJ) $(SFOBJ) $(ZEOBJ) $(EXOBJ)
	@$(CXX) $(CMOBJ) $(SKOBJ) $(LDFLAGS) -o $(SNAKE)
	@$(CXX) $(CMOBJ) $(PCOBJ) $(LDFLAGS) -o $(PACMAN)
	@$(CXX) $(CMOBJ) $(QXOBJ) $(LDFLAGS) -o $(QIX)
	@$(CXX) $(CMOBJ) $(SFOBJ) $(LDFLAGS) -o $(SF)
	@$(CXX) $(CMOBJ) $(ZEOBJ) $(LDFLAGS) -o $(ZE)
#	@$(CXX) $(CMOBJ) $(EXOBJ) $(LDFLAGS) -o $(EX)


clean:
	@rm -f $(CMOBJ) $(SKOBJ) $(PCOBJ) $(QXOBJ) $(SFOBJ) $(ZEOBJ)

fclean:	clean
	@rm -f $(SNAKE) $(PACMAN) $(QIX) $(SF) $(ZE)

re:	fclean all

.PHONY:	all clean fclean re
