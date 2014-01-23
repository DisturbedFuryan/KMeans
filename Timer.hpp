#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

//======================================================================================================================
class Timer {
public:
    Timer();
    
    /* Różne akcje. */
    void Start();
    void Stop();
    void Pause();
    void Unpause();

    /* Zwraca czas w sekundach. */
    double GetTime();
    
    bool IsStarted() const { return m_started; }
    bool IsPaused() const { return m_paused; }
    
private:
    long int m_startClockTicks;
    long int m_pausedTicks;
    
    struct timespec m_ts;
    
    /* Flagi. */
    bool m_started;
    bool m_paused;
    
    long GetClockTicks();
};
//======================================================================================================================

#endif
