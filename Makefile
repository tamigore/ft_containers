# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:26:46 by user42            #+#    #+#              #
#    Updated: 2022/08/13 14:27:12 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

NAME = ft_containers

DIR_S = srcs/

SOURCES =	main.cpp	\
			stack.cpp	\
			vector.cpp

HEADER =	ft.hpp		\
			stack.hpp	\
			vector.hpp
# map.hpp

INC = inc/

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SOURCES:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CXX) -c $(SRCS) $(FLAGS) -I $(INC)

bonus: all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all