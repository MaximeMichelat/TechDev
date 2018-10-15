#
# Makefile pour le game of life
#
# Ce Makefile dépend de GNU make.

NAME = game-of-life
VERSION = 0.0.4

CC=clang -g
CFLAGS=-Wall -O2 -Wextra -std=c99 -pedantic
LDFLAGS=
LIB_FILES=obj/grille.o obj/jeu.o
LIB=lib/libjeu.a
OBJS=$(SOURCES:src/%c=obj/%o)
PROG=bin/exec

MODE=GRAPHIQUE

ifeq ($(MODE), GRAPHIQUE)
	CFLAGS += `pkg-config --cflags cairo` -I/usr/include/X11
	LDFLAGS += -lcairo -lX11

	SOURCE_DIR = src/
	HEADERS_DIR = include/
else
	SOURCE_DIR = src_console/
	HEADERS_DIR = include_console/
endif

SOURCES=$(wildcard ${SOURCE_DIR}*.c)
HEADERS=$(wildcard ${SOURCE_DIR}*.h)

all: $(PROG)

Q := @

GREEN = \033[01;32m
BLUE = \033[01;34m
MAGENTA = \033[01;35m
RED = \033[01;31m
YELLOW = \O33[33m
WHITE = \033[37m
RESET = \033[00m

$(PROG) : $(OBJS)
	@echo -e '${GREEN} [CCLD]  ${WHITE}$(PROG)${RESET}'
	$Q$(CC) -o $(PROG) $(CFLAGS) $(LDFLAGS) $(OBJS)

obj/%.o: src/%.c
	@echo -e '${BLUE} [CC]    ${WHITE}$@${RESET}'
	$Q$(CC) -o $@ -c $< $(CFLAGS)

$(LIB): ${LIB_FILES}
	@echo -e '${YELLOW} [LIB]    ${WHITE}$@${RESET}'
	@ar -rcs $@ $^

doc:
	@echo -e '${MAGENTA} [DOXY]  ${WHITE}$@${RESET}'
	$Qdoxygen

clean:
	@echo -e '${RED} [RM]    ${WHITE}*.o $(PROG)${RESET}'
	$Q/bin/rm -f obj/*.o $(PROG)
	@echo -e '${RED} [RM]    ${WHITE}${NAME}-${VERSION}${RESET}'
	$Q/bin/rm -f "${NAME}-${VERSION}"

archive: dist

dist:
	rm -f ${NAME}-${VERSION}
	ln -sf . ${NAME}-${VERSION}
	find "${NAME}-${VERSION}"/* | { \
		grep '/\([mM]akefile\|Doxyfile\|explication.txt\|bin\|lib\|obj\|src\|.*\.[choa]\)$$'; \
	} | xargs tar cvzf projetTechDev.tar.gz
	find "${NAME}-${VERSION}"/* | { \
		grep '/\([mM]akefile\|Doxyfile\|explication.txt\|bin\|lib\|obj\|src\|.*\.[choa]\)$$'; \
	} | xargs tar cvJf projetTechDev.tar.xz
