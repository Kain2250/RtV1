# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/21 19:14:26 by kain2250          #+#    #+#              #
#    Updated: 2020/10/22 21:14:17 by kain2250         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Определение системных команд
NAME = rtv1

# Флаги компиляции:
GCC = gcc
CCFLAGS = -Wall -Wextra -Werror
OTHERS_FLAGS = -lm -lft -lSDL2 -lSDL2_image -lSDL2_ttf -lGL
# Список фреймворков и их пути:
FRAME_SDL2_DIR = Frameworks
FRAME_SDL2 = $(FRAME_SDL2_DIR)/SDL2.framework
FRAME_SDL2_IMAGE = $(FRAME_SDL2_DIR)/SDL2_image.framework
FRAME_SDL2_TTF = $(FRAME_SDL2_DIR)/SDL2_ttf.framework

ifeq ($(shell uname), Linux)
	FRAMEWORKS = -L /usr/bin/
	INCLUDES_SDL2 = -I /usr/local/include/
else
	FRAMEWORKS = -F Frameworks \
		-framework SDL2 \
		-framework SDL2_image \
		-framework SDL2_ttf \
		-rpath $(FRAME_SDL2_DIR)

	INCLUDES_SDL2 = -F $(FRAME_SDL2_DIR) \
	-I $(FRAME_SDL2)/Headers \
	-I $(FRAME_SDL2_IMAGE)/Headers \
	-I $(FRAME_SDL2_TTF)/Headers
endif

# Список библиотек и их пути:
LIBFT_DIRECTORY = libft

# Флаги для сборки библиотек
LIBRARIES_LIBFT = -L $(LIBFT_DIRECTORY)

# Заголовочные файлы и их пути:
INCLUDES_DIRECTORY = include/
INCLUDES_DIRECTORY_LIBFT = $(LIBFT_DIRECTORY)/includes


INCLUDES = -I$(INCLUDES_DIRECTORY) \
	-I$(INCLUDES_DIRECTORY_LIBFT) \
	$(INCLUDES_SDL2)

HEADERS_LIST = *.h

HEADERS = $(addprefix $(INCLUDES_DIRECTORY), $(HEADERS_LIST))

# Основные файлы программы и их пути:
SRC_DIRECTORY = src/
SRC_LIST = *.c \


SRC = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))

# Определение цвета вывода:
GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

# Лабуда-бу-даб-даб
.PHONY: all clean fclean re

# Основные правила сборки:
all: $(NAME)

$(NAME): $(LIBFT_DIRECTORY) $(SRC) $(HEADERS)
	@$(MAKE) -C $(LIBFT_DIRECTORY)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) $(CCFLAGS) $(SRC) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

$(LIBFT_DIRECTORY):
	@$(MAKE) -C $(LIBFT_DIRECTORY)

debug: $(LIBFT_DIRECTORY) $(SRC) $(HEADERS)
	@$(MAKE) -C $(LIBFT_DIRECTORY)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) -g $(CCFLAGS) $(SRC) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

clean:
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Исполняемый файл $(NAME) удален$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIRECTORY) fclean
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

re:
	@$(MAKE) fclean
	@$(MAKE) all
