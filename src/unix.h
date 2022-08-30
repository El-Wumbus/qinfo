/*
Author: Aidan Neal <decator.c@proton.me>
  qinfo is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef UNIX_H
#define UNIX_H

#include <ctype.h>
#include <errno.h>
#include "statx.h" // Statx syscall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/utsname.h> // Uname Syscall
#include <sys/statvfs.h>

#define MAXLINE 12
#define BUFFERSIZE 4024

#define PACMAN_PACKAGE_MANAGER 0
#define APT_PACKAGE_MANAGER 1
#define APK_PACKAGE_MANAGER 2
#define FLATPAK_PACKAGE_MANAGER 3
#define SNAP_PACKAGE_MANAGER 4

typedef unsigned short int iterator;
typedef unsigned long int packagecount;
typedef pid_t pid;

struct date
{
  unsigned int day;
  unsigned int month;
  unsigned int year;
};

/**
 * @brief Get the number of cores
 *
 * @return unsigned int
 */
unsigned int get_core_count();

/**
 * @brief Get the thread count
 *
 * @return unsigned int
 */
unsigned int get_thread_count();

/**
 * @brief Get the total memory
 *
 * @return unsigned int
 */
int get_total_memory();

/**
 * @brief Get the avalible memory
 *
 * @return int
 */
int get_avalible_memory();

long get_uptime();

/**
 * @brief Get the cpu model object
 *
 * @param storage_variable
 * @return int
 */
char *get_cpu_model();

/**
 * @brief Get the operating system name
 *
 * @return char*
 */
char *get_operating_system_name();

/**
 * @brief Get the system hostname
 *
 * @param storage_variable
 * @return int
 */
char *get_hostname();

/**
 * @brief return the output of the uname --kernel-name --kernel-release command
 *
 * @param storage_variable
 * @return int
 */
char *kuname();
char *get_board_model();

/**
 * It gets the creation date of the file system and stores it in a struct date
 *
 * @param storage_variable A pointer to a struct date variable that will be used to
 *
 * @return The date of the file system's creation.
 */
struct date get_creation_date();

char *get_username();
char *get_operating_system_name_bedrock();
packagecount get_num_packages(unsigned short package_manager_id);
char *get_shell_name();
struct statvfs df(const char* path);
#endif // UNIX_H
