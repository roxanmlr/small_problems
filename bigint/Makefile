NAME		= bigint
SOURCES		= $(wildcard *.cpp)
OBJECTS		= $(patsubst %.cpp,build/%.o,$(SOURCES))

CXX			= clang++
SAN			= -fsanitize=address,undefined
CXXFLAGS	= -g -Wall -Wextra -Werror -std=c++98 $(SAN)

all: $(NAME)
$(NAME):$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
build/%.o: %.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o $@ $^
clean:
	rm -rf build
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
