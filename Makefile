CC = gcc
CFLAGS=-g -Wall -lm -O2
source_files = $(wildcard src/*.c) $(wildcard library/*.c)
BUILD_LOCATION = dist
INSTALL_LOCATION = /usr/bin
BIN = qinfo

default: build

build:
	mkdir -p $(BUILD_LOCATION)
	$(CC) -o $(BUILD_LOCATION)/$(BIN) $(source_files) $(CFLAGS)

clean:
	rm -rf $(output_dir)

install: build
	mkdir -p $(PREFIX)$(DESTDIR)$(INSTALL_LOCATION)
	install -m 0755 $(output_dir)/$(BIN) $(PREFIX)$(DESTDIR)$(INSTALL_LOCATION)/$(BIN)

run: clean build
	$(BUILD_LOCATION)/$(BIN)