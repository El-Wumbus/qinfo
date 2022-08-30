# qinfo

A Linux🐧 system info program. Fetches system info and displays it.  

## Feature Set

* Show CPU model name, model number, cores, threads, and family.
* Show Total RAM and RAM usage
* Show Distro Name
* Show kernel name
* Show Username
* Show Motherboard model and vendor
* Filesystem Birthdate
* Show Hostname
* Show formatted uptime
* Runtime ini configuration parsing (using [inih](https://github.com/benhoyt/inih))
* Show number of installed packages
* Print kernel name and release
* Print disk usage
  
## How to install

## Arch User Repository

On Arch linux and Arch Linux based systems (systems with `pacman` and `makepkg`) there's an AUR package available to you. You can install it in one of two ways:

* With an AUR helper:

  ```bash
  # for example, yay
  yay -S qinfo-git
  ```

* Manually 😎:

  ```bash
   git clone https://aur.archlinux.org/qinfo-git.git
   cd qinfo-git
   makepkg -si
  ```

### Compile *Manually* 😎

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

#### Compiling on Alpine

Despite having previously noted that this program isn't validated to work when compiling
using any stdlib other than `glibc`, i've provided some instructions to *hopefully* get
the program to compile on a non-glibc using distro, Alpine.  

qinfo uses `argp` for argument parsing. `argp` is a GNU extention to libc,
and thus isn't usually present when not using glibc. To add the neccesarry headers,
needed for compilation, run the following:

```bash
apk add argp-standalone
```

This is required because Alpine Linux uses the `musl` C library.

You'll also need to install `gcc`, or symlink `clang` to it. You'll need `make` as well.

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

```txt
$ ./dist/qinfo -?
Usage: qinfo [OPTION...] 
qinfo -- A system info program. Gets system info and displays it.

  -c, --config=CONFIG_FILE    Use this config file instead of the defualt
                             location.
  -s, --hide_warnings        Hide any non-critical warnings.
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to <decator.c@proton.me>.
```

Anything printed here is configurable at `$HOME/.config/.qinfo.conf`. An example configuration looks like this:

```ini
[Display]
DISPLAY_CPU_INFO = true ; Display cpu name and core/thread info
DISPLAY_EXTRA_CPU_INFO = false ; Display extra cpu info
DISPLAY_MEMORY_INFO = true ; Display memory capacity and usage ratio
DISPLAY_HOSTNAME = true ; Display the computer's hostname
DISPLAY_UPTIME = true ; Display the system uptime
DISPLAY_OPERATING_SYSTEM = true ; Display the operating system name
DISPLAY_KERNEL_VERSION = true ; Only supported properly on unix-like operating systems
DISPLAY_ROOTFS_BIRTHDAY = true ; Display the rootfs birthday
DISPLAY_MOTHERBOARD_INFO = true ; Display motherboard info
DISPLAY_LOGO = true ; Disable or Enable the logo display
DISPLAY_USERNAME = true ; Display the username of the calling user
DISPLAY_PACKAGES = false ; Display the number packages installed using various package managers.

[Color]
; Availible Color Options:
; - black
; - red
; - green
; - yellow
; - blue
; - magenta
; - cyan
; - white
; - bold red
; - bold green
; - bold yellow
; - bold blue
; - bold magenta
; - bold cyan
; - bold white
; - none

IDCOLOR = bold cyan ; Color for the id column
TXTCOLOR = none ; Color for the text column
LOGOCOLOR = red ; Color for the logo

[Extra]
USE_GIGABYTES = true ; Measure memory in gigabytes instead of kilobytes
DISPLAY_DATES = MDY ; supported formats are YMD (YYYY/MM/DD) and MDY(MM/DD/YYYY).
```

If no configuration is found then this notice will appear above the defualt output: `$HOME/.config/.qinfo.conf' not found, not loading configuration`.

## Contributing

* Check the issues (if there are any), it's a good place to start when you don't know what to do.
* Fork the repository and create pull requests to this repository.
* Don’t change the formatting - Dont reformat or otherwise change the formatting of source code or documentation in the repo. Use the same formatting as the rest of the codebase.
* Make documentation - If adding features or otherwise changing the user experience create documentation regarding the added or changed features.
* Use space only indentation in all source code files with the sole execption of Makefile - Do not use tabs or any form of indentation other than spaces. Use 2 space indentation.
