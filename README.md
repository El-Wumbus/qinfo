# qinfo

A Linux system info program. Fetches system info and displays it.  

## Feature Set

* Show CPU model name, cores and threads
* Show Total RAM and RAM usage
* Show Distro Name
* Show kernel name
* Filesystem Birthdate
* Show Hostname
* Show formatted uptime

## How to install

To get the source code of this software you'll need the `git` version control software.
You probably already have it installed, you can check `git --version`.
If you get an error message then you must install `git` from your distro's repositories.

For the installation of this software a C compiler is required. Your distro already has one installed, it's probably `gcc`.
If not, then you need to install `gcc` (or have another compiler symlinked to it) You can check with `gcc --version`. If you get an error message then you must install
`gcc` from your distro's repositories.

You'll also need `make`, you likely already have this installed. You can check with `make --version`.
If you get an error message then you must install `make` from your distro's repositories.

This program is built with `glibc` in mind. If you use a different C library it may not function as expected.
This does not mean it doesn't work with other C libraries, this means i haven't confirmed functionality with
all the C libraries out there. Ensure you're using `glibc` before complaining about broken software.

Now that we have all the dependencies present we can compile the project. The following instructions assume the bash shell, though these instructions will work with the *vast* majority of linux shells (everything you're likely to use).

```bash
git clone https://github.com/El-Wumbus/qinfo.git
cd qinfo
sudo make install
```

If using Arch Linux you can Compile with pkgbuild to manage the package with pacman.

```bash
git clone https://github.com/El-Wumbus/qinfo.git
cd qinfo/archpkg
makepkg -si
```

## Usage

```bash
$ qinfo
CPU:            AMD Ryzen 5 5600X 6-Core Processor (6 cores, 12 threads)
EXTRA CPU INFO: Model number 0xA21, Family Value: 0x19
RAM:            6.80/31.27 GB 
OS:             Arch Linux (Linux)
Hostname:       Aidan-PC
ROOTFS BIRTH:   5/14/2022
Uptime:         19 hours 48 minutes 46 seconds
```

Anything printed here is configurable at compile-time. You may do so in `src/config.h`. The default configuration looks like this:

```C
/* Display cpu name and core/thread info */
bool DISPLAY_CPU_INFO         = true;

/* Display extra cpu info */
bool DISPLAY_ETC_CPU_INFO     = true;

/* Display memory capacity and usage ratio */
bool DISPLAY_MEMORY_INFO      = true;

/* Display the computer's hostname */
bool DISPLAY_HOSTNAME         = true;

/* Display the system uptime */
bool DISPLAY_UPTIME           = true;

/* Display the operating system name */
bool DISPLAY_OPERATING_SYSTEM = true;

/* measure memory in gigabytes instead of kilobytes */
bool USE_GIGABYTES            = true;

/* Only supported properly on unix-like operating systems */
bool DISPLAY_KERNEL_VERSION   = true;

/* Display the rootfs birthday */
bool DISPLAY_ROOTFS_BIRTHDAY  = true;

/* Otherwise print in MM/DD/YYYY format. */
bool DISPLAY_DATES_YYYY_MM_DD = false;
```

## Contributing

* Check the issues (if there are any), it's a good place to start when you don't know what to do.
* Fork the repository and create pull requests to this repository.
* Don’t change the formatting - Dont reformat or otherwise change the formatting of source code or documentation in the repo. Use the same formatting as the rest of the codebase.
* Make documentation - If adding features or otherwise changing the user experience create documentation regarding the added or changed features.
* Use space only indentation in all source code files with the sole execption of Makefile - Do not use tabs or any form of indentation other than spaces. Use 2 space indentation.

## LICENSE

[![GNU LGPLv3 Image](https://www.gnu.org/graphics/lgplv3-147x51.png)](https://www.gnu.org/licenses/lgpl-3.0.html)  

qinfo is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation;
either version 3 of the License, or (at your option) any later version.
