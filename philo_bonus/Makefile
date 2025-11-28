NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
CFLAGS += -g -O0 # debug mode

SRC_DIR = src
UTILS_DIR = src/utils
INCLUDE_DIR = include
OBJ_DIR = obj

SRCS =	$(SRC_DIR)/main.c \
		$(UTILS_DIR)/atomic_utils.c \
		$(UTILS_DIR)/atou_safe.c \
		$(UTILS_DIR)/cleanup.c \
		$(UTILS_DIR)/init.c \
		$(UTILS_DIR)/input.c \
		$(UTILS_DIR)/monitor_utils.c \
		$(UTILS_DIR)/output.c \
		$(UTILS_DIR)/philo_utils.c \
		$(UTILS_DIR)/start.c \
		$(UTILS_DIR)/timing.c \
		$(UTILS_DIR)/utils.c \
		$(UTILS_DIR)/wait.c \
		$(UTILS_DIR)/xtoa.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN) $(NAME) compiled successfully!$(RESET)"

# $(@D) expands to only the dirs in the target (no files)
$(OBJ_DIR)/%.o: %.c $(INCLUDE_DIR)/bonus_philo.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE) Compiling: $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED) Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re