#ifndef POSIX_TIMERS_H
#define POSIX_TIMERS_H


#ifdef POSIX_TIMERS
void init_posix_timers(void);
void posix_eval_timer_set(int micros);
int posix_eval_timer_get(void);
void sigalrm_handler (int, siginfo_t *, void *);
#else
#ifdef SIGNAL_FUNC_TAKES_INT
void sigalrm_handler (int);
#else
void sigalrm_handler (void);
#endif

#endif

#endif
