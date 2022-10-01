NAME = ft_containers

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

SRCS = main.cpp
HEADERS =	iterator.hpp \
			map.hpp \
			pair.hpp \
			red_black_tree.hpp \
			red_black_tree_utils.hpp \
			set.hpp \
			stack.hpp \
			type_traits.hpp \
			utils.hpp \
			vector.hpp

OBJS = $(SRCS:%.cpp=%.o)

$(NAME):	$(OBJS) $(HEADERS) Makefile
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY: all clean fclean re