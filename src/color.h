#ifdef __linux__
// Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

// Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

// High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

// High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

// Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

// Reset
#define COLOR_END "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"
#define NONE '\0'

#else

 //Regular text
    #define BLK "\x1b[30m"
    #define RED "\x1b[31m"
    #define GRN "\x1b[32m"
    #define YEL "\x1b[33m"
    #define BLU "\x1b[34m"
    #define MAG "\x1b[35m"
    #define CYN "\x1b[36m"
    #define WHT "\x1b[37m"

    //Regular bold text
    #define BBLK "\x1b[30m"
    #define BRED "\x1b[31m"
    #define BGRN "\x1b[32m"
    #define BYEL "\x1b[33m"
    #define BBLU "\x1b[34m"
    #define BMAG "\x1b[35m"
    #define BCYN "\x1b[36m"
    #define BWHT "\x1b[37m"

    //Regular underline text
    #define UBLK "\x1b[4;30m"
    #define URED "\x1b[4;31m"
    #define UGRN "\x1b[4;32m"
    #define UYEL "\x1b[4;33m"
    #define UBLU "\x1b[4;34m"
    #define UMAG "\x1b[4;35m"
    #define UCYN "\x1b[4;36m"
    #define UWHT "\x1b[4;37m;"

    //Regular background
    #define BLKB "\x1b[40m"
    #define REDB "\x1b[41m"
    #define GRNB "\x1b[42m"
    #define YELB "\x1b[43m"
    #define BLUB "\x1b[44m"
    #define MAGB "\x1b[45m"
    #define CYNB "\x1b[46m"
    #define WHTB "\x1b[47m"

    //High intensty background
    #define BLKHB "\x1b[100m"
    #define REDHB "\x1b[101m"
    #define GRNHB "\x1b[102m"
    #define YELHB "\x1b[103m"
    #define BLUHB "\x1b[104m"
    #define MAGHB "\x1b[105m"
    #define CYNHB "\x1b[106m"
    #define WHTHB "\x1b[107m"

    //High intensty text
    #define HBLK "\x1b[90m"
    #define HRED "\x1b[91m"
    #define HGRN "\x1b[92m"
    #define HYEL "\x1b[93m"
    #define HBLU "\x1b[94m"
    #define HMAG "\x1b[95m"
    #define HCYN "\x1b[96m"
    #define HWHT "\x1b[97m"

    //Bold high intensity text
    #define BHBLK "\x1b[90m"
    #define BHRED "\x1b[91m"
    #define BHGRN "\x1b[92m"
    #define BHYEL "\x1b[93m"
    #define BHBLU "\x1b[94m"
    #define BHMAG "\x1b[95m"
    #define BHCYN "\x1b[96m"
    #define BHWHT "\x1b[97m"

    //Reset
    #define COLOR_END "\x1b[0m"
    #define CRESET "\x1b[0m"
    #define COLOR_RESET "\e[0m"
    #define NONE '\0';

#endif

struct color
{
    char *ansi_id_color;
    char *ansi_text_color;
    char *logo_color;
};