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

#pragma once
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>
#include <string.h>
#include <windows.h>
#include <sysinfoapi.h>


#define MAXLINE 12
#define BUFFERSIZE 4024
#define PACMAN_PACKAGE_MANAGER 0
#define APT_PACKAGE_MANAGER 1
#define APK_PACKAGE_MANAGER 2
#define FLATPAK_PACKAGE_MANAGER 3
#define SNAP_PACKAGE_MANAGER 4

#define BYTE_GIGABYTE_CONVERSION 1073741824L
#define BYTE_KILOBYTE_CONVERSION 1024
#define KILOBYTE_GIGABYTE_CONVERSION 1048576 // Number of kilobytes in a gigabyte
#define MILLISECONDS_SECONDS_CONVERSION 1000
typedef unsigned short int iter;
typedef unsigned long int packagecount;
typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);
typedef PSYSTEM_LOGICAL_PROCESSOR_INFORMATION PSLPI;
typedef unsigned long long size_t;

struct date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

void init(void);
unsigned int get_core_count (void);
unsigned int get_thread_count (void);
int get_total_memory (void);
int get_avalible_memory (void);
long get_uptime (void);
size_t get_cpu_model (char *dest);
size_t get_hostname (char *dest);
size_t get_kernel_release (char *dest);
size_t get_operating_system_name (char *dest);
size_t get_board_model (char *dest);
struct date get_creation_date (void);
char *get_username (void);
packagecount get_num_packages (unsigned short package_manager_id);
size_t get_shell_name (char *dest);
short get_disk_usage (char **dest, bool gigs);
