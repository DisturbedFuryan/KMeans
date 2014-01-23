#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

//======================================================================================================================
class Timer {
public:
    Timer();
    
    /* Various actions. */
    void Start();
    void Stop();
    void Pause();
    void Unpause();

    /* Returns time in seconds. */
    double GetTime();
    
    bool IsStarted() const { return m_started; }
    bool IsPaused() const { return m_paused; }
    
private:
    long int m_startClockTicks;
    long int m_pausedTicks;
    
    struct timespec m_ts;
    
    /* Flags. */
    bool m_started;
    bool m_paused;
    
    long GetClockTicks();
};
//======================================================================================================================

#endif
