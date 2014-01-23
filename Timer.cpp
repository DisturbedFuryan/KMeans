#include "Timer.hpp"


Timer::Timer() : m_startClockTicks( 0 ), m_pausedTicks( 0 ), m_started( false ), m_paused( false ) {}


void Timer::Start() {
    m_started = true;
    m_paused = false;
    
    m_startClockTicks = GetClockTicks();
}


void Timer::Stop() {
    m_started = false;
    m_paused = false;
}


void Timer::Pause() {
    if ( m_started && !m_paused ) {
        m_paused = true;
        
        m_pausedTicks = ( GetClockTicks() - m_startClockTicks );
    }
}


void Timer::Unpause() {
    if ( m_paused ) {
        m_paused = false;
        
        m_startClockTicks = ( GetClockTicks() - m_pausedTicks );
        
        m_pausedTicks = 0;
    }
}


double Timer::GetTime() {
    if ( m_started ) {
        if ( m_paused ) {
            return ( static_cast<double>( m_pausedTicks ) / 1000000000.0 );
        }
        
        return ( static_cast<double>( GetClockTicks() - m_startClockTicks ) / 1000000000.0 );
    }
    
    return 0.0;
}


long Timer::GetClockTicks() {
    clock_gettime(CLOCK_MONOTONIC, &m_ts);
    return ( ( m_ts.tv_sec * 1000000000 ) + m_ts.tv_nsec );
}
