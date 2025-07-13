#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER ""

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 1000

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "dba-date", 0, 1) \
    X("", "dba-time", 60, 2) \
    X("", "dba-battery", 60, 3) \
    /* X("", "dba-updates", 3600, 1)  \*/
    /* X("", "dba-disksize", 60, 2)   \*/

#endif  // CONFIG_H
