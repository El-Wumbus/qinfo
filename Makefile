CC = gcc
headder_files = $(wildcard src/*.h)
source_file = src/qinfo.c
output_dir = dist
output_file = qinfo

default: build

build: $(source_file) $(headder_files)
	mkdir -p $(output_dir)
	$(CC) -o $(output_dir)/$(output_file) $(source_file)

clean:
	rm -rf $(output_dir)

install: build
	mkdir -p $(PREFIX)$(DESTDIR)/usr/bin/
	install -m 0755 $(output_dir)/$(output_file) $(PREFIX)$(DESTDIR)/usr/bin/qinfo

run: clean build
	dist/qinfo