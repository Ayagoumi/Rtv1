# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/25 10:38:14 by ayagoumi          #+#    #+#              #
#    Updated: 2021/03/13 19:11:40 by yoouali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = rtv1

DEF = 		\x1B[1;0m
RED = 		\x1B[1;31m
PURPLE =	\x1B[1;34m
BLUE = 		\x1B[1;96m
GREEN = 	\x1B[1;32m
SILVER = 	\x1B[1;90m
YELLOW = 	\x1B[1;33m

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB = -lft
PATH_LIB = libft/

SDLF = -I SDL/SDL2.framework/Headers

INC = inc/rtv1.h
INCLIB = libft/libft.h
INC_PATH = inc/

PATH_SRC = srcs/
PATH_WIN = $(PATH_SRC)window/
PATH_EVENT= $(PATH_SRC)events/
PATH_VEC = $(PATH_SRC)vec_operations/
PATH_XML = $(PATH_SRC)xml/
PATH_RAYCAST = $(PATH_SRC)raycast/
PATH_OBJ = obj/

SRC =				main.c


SRC_WIN =			sdl_init.c

SRC_EVENT = 		events.c


SRC_VEC = 			operations.c \
					operations2.c \
					map.c

SRC_XML =			check_file.c\
					color.c\
					data.c\
					data2.c\
					last.c\
					leak.c\
					load.c\
					object.c\
					rule.c\
					xml.c

SRC_RAYCAST =		camera.c\
					raycast.c\
					color_object.c\
					intersect.c\
					phong_coloring.c\
					surface_normal.c

FRAM = -lmlx -framework OpenGL -framework AppKit -framework OpenCL  -framework SDL2 -F ./SDL/ -framework SDL2_mixer -F ./SDL  -framework SDL2_image -F ./SDL -framework SDL2_ttf -F ./SDL -rpath @loader_path/SDL -lz

OBJ := $(addprefix $(PATH_OBJ), $(SRC:.c=.o))\
	$(addprefix $(PATH_OBJ), $(SRC_WIN:.c=.o))\
	$(addprefix $(PATH_OBJ), $(SRC_EVENT:.c=.o))\
	$(addprefix $(PATH_OBJ), $(SRC_VEC:.c=.o))\
	$(addprefix $(PATH_OBJ), $(SRC_XML:.c=.o))\
	$(addprefix $(PATH_OBJ), $(SRC_RAYCAST:.c=.o))

define to_obj
@mkdir -p $(PATH_OBJ)
@$(CC) $(CFLAGS) -c $1 -o $2 -I $(INC_PATH) -I $(PATH_LIB) $(SDLF)

@printf "$(SILVER)[$(PURPLE)Object file$(BLUE) $(notdir $2)$(SILVER)] $(GREEN)Created.$(DEF)\n"
endef

define to_binary
@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(PATH_LIB) $(LIB) $(FRAM) -I $(INC_PATH) -I $(PATH_LIB) $(SDLF)
@printf "$(SILVER)[$(PURPLE)Binary file$(BLUE) $(notdir $(NAME))$(SILVER)] $(GREEN)Created.$(DEF)\n\n"
endef

define ft_clean
@rm -rf $1
@printf "$(SILVER)[$(PURPLE)$1$(YELLOW)$2$(SILVER)] $(RED)deleted.$(DEF)\n\n"
endef

all: $(NAME)

$(NAME) : $(OBJ)
	@make --no-print-directory -C $(PATH_LIB)
	@$(call to_binary)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

$(PATH_OBJ)%.o: $(PATH_WIN)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

$(PATH_OBJ)%.o: $(PATH_EVENT)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

$(PATH_OBJ)%.o: $(PATH_VEC)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

$(PATH_OBJ)%.o: $(PATH_XML)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

$(PATH_OBJ)%.o: $(PATH_RAYCAST)%.c $(INC) $(INCLIB)
	@$(call to_obj, $<, $@)

clean:
	@make clean --no-print-directory -C $(PATH_LIB)
	@$(call ft_clean,$(OBJ))
	@rm -rf $(PATH_OBJ)

fclean: clean
	@make fclean --no-print-directory -C $(PATH_LIB)
	@$(call ft_clean, $(NAME))

re: fclean all

.PHONY: re fclean clean all
