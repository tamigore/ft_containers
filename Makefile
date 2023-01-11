# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:26:46 by user42            #+#    #+#              #
#    Updated: 2022/12/06 16:38:54 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

NAME = ft_containers

DIR_S = srcs/

SOURCES =	main.cpp	\
			map.cpp
			# RBTree.cpp	\
			# stack.cpp	\
			# vector.cpp	\

HEADER =	ft.hpp		\
			pair.hpp	\
			RBTree.hpp	\
			map.hpp
			# stack.hpp	\
			# vector.hpp	\
			# usefull.hpp	\

INC = std_inc/

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SOURCES:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)

std:
			$(eval FLAGS += $(M_STD))
			$(CXX) $(FLAGS) -I $(INC) -g -c $(SRCS) -o $(OBJS)
			$(CXX) $(FLAGS) $(OBJS) -o $(NAME) > test_std

ft:			$(OBJS_FILE)
			$(eval FLAGS += $(M_FT))
			$(CXX) $(FLAGS) -I $(INC) -g -c $(SRCS) -o $(OBJS)
			$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

bonus: all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all