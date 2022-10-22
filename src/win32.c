#ifdef _WIN32
#include "win32.h"

static processorCoreCount;
static logicalProcessorCount;

unsigned int get_core_count(void)
{
    return processorCoreCount;
}

unsigned int get_thread_count(void)
{
    return logicalProcessorCount;
}

static MEMORYSTATUSEX mem_stats;

int get_total_memory(void)
{
    return mem_stats.ullTotalPhys / BYTE_KILOBYTE_CONVERSION;
}

int get_avalible_memory(void)
{
    return mem_stats.ullAvailPhys / BYTE_KILOBYTE_CONVERSION;
}

long get_uptime(void)
{
    return GetTickCount64() / MILLISECONDS_SECONDS_CONVERSION;
}

void init(void)
{
    PSLPI LPI;
    LPFN_GLPI glpi;
    DWORD lpi_return_len = 0;
    BOOL done = FALSE;
    glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
        fprintf(stderr, "\nGetLogicalProcessorInformation is not supported.\n");
        exit(1);
    }
    PSLPI buffer = NULL;

    while (!done)
    {
        DWORD rc = glpi(buffer, &lpi_return_len);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                    lpi_return_len);

                if (NULL == buffer)
                {
                    fprintf(stderr, "\nError: Allocation failure\n");
                    exit(1);
                }
            }
            else
            {
                fprintf(stderr, "\nError %d\n", GetLastError());
                exit(1);
            }
        }
        else
        {
            done = TRUE;
        }
    }

    LPI = buffer;
    free(buffer);

    DWORD logicalProcessorCount = 0;
    DWORD processorCoreCount = 0;
    DWORD byteOffset = 0;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= lpi_return_len)
    {
        switch (LPI->Relationship)
        {
        case RelationProcessorCore:
            processorCoreCount++;

            // A hyperthreaded core supplies more than one logical processor.
            logicalProcessorCount += CountSetBits(LPI->ProcessorMask);
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        LPI++;
    }

    mem_stats.dwLength = sizeof(mem_stats);

    GlobalMemoryStatusEx(&mem_stats);
}

static DWORD CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}

size_t get_operating_system_name(char *dest)
{
    int MajorVersion = 0, MinorVersion = 0;

    NTSTATUS(WINAPI * RtlGetVersion)
    (LPOSVERSIONINFOEXW);
    OSVERSIONINFOEXW osInfo;

    // Get the address of the RtlGetVersion function
    *(FARPROC *)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

    if (NULL != RtlGetVersion)
    {
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        RtlGetVersion(&osInfo);
        MajorVersion = osInfo.dwMajorVersion;
    }

    char buffer[BUFFERSIZE];
    if (MinorVersion > 0)
    {
        sprintf(buffer, "Windows %d.%d", MajorVersion, MinorVersion);
    }
    else
    {
        sprintf(buffer, "Windows %d", MajorVersion);
    }

    strcpy(dest, buffer);
    size_t len = (strlen(buffer) + 1) * sizeof(char);
    return len;
}

size_t get_cpu_model(char *dest)
{
    strcpy(dest, "UNAVAILABLE");
    return 12 * sizeof(char);
}
size_t get_hostname(char *dest)
{
    strcpy(dest, "UNAVAILABLE");
    return 12 * sizeof(char);
}
size_t get_kernel_release(char *dest)
{
    strcpy(dest, "UNAVAILABLE");
    return 12 * sizeof(char);
}
size_t get_board_model(char *dest)
{
    strcpy(dest, "UNAVAILABLE");
    return 12 * sizeof(char);
}
struct date get_creation_date(void)
{
}
char *get_username(void)
{
    return "UNAVAILABLE";
}
packagecount get_num_packages(unsigned short package_manager_id)
{
    return 0;
}
size_t get_shell_name(char *dest)
{
    strcpy(dest, "UNAVAILABLE");
    return 12 * sizeof(char);
}
short get_disk_usage(char **dest, bool gigs)
{
    return -2;
}
#endif