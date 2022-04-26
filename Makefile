CC       := gcc
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/run
SRCEXT   := c
SOURCES  := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS   := -g -fsanitize=address
LIB      := -L lib
INC      := -I include

JUNK := tish.config $(wildcard *vgcore.*) $(wildcard *.gdb*)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB) -O3 -fsanitize=address

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $< -save-temps -O3
	
clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(JUNK)"; $(RM) -r $(BUILDDIR) $(TARGET) $(JUNK)
	@clear

valgrind: $(TARGET)
	@valgrind --leak-check=full $(TARGET)

run: $(TARGET)
	@$(TARGET)

.PHONY: clean
