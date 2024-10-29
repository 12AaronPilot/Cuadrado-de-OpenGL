#pragma once
#include <windows.h>
#include <cmath>

const unsigned long MAX_SAMPLE_COUNT = 50;

class CTimer
{
private:
	float           m_TimeScale;                // Amount to scale counter
	float           m_TimeElapsed;              // Time elapsed since previous frame
    __int64         m_CurrentTime;            // Current Performance Counter
    __int64         m_LastTime;               // Performance Counter last frame
	__int64         m_PerfFreq;                 // Performance Frequency

    float           m_FrameTime[MAX_SAMPLE_COUNT];
    unsigned long   m_SampleCount;

    unsigned long   m_FrameRate;              // Stores current framerate

public:
	CTimer()
	{
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_PerfFreq);
		QueryPerformanceCounter((LARGE_INTEGER *) &m_LastTime); 
		m_TimeScale			= 1.0f / m_PerfFreq;

		m_SampleCount       = 0;
		m_FrameRate			= 0;
	}
	~CTimer() { }

	void Tick()
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&m_CurrentTime);

		float fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

		m_LastTime = m_CurrentTime;
		m_TimeElapsed = fTimeElapsed;

		if ( fabsf(fTimeElapsed - m_TimeElapsed) < 1.0f  ) {
			memmove( &m_FrameTime[1], m_FrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float) );
			m_FrameTime[ 0 ] = fTimeElapsed;
			if ( m_SampleCount < MAX_SAMPLE_COUNT ) m_SampleCount++;
		} 

		m_TimeElapsed = 0.0f;
		if ( m_SampleCount > 0 ) {
			for ( ULONG i = 0; i < m_SampleCount; i++ ) m_TimeElapsed += m_FrameTime[ i ];
			m_TimeElapsed /= m_SampleCount;
		} 
	}
    float GetTimeElapsed() const
	{
		return m_TimeElapsed;
	}
};

