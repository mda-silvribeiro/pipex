NAME			=	pipex

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SAN				=  -fsanitize=address
RM				=	rm -rf

PIPEX			=	srcs/utils.c \
					srcs/utils2.c \
					srcs/pipex.c \
					srcs/pipex_utils.c


PIPEX_O			=	$(PIPEX:.c=.o)



all: $(NAME)

$(NAME): $(PIPEX_O)
	$(CC) $(SAN) $(CFLAGS) $(PIPEX)
	mv a.out $(NAME)

.c.o:
	$(CC) $(SAN) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(PIPEX_O) $(NAME)

fclean: clean
	$(RM) out

re:	fclean all

.PHONY:	all clean fclean re
