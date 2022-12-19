TARGET	= program

CC		= cc

SRCS	= program.c

OBJS	= $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re:
	make fclean
	make all

.PHONY: all bonus clean fclean re