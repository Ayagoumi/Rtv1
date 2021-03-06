# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 06:06:14 by mzaboub           #+#    #+#              #
#    Updated: 2021/03/06 11:19:02 by ayagoumi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

DEF = 		\x1B[1;0m
RED = 		\x1B[1;31m
PURPLE =	\x1B[1;34m
BLUE = 		\x1B[1;96m
GREEN = 	\x1B[1;32m
SILVER = 	\x1B[1;90m
YELLOW = 	\x1B[1;33m

SRC_PATH= .
SRC_FILES= ft_atoi.c  	ft_bzero.c		ft_charinword.c	ft_isalnum.c	\
			ft_isalpha.c	ft_isascii.c	ft_isdigit.c	ft_isprime.c 	\
			ft_isprint.c 	ft_itoa.c 		ft_lstadd.c  	ft_lstdel.c		\
			ft_lstiter.c	ft_lstmap.c		ft_lstnew.c		ft_lstsize.c 	\
			ft_lstsplit.c	ft_memalloc.c	ft_memccpy.c	ft_memchr.c 	\
			ft_memcmp.c	ft_memcpy.c		ft_memcpynull.c	ft_memdel.c 	\
			ft_memmove.c	ft_memset.c		ft_putchar.c	ft_putchar_fd.c \
			ft_putendl.c	ft_putendl_fd.c	ft_putnbr.c		ft_putnbr_fd.c	\
			ft_putstr.c	ft_putstr_fd.c	ft_sqrt.c		ft_strcat.c		\
			ft_strchr.c	ft_strclr.c		ft_strcmp.c		ft_strcpy.c		\
			ft_strdel.c	ft_strdup.c		ft_strequ.c		ft_striter.c	\
			ft_striteri.c	ft_strjoin.c	ft_strlcat.c	ft_strlen.c		\
			ft_strmap.c	ft_strmapi.c	ft_strncat.c	ft_strncmp.c 	\
			ft_strncpy.c	ft_strnequ.c	ft_strnew.c		ft_strnstr.c 	\
			ft_strrchr.c	ft_strrev.c		ft_strsplit.c	ft_strstr.c 	\
			ft_strsub.c	ft_strtrim.c	ft_tolower.c	ft_toupper.c 	\
			get_next_line.c	ft_lstdelone.c	ft_atoi_base.c ft_split_whitespaces.c \
			upper_case.c

SRC= $(addprefix $(SRC_PATH)/, $(SRC_FILES))


OBJ_PATH= obj
OBJ_NAME= $(SRC_FILES:.c=.o)
OBJ= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))


CFLAGS=  -Wall -Wextra -Werror
CC= gcc
HDR_FLAGS= -I.


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(SILVER)[$(YELLOW)libft$(BLUE)$(notdir $2)$(SILVER)]$(GREEN) library compilled.$(DEF)\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(HDR_FLAGS) -o $@ -c $<


clean:
	@rm -fr $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "$(SILVER)[$(YELLOW)libft$(BLUE)$(notdir $2)$(SILVER)]$(RED) files deleted.$(DEF)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(SILVER)[$(YELLOW)libft$(BLUE)$(notdir $2)$(SILVER)]$(RED) library deleted.$(DEF)\n"

re: fclean all

