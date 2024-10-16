#include "config.h"

#include "block.h"
#include "util.h"

Block blocks[] = {
    //{ "dba-updates", 3600, 0 },
    { "dba-disksize", 60, 0 },
    { "dba-date", 30,  0 },
    { "dba-battery", 60, 0 }
};

const unsigned short blockCount = LEN(blocks);
