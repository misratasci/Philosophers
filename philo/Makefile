NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS =  utils.c ft_atoi.c ft_itoa.c philo_init.c philo.c main.c actions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

git:
	@make fclean
	@git add .
	@git status
	@read -p "Enter commit message: " message; \
	git commit -m "$$message"
	@git push
	@git log

.PHONY: all clean fclean re git