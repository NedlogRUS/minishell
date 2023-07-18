# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 19:00:48 by apanikov          #+#    #+#              #
#    Updated: 2023/07/17 15:55:49 by vtavitia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = minishell
# SRCDIR = src
# OBJDIR = obj
# INCLUDESDIR = includes
# SRCS = $(addprefix $(SRCDIR)/, main.c)
# OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
# CC = cc
# RM = rm -rf
# CFLAGS = -Wall -Wextra -Werror
# LIBFT = ./libft
# LIBFTA = $(LIBFT)/libft.a
# LIBS = -L$(LIBFT) -lft
# HEADER = $(addprefix $(INCLUDESDIR)/, minishell.h apanikov.h vtavitia.h)

# all: $(NAME) 

# $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) Makefile
# 	@ mkdir -p $(OBJDIR)
# 	@ $(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS) $(LIBFTA)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# $(LIBFTA):
# 	@$(MAKE) -C $(LIBFT)

# clean:
# 	$(RM) $(OBJS) 
# 	$(RM) $(OBJDIR)
# 	@$(MAKE) -C $(LIBFT) fclean

# fclean: clean
# 	$(RM) $(NAME)
# 	@$(MAKE) -C $(LIBFT) fclean

# re: fclean all

# .PHONY: all clean fclean re 

# Main Variables
NAME     = minishell
GCC      = gcc
CFLAGS   = -Wall -Wextra -Werror -g #-fsanitize=address
RM       = rm -rf
OUTPUT   = ./$(NAME)
LIBS     = -I./includes/ -I./readline/include
LIBS_DIR = includes

# Compiled directories
SRC = src
OBJ = obj
SUBDIRS = execute builtins parser main pipes_redirs tokenization

# Folder directions
SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

# File directions
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))
LIB_DIR = $(foreach dir, $(LIBS_DIR), $(wildcard $(dir)/*.h))

# Libft
LIBFT     = ft
LIBFT_DIR = ./lib$(LIBFT)/

# Readline Part
RDLINE        := readline
RDLINE_PATH   = $(addprefix $(shell pwd)/, $(RDLINE))
RDLINE_MAIN   = $(addprefix $(RDLINE), -main)
RDLINE_RESERV = $(addprefix $(RDLINE), -lib)
RDLINE_DIR    = ./$(RDLINE)/lib

# Colors
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m

all: readline $(NAME)
	@echo > /dev/null

bonus: all

readline: Makefile
	@if [ -d $(RDLINE) ]; then \
		make READLINE_READY; \
	else \
		make readline-util; \
	fi

readline-util:
	@echo "${YELLOW}Please wait until program compiling...${RESET}"
	@$(RM) $(RDLINE_RESERV)
	@cp -R $(RDLINE_MAIN) $(RDLINE_RESERV)
	@cd $(RDLINE_RESERV) && exec ./configure --prefix=${RDLINE_PATH}
	@make -C ./$(RDLINE_RESERV)
	@make -C ./$(RDLINE_RESERV) install
	@$(RM) $(RDLINE_RESERV)
	@make READLINE_READY

$(NAME): $(LIB_DIR) Makefile $(OBJS)
	@make WAIT_COMPILE_MSG
	@echo "${GREEN}-> Compiling LIBFT...${RESET}"
	@make -C $(LIBFT_DIR) all
	@$(GCC) -o $(NAME) $(OBJS) -g $(CFLAGS) $(LIBS) -L$(LIBFT_DIR) -l$(LIBFT) -L$(RDLINE_DIR) -l$(RDLINE) -lncurses 
	@make DONE_MSG

$(OBJ)/%.o: $(SRC)/%.c $(LIB_DIR)
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@echo "${YELLOW}Compiling $<${RESET}"
	@$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean: DELETE_OBJ_MSG
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
fclean: clean DELETE_PROGRAM_MSG
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(RDLINE)
re: fclean all

# Helper messages
READLINE_READY:
	@echo "${GREEN}Readline is Ready!${RESET}" > /dev/null
WAIT_COMPILE_MSG:
	@echo "${YELLOW}Please wait until program compiling...${RESET}"
DONE_MSG:
	@echo "${GREEN}! Minishell is ready !${RESET}"
DELETE_OBJ_MSG:
	@echo "${RED}Object files deleting...${RESET}"
DELETE_PROGRAM_MSG:
	@echo "${RED}! ATTENTION !\nMinishell is deleting...${RESET}"

.PHONY: all clean fclean re
