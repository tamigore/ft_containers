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

SOURCES =	RBTree.cpp

MAINS =	main.cpp	\
		map.cpp
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
MAIN = $(addprefix $(DIR_S),$(MAINS))

OBJS = $(SOURCES:.cpp=.o)
OBJS += $(MAINS:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

M_STD = -D STD

m_FT = -D FT

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJS): $(SRCS) $(MAIN)
	$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)
	$(CXX) -c $(MAIN) $(FLAGS) -I $(INC)

std:
			$(eval FLAGS += $(M_STD))
			$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)
			$(CXX) -c $(MAIN) $(FLAGS) -I $(INC)
			$(CXX) $(OBJS) $(FLAGS) -o $(NAME) > test_std

ft:			$(SRCS)
			$(eval FLAGS += $(M_FT))
			$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)
			$(CXX) -c $(MAIN) $(FLAGS) -I $(INC)
			$(CXX) $(OBJS) $(FLAGS) -o $(NAME) > test_ft

bonus: all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all