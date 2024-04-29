# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 11:39:18 by bgolding          #+#    #+#              #
#    Updated: 2024/04/23 14:06:39 by tfrily           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

INC_DIR		=	inc/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
DEP_DIR		=	$(OBJ_DIR)dep/

SRCS		=	ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isascii \
				ft_isprint \
				ft_strlen \
				ft_memset \
				ft_bzero \
				ft_memcpy \
				ft_memmove \
				ft_strlcpy \
				ft_strlcat \
				ft_toupper \
				ft_tolower \
				ft_strchr \
				ft_strrchr \
				ft_strcmp \
				ft_strncmp \
				ft_memchr \
				ft_memcmp \
				ft_strnstr \
				ft_atoi \
				ft_calloc \
				ft_strdup \
				ft_substr \
				ft_strjoin \
				ft_strtrim \
				ft_split \
				ft_itoa \
				ft_strmapi \
				ft_striteri \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_lstnew \
				ft_lstadd_front \
				ft_lstsize \
				ft_lstlast \
				ft_lstadd_back \
				ft_lstdelone \
				ft_lstclear \
				ft_lstiter \
				ft_lstmap \
				ft_isspace \
				ft_atoi_base \
				ft_strcpy
			
OBJS		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))
DEPS		=	$(addprefix $(DEP_DIR), $(addsuffix .d, $(SRCS)))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
DEP_FLAGS	=	-MMD -MF $(DEP_DIR)$*.d
RM			=	rm -f
AR			=	ar -rc

DEF_COLOR	=	\033[0;39m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m

ifeq ($(MODE), debug)
	CFLAGS += -g
else ifeq ($(MODE), sanitize)
	CFLAGS += -g -fsanitize=address
endif

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(AR) $@ $(OBJS)
				@printf "$(GREEN)\n$(NAME) successfully compiled$(DEF_COLOR)\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(DEP_DIR)
				@$(CC) $(CFLAGS) $(DEP_FLAGS) -I $(INC_DIR) -c $< -o $@
				@printf "$(YELLOW).$(DEF_COLOR)"

clean:
				@$(RM) -rf $(OBJ_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

-include $(DEPS)

.PHONY:			all clean fclean re