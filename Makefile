NAME = ft_containers

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

SRCS = main.cpp
HEADERS =	vector.hpp utils/enable_if.hpp utils/equal.hpp utils/is_integral.hpp utils/iterator.hpp utils/iterators_traits.hpp \
			utils/other_utils.hpp utils/pair.hpp utils/reverse_iterator.hpp
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