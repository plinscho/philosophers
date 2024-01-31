CC := gcc
CFLAGS := -Wall -Werror -Wextra -g

SRC_DIR := src
SRC_FILES := main.c input_utils.c philo_init.c philo_exit.c philo_routine.c philo_utils.c
OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
EXECUTABLE := philo


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

fclean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)
re:
	make fclean
	make all

.PHONY: all fclean
