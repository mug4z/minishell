# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfrily <tfrily@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 11:27:07 by tfrily            #+#    #+#              #
#    Updated: 2024/04/29 11:27:09 by tfrily           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INC_DIR		=	inc/
SRC_DIR		=	src/
SRC_SUBDIRS	=	main parsing execution utils builtins
OBJ_DIR		=	obj/
DEP_DIR		=	$(OBJ_DIR)dep/
LIBFT_DIR	=	lib/libft/
READLINE_DIR = $(HOME)/.brew/opt/readline/lib
READLINE_INC_DIR = $(HOME)/.brew/opt/readline/include

MAIN_SRCS	=	main init_minishell

PARS_SRCS	=	readline parser lexer syntax_chk sanitizer expension heredoc
EXEC_SRCS	=	execution exec_utils path_search pipe_utils1 pipe_utils2 \
				command_utils1 command_utils2 redirect redirect_utils
UTILS_SRCS	=	error_utils token_utils1 token_utils2 env_utils1 env_utils2 env_utils3 sanitizer_utils \
				parser_utils1 exit_code_utils expensions_utils1 expensions_utils2 env_utils4 cd_utils \
				heredoc_utils1 heredoc_utils2 tmp_utils
BUILTIN_SRCS=	builtins echo cd pwd export export_print unset env exit

SRCS		=	$(addprefix $(SRC_DIR)main/, $(addsuffix .c, $(MAIN_SRCS))) \
				$(addprefix $(SRC_DIR)parsing/, $(addsuffix .c, $(PARS_SRCS))) \
				$(addprefix $(SRC_DIR)execution/, $(addsuffix .c, $(EXEC_SRCS))) \
				$(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS_SRCS))) \
				$(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTIN_SRCS)))

OBJS		=	$(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
DEPS		=	$(addprefix $(DEP_DIR), $(notdir $(SRCS:.c=.d)))
VPATH		=	$(addprefix $(SRC_DIR), $(SRC_SUBDIRS))

vpath %.c $(VPATH)

LIBFT		=	$(LIBFT_DIR)libft.a

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
DEP_FLAGS	=	-MMD -MP -MF $(DEP_DIR)$*.d
RM			=	rm -f

DEF_COLOR	=	\033[0;39m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m

ifeq ($(MODE), debug)
	CFLAGS += -g
else ifeq ($(MODE), sanitize)
	CFLAGS += -g -fsanitize=address
endif

all:			$(NAME)

$(NAME): 		$(LIBFT) $(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline -o $@
				@printf "$(GREEN)\n$(NAME) successfully compiled$(DEF_COLOR)\n"

$(OBJ_DIR)%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(DEP_DIR)
				@$(CC) $(CFLAGS) $(DEP_FLAGS) -I $(INC_DIR) -I$(LIBFT_DIR)/inc -I$(READLINE_INC_DIR)  -c $< -o $@
				@printf "$(YELLOW).$(DEF_COLOR)"

$(LIBFT):
				@make -C $(LIBFT_DIR) MODE=$(MODE)

clean:
				@$(RM) -r $(OBJ_DIR)
				@make -C $(LIBFT_DIR) clean

fclean:			clean
				@$(RM) $(NAME)
				@make -C $(LIBFT_DIR) fclean

re:				fclean all

-include $(DEPS)

.PHONY:			all clean fclean re


# minishell/
# 	Makefile
#	minishell (EXECUTABLE)
# 	/inc
# 		*.h
# 	/src
#		/main
# 			%.c
#		/parsing
# 			%.c
#		/execution
# 			%.c
# 	/obj
# 		/dependencies
# 			%.d
# 		%.o
# 	/lib
# 		libft/
# 			Makefile
#			libft.a
# 			inc/
# 				libft.h
# 			src/
# 				%.c
# 			obj/
# 				%.o