NAME 		=	exec
FLAGS 		=	-Wall -Wextra -Werror -std=c++98

SRCS_DIR 	=	./
SRCS 		=	main.cpp \
				Converter.cpp

OBJS_DIR 	=	objects/
OBJ 		=	$(SRCS:.cpp=.o)
OBJS 		=	$(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@c++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@c++ $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean