//----------------------------------------------------------------------------//
//                             MICRO COUNTER CLASS                            //
//----------------------------------------------------------------------------//
//  Author: Łukasz Korbel, e-mail: korbel85@gmail.com                         //
//  Licence: GPL                                                              //
//  Version: 1.00                                                             //
//----------------------------------------------------------------------------//
//  Version info:                                                             //
//  1.00 - basic time measurements                              // 26.09.2009 //
//----------------------------------------------------------------------------//

#ifndef MICRO_COUNTER_H
#define MICRO_COUNTER_H

//System time includes
//----------------------------------------------------------------------------//
#include <sys/time.h>

//! Time counting in microseconds
/*! Manages time measurements on basis of gettimeofday(...) function from 
sys/time.h. Single call of functions start() and stop() will set value 
elapsedTime_ to amount of microsecods between calls. Multiple call of start() 
and stop() in sequence will computes average of elapsed times from all calls. */
//----------------------------------------------------------------------------//
class MicroCounter
{
    public:
        MicroCounter() : elapsedTime_(0), frequency_(0), averageTime_(0), n_(1) { };
        ~MicroCounter() { };

        /*! Set time of events start. */
        void start() { gettimeofday( &startTime_, 0 ); }

        /*! Returns time elapsed from start call. */
        const double& update()
        {
            gettimeofday( &stopTime_, 0 ); 
            return elapsedTime_ = 1e6 * (stopTime_.tv_sec -startTime_.tv_sec) + 
                            stopTime_.tv_usec - startTime_.tv_usec;
        }

        /*! Set time of events end. Sets diffrence between stop and start to 
        elapsed time value, computes frequency and average */
        void stop()
        {
            gettimeofday( &stopTime_, 0 );
            elapsedTime_ = 1e6 * (stopTime_.tv_sec -startTime_.tv_sec) + 
                           stopTime_.tv_usec - startTime_.tv_usec;
            averageTime_ = (n_ * averageTime_ + elapsedTime_) / (n_ + 1);
            n_++;
            frequency_ = 1e6 / elapsedTime_;
            startTime_ = stopTime_;
        }

        /*! Clears average time. */
        void resetAverage() { averageTime_ = 0; n_ = 1; }

        /*! Returns time elapsed between start() ans stop() functions calls as a 
        measure of event time. \return elapsed time in microseconds [us]*/
        const double& elapsedTime() const { return elapsedTime_; }

        /*! Computes events frequency on basis of elapsed time. 
        \return event frequency in [Hz] */
        const double& eventFrequency() const { return frequency_; }

        /*! Return average of all times measured. Cleared by reset function. */
        const double& averageTime() const { return averageTime_; }

    protected:
        struct timeval startTime_, stopTime_;
        double elapsedTime_, frequency_, averageTime_;
        int n_;
};
//----------------------------------------------------------------------------//

#endif //MICRO_COUNTER_H
