CC = gcc
CFLAGS=-g -Wall -O2 -lm
source_files = $(wildcard src/*.c) $(wildcard library/*.c)
output_dir = dist
output_file = qinfo

default: build

build:
	mkdir -p $(output_dir)
	$(CC) -o $(output_dir)/$(output_file) $(source_files) $(CFLAGS)

clean:
	rm -rf $(output_dir)

install: build
	mkdir -p $(PREFIX)$(DESTDIR)/usr/bin/
	install -m 0755 $(output_dir)/$(output_file) $(PREFIX)$(DESTDIR)/usr/bin/qinfo

run: clean build
	dist/qinfo