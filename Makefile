#Copyright Tudor Robert-Fabian 312CAa 2023-2024
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c -lm -Wall -Wextra -o image_editor

pack:
	zip -FSr 312CA_TudorRobert-Fabian_Tema3.zip README Makefile *.c *.h *.md

clean:
	rm -f $(TARGETS)

.PHONY: pack clean