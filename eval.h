#ifndef FLUFF_EVAL_H
#define FLUFF_EVAL_H

#include <atomic>

extern std::atomic<bool> outoftime;
extern LPC_INT max_cost;

void set_eval(LPC_INT time);
LPC_INT get_eval();
#endif
