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
#ifndef QINFO_H
#define QINFO_Hstruct packages;


/* #include "color.h" */
#include "config.h"
#include "system.h"
#include "unix.h"
#include <stdio.h>
#include <stdlib.h>

#define SECOND_DAY_CONVERSION 86400 // Number of seconds in a day
#define SECOND_HOUR_CONVERSION 3600 // Number of seconds in an hour
#define SECOND_MINUTE_CONVERSION 60 // Number of seconds in a minute
#define HOUR_DAY_CONVERSION 24 // Number of hours in a day
#define MINUTE_HOUR_CONVERSION 60 // Number of minutes in an hour

#define KILOBYTE_GIGABYTE_CONVERSION 1048576 // Number of kilobytes in a gigabyte

struct uptime {
  unsigned int days;
  unsigned int hours;
  unsigned int minutes;
  unsigned int seconds;
};

struct packages {
  packagecount pacman_packages;
  packagecount apt_packages;
  packagecount apk_packages;
  packagecount flatpak_packages;
  packagecount snap_packages;
};

struct uptime formatted_uptime(long uptime);
struct packages formatted_packages();
#endif