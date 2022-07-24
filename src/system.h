// Checking for windows OS with
// _WIN32 macro
#ifdef _WIN32
#define OPERATING_SYSTEM "Windows32"
#include "windows.h"

// Checking for mac OS with
// __APPLE__ macro
#elif __APPLE__
#define OPERATING_SYSTEM "MacOS"

// Checking for linux OS with
// __linux__ macro
#elif __linux__
#define OPERATING_SYSTEM "Linux"

// Checking for iOS embedded OS with
// TARGET_OS_EMBEDDED macro
#elif TARGET_OS_EMBEDDED
#define OPERATING_SYSTEM "iOSEmbedded"

// Checking for iOS simulator OS with
// TARGET_IPHONE_SIMULATOR macro
#elif TARGET_IPHONE_SIMULATOR
#define OPERATING_SYSTEM "iOSSimulator"

// Checking for iPhone OS with
// TARGET_OS_IPHONE macro
#elif TARGET_OS_IPHONE
#define OPERATING_SYSTEM "iOS"

// Checking for MAC OS with
// TARGET_OS_MAC macro
#elif TARGET_OS_MAC
#define OPERATING_SYSTEM "MacOS"

// Checking for Android OS with
// __ANDROID__ macro
#elif__ANDROID__
#define OPERATING_SYSTEM "Android"

// Checking for unix OS with
// __unix__ macro
#elif __unix__
#define OPERATING_SYSTEM "Unix"

// Checking for POSIX based OS with
// _POSIX_VERSION macro
#elif _POSIX_VERSION
#define OPERATING_SYSTEM "POSIX"

// Checking for Solaris OS with
// __sun macro
#elif __sun
#define OPERATING_SYSTEM "Solaris"

// Checking for HP UX OS with
// __hpux macro
#elif __hpux
#define OPERATING_SYSTEM "HP-UX"

// Checking for BSD OS with
// BSD macro
#elif BSD
#define OPERATING_SYSTEM "BSD"

// Checking for DragonFly BSD OS with
// __DragonFly__ macro
#elif __DragonFly__
#define OPERATING_SYSTEM "DragonFlyBSD"

// Checking for FreeBSD OS with
// __FreeBSD__ macro
#elif __FreeBSD__
#define OPERATING_SYSTEM "FreeBSD"

// Checking for Net BSD OS with
// __NetBSD__ macro
#elif __NetBSD__
#define OPERATING_SYSTEM "NetBSD"

// Checking for Open BSD OS with
// __OpenBSD__ macro
#elif __OpenBSD__
#define OPERATING_SYSTEM "OpenBSD"

// If neither of them is present
#else
#define OPERATING_SYSTEM "Unknown"

#endif