CXX = clang++
LDFLAGS = -g -Wall -Wextra -Werror -std=c++98
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98

NAME = bigint
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))

all: $(NAME)

$(NAME):$(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^
build/%.o: %.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $^ -o $@
clean:
	rm -rf build
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all re fclean clean