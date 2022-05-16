CC       := gcc
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/run
SRCEXT   := c
SOURCES  := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS   := -Wall -Wextra -std=gnu11 -g -fsanitize=address
LIB      := -L lib -lreadline
INC      := -I include

LOGS     := vgcore.* ./tests/vgcore.* # Removed with clean command

PRINT_LINK     = \e[1;32m==>\e[0m \e[1;33mLinking...\e[0m\n
PRINT_BUILD    = \e[1;32m==>\e[0m \e[1;34mBuilding...\e[0m\n
PRINT_CLEAN    = \e[1;32m==>\e[0m \e[1;34mCleaning...\e[0m\n

PRINT_RUN      = \e[1;32m==>\e[0m \e[1;32mStarting program...\e[0m\n
PRINT_VALGRIND = \e[1;32m==>\e[0m \e[1;33mRunning with Valgrind...\e[0m\n
PRINT_CHECKER  = \e[1;32m==>\e[0m \e[1;33mTesting using checker...\e[0m\n


ARROW = \e[1;34m  ->\e[0m

build: $(TARGET)

$(TARGET): $(OBJECTS)
	@printf "$(PRINT_LINK)"
	@printf "$(ARROW) $(CC) $^ -o \e[0;32m$(TARGET)\e[0m $(LIB)\n"; \
	                  $(CC) $^ -o         $(TARGET)      $(LIB) -O3 -fsanitize=address
	@printf "\e[1;32m==>\e[0m \e[1;36mDone!\e[0m\n\n"

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@printf  "$(PRINT_BUILD)"
	@mkdir -p $(BUILDDIR)
	@printf  "$(ARROW) $(CC) $(CFLAGS) -c -o $@ \e[0;34m$<\e[0m\n"; \
	                   $(CC) $(CFLAGS) $(INC) -c -o $@  $< -save-temps -O3

clean:
	@printf "$(PRINT_CLEAN)"
	@printf "$(ARROW) $(RM) -r $(BUILDDIR) \e[0;32m$(TARGET)\e[0m $(LOGS)\n"; \
	                  $(RM) -r $(BUILDDIR)         $(TARGET)      $(LOGS)

check: $(TARGET)
	@printf "$(PRINT_CHECKER)"
	(cd ./tests && ./check.sh)

valgrind: $(TARGET)
	@printf "$(PRINT_VALGRIND)"
	@valgrind --leak-check=full \
			  --show-leak-kinds=all \
			  --track-origins=yes \
			  -s \
			  $(TARGET)

run: $(TARGET)
	@printf "$(PRINT_RUN)"
	@$(TARGET)

.PHONY: clean
