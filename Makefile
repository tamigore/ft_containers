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

SNAME = std_containers

NAME = ft_containers

DIR_S = srcs/

SOURCES =	main.cpp	\
			stack.cpp	\
			vector.cpp	\
			set.cpp		\
			map.cpp

HEADER =	ft.hpp		\
			pair.hpp	\
			RBTree.hpp	\
			stack.hpp	\
			vector.hpp	\
			usefull.hpp	\
			map.hpp

INC = inc/

HEADERS = $(addprefix $(INC),$(HEADER))
SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SOURCES:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98 -g3 #-fsanitize=address
S_FLAG = NULL

M_STD = -D STD
M_FT = -D FT

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)

std:
		$(eval S_FLAG = $(M_STD))
		$(CXX) -c $(SRCS) $(FLAGS) $(S_FLAG) -I $(INC)
		$(CXX) $(OBJS) $(FLAGS) $(S_FLAG) -o $(SNAME)

ft:
		$(eval S_FLAG = $(M_FT))
		$(CXX) -c $(SRCS) $(FLAGS) $(S_FLAG) -I $(INC)
		$(CXX) $(OBJS) $(FLAGS) $(S_FLAG) -o $(NAME)

bonus: all

clean:
	@rm -rf $(OBJS)
	@rm -f test_ft.txt
	@rm -f test_std.txt

fclean: clean
	@rm -f $(NAME)
	@rm -f $(SNAME)

re: fclean all