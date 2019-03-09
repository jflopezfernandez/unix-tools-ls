
vpath %.c src
vpath %.h include

CC := gcc

CFLAGS := -O3 -mtune=intel -march=skylake -mavx2
CPPFLAGS := -I include

PROGRAM := ls

DOXYGEN := doxygen

DOXYGEN_CONFIG := doxygen.config

all: documentation $(PROGRAM)

$(PROGRAM): str.o ls.o

ls.o: ls.c
str.o: str.c

documentation: $(DOXYGEN_CONFIG)
	$(DOXYGEN) $(DOXYGEN_CONFIG)

$(DOXYGEN_CONFIG):
	$(DOXYGEN) -g - | \
	sed -n -e 's/^\(OUTPUT_DIRECTORY\s*=\s*\)/\1 doc/;/.*/p' > $(DOXYGEN_CONFIG)

.PHONY: clean
clean:
	rm -rf $(PROGRAM)
	rm -rf *.o
	rm -rf $(DOXYGEN_CONFIG)
	rm -rf doxygen2.config
