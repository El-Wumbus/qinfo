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
struct packages;

/* #include "color.h" */
#include "config.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>

#define SECOND_DAY_CONVERSION 86400 // Number of seconds in a day
#define SECOND_HOUR_CONVERSION 3600 // Number of seconds in an hour
#define SECOND_MINUTE_CONVERSION 60 // Number of seconds in a minute
#define HOUR_DAY_CONVERSION 24      // Number of hours in a day
#define MINUTE_HOUR_CONVERSION 60   // Number of minutes in an hour

struct uptime
{
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
};

struct packages
{
    packagecount pacman_packages;
    packagecount apt_packages;
    packagecount apk_packages;
    packagecount flatpak_packages;
    packagecount snap_packages;
};

/* Used by main to communicate with parse_opt. */

struct arguments
{
    bool silent;
    char *config_file;
};

static struct uptime formatted_uptime (long uptime);
static struct packages formatted_packages ();

static void printos ();
static void printlogo ();
static void printcpuinfo (bool extra);
static void printmem (bool gigs);
static void printuser ();
static void printshell ();
static void printhostname ();
static void printboard ();
static void printrootfsbirth (bool format);
static void printuptime ();
static void printkernel ();
static void printpackages ();
static void printdiskinfo (bool gigs);
