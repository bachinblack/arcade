##
## Makefile for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
## 
## Made by Arthur Josso
## Login   <arthur.josso@epitech.eu>
## 
## Started on  Thu Mar  9 17:55:07 2017 Arthur Josso
## Last update Fri Mar 24 16:24:22 2017 Arthur Josso
##

CXX	=	g++

N_SDL	=	lib_arcade_sdl.so

N_AA	=	lib_arcade_aa.so

N_GL	=	lib_arcade_gl.so

INC	=	-I./inc/ -I../inc/

CP_PATH	=	../lib/

CXXFLAGS	+=	$(INC) -fpic -Wall -W -Wextra -std=c++11

LDFLAGS	+=	-shared

SRC	=	src/AGraphix.cpp \
		src/PixArray.cpp \
		src/PutText.cpp

SRC_SDL	=	src/GraphixSDL.cpp
SRC_AA	=	src/GraphixAA.cpp
SRC_GL	=	src/GraphixGL.cpp

OBJ	=	$(SRC:.cpp=.o)
OBJ_SDL	=	$(SRC_SDL:.cpp=.o)
OBJ_AA	=	$(SRC_AA:.cpp=.o)
OBJ_GL	=	$(SRC_GL:.cpp=.o)

all:	$(OBJ) $(N_SDL) $(N_GL) $(N_AA)

$(N_SDL):
	$(CXX) -c $(SRC_SDL) -o $(OBJ_SDL) $(CXXFLAGS) `sdl-config --cflags`
	@$(CXX) $(OBJ) $(OBJ_SDL) -o $(N_SDL) $(LDFLAGS) `sdl-config --libs`
	@cp $(N_SDL) $(CP_PATH)

$(N_GL):
	$(CXX) -c $(SRC_GL) -o $(OBJ_GL) $(CXXFLAGS)
	@$(CXX) $(OBJ) $(OBJ_GL) -o $(N_GL) $(LDFLAGS) -lGL -lSDL2
	@cp $(N_GL) $(CP_PATH)

$(N_AA):
	$(CXX) -c $(SRC_AA) -o  $(OBJ_AA) $(CXXFLAGS)
	@$(CXX) $(OBJ) $(OBJ_AA) -o $(N_AA) $(LDFLAGS) `aalib-config --libs`
	@cp $(N_AA) $(CP_PATH)

clean:
	@rm -f $(OBJ) $(OBJ_SDL) $(OBJ_AA) $(OBJ_GL)

fclean:	clean
	@rm -f $(N_SDL) $(CP_PATH)$(N_SDL) $(N_GL) $(CP_PATH)$(N_GL) $(N_AA) $(CP_PATH)$(N_AA)

re:	fclean all

.PHONY:	all clean fclean re
