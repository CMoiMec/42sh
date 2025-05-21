##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Handles rules used by make to build this project
##

# Definition of ressources used to build 1st binary
BIN1_NAME		=	42sh
BIN1_DIR		=	src/
BIN1_SUB1		=	$(BIN1_DIR)*/
BIN1_SUB2		=	$(BIN1_SUB1)*/
BIN1_SRC		=	$(wildcard $(BIN1_DIR)*.c $(BIN1_SUB1)*.c $(BIN1_SUB2)*.c)
BIN1_OBJ		=	$(BIN1_SRC:.c=.o)

# Definition of ressources used to build 'my' library
LIB_NAME		=	libmy.a
LIB_DIR			=	lib/my/
LIB_SRC			=	$(wildcard $(LIB_DIR)*.c)
LIB_OBJ			=	$(LIB_SRC:.c=.o)

# Definition of ressources used to build unit tests
CRIT_DIR		=	tests/criterion/
CRIT_SUB1		=	$(CRIT_DIR)*/
CRIT_SUB2		=	$(CRIT_SUB1)*/
CRIT_BIN1		=	$(filter-out src/shell/main.c, $(BIN1_SRC))
CRIT_SRC		=	$(wildcard $(CRIT_DIR)*.c $(CRIT_SUB1)*.c $(CRIT_SUB2)*.c)
CRIT_PACK		=	$(CRIT_SRC) $(CRIT_BIN1)
CRIT_LDFLAGS	=	--coverage -lcriterion -L/opt/homebrew/lib

# Definition of compiler and linker flags
CFLAGS 			+=	-Wall -Wextra -Wpedantic -Wundef -Wfloat-equal -Wshadow \
					-Wpointer-arith -Wcast-align -Waggregate-return			\
					-Wwrite-strings -Wstrict-prototypes -Winit-self 		\
					-Wno-attributes -Wlogical-not-parentheses -Waddress 	\
					-O2 -Iinclude -D_GNU_SOURCE
LDFLAGS 		+=	-Llib -lmy -lncurses
MAKEFLAGS 		+=

all: lib/$(LIB_NAME) $(BIN1_NAME)

$(BIN1_NAME): $(BIN1_OBJ)
	$(CC) -o $(BIN1_NAME) $(BIN1_OBJ) $(LDFLAGS)
	@printf "\e[33m-> Building binary: %s:\t\t\e[1;42mdone\e[0m\n" $(BIN1_NAME)

lib/$(LIB_NAME): $(LIB_OBJ)
	$(AR) rc libmy.a $(LIB_OBJ)
	mv $(LIB_NAME) lib/
	mkdir -p include
	cp $(LIB_DIR)*.h include 2>&- | true
	cp $(BIN1_DIR)*.h $(BIN1_SUB1)*.h $(BIN1_SUB2)*.h include 2>&- | true
	@printf "\e[33m-> Building library: %s:\t\t\e[1;42mdone\e[0m\n" $(LIB_NAME)

clean:
	find . -name "*~" -delete -o -name "#*#" -delete
	find . -name "coding-style-reports.logs" -delete
	find . -name "*.gcda" -delete -o -name "*.gcno" -delete
	@printf "\e[33m-> Deleting garbage files:\t\t\e[1;42mdone\e[0m\n"

tests_run: fclean lib/$(LIB_NAME)
	$(CC) $(CFLAGS) -o unit_tests $(CRIT_PACK) $(CRIT_LDFLAGS) $(LDFLAGS)
	@printf "\e[33m-> Building unit tests:\t\t\t\e[1;42mdone\e[0m\n"
	- timeout 3m ./unit_tests
	gcovr --exclude tests

fclean: clean
	$(RM) -r include *.dSYM
	$(RM) $(BIN1_NAME) $(BIN1_OBJ) $(BIN1_MAIN)
	$(RM) $(LIB_OBJ) lib/$(LIB_NAME) unit_tests
	@printf "\e[33m-> Deleting project-built files:\t\e[1;42mdone\e[0m\n"

bashtest:
	@cp tests/test.sh .
	@cp -r tests/bashtest .
	@./tests/test.sh
	@rm -r test.sh
	@rm -r bashtest

cs: fclean
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log

re: fclean all

.PHONY: all clean fclean re bashtest
