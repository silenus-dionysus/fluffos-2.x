#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "std.h"
#include "main.h"
#include "comm.h"
#include <time.h>
#include "backend.h"


//need to figure out how to set the next time timePoint based on the current timepoint and the current time.
std::atomic<bool> outoftime;
int lasttime;
LPC_INT max_cost;

struct EvalTimer {
    EvalTimer()
        : th_([this]() { this->runThread(); })
    {
        outoftime = false;
    }

    ~EvalTimer() {
        {
            std::lock_guard<std::mutex> l(m_);
            stop_ = true;
            outoftime = true;
        }
        c_.notify_one();
        th_.join();
    }

    void runThread() {
        while(this->wait_for(std::chrono::nanoseconds(max_cost*1000000)))
        {
            outoftime = true;
        }
            
    }

    // Returns false if stop_ == true.
    template<class Duration>
    bool wait_for(Duration duration) {
        std::unique_lock<std::mutex> l(m_);
        return !c_.wait_for(l, duration, [this]() { return stop_; });
    }

    std::condition_variable c_;
    std::mutex m_;
    bool stop_ = false;
    std::thread th_;
};

EvalTimer timer;

void set_eval(LPC_INT){
	outoftime = false;
}

LPC_INT get_eval(){
	return outoftime;
}

