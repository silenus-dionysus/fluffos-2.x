#ifndef DUMPSTAT_H
#define DUMPSTAT_H

#include "lpc_incl.h"

/*
 * dumpstat.c
 */

class DumpStat {
public:
int data_size (object_t *);
void dumpstat (const char *);
};

extern DumpStat globalDumpStat;
#endif
