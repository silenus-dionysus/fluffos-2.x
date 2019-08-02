#ifndef RECLAIM_H
#define RECLAIM_H

/*
 * reclaim.c
 */

class Reclaim {
public:
int reclaim_objects (void);
};

extern Reclaim globalReclaim;
#endif
