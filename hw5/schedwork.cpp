#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isOverScheduled(const map<Worker_T, size_t>& shifts, const Worker_T worker, const size_t maxShifts);

bool canWork(const Worker_T worker, const size_t day, const AvailabilityMatrix& avail);

bool scheduleWorkers( const AvailabilityMatrix& avail, DailySchedule& sched, map<Worker_T, size_t>& shifts,
                      const size_t dailyNeed, const size_t maxShifts, size_t day = 0, int current_worker = 0);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());
    map<Worker_T, size_t> shifts;
    for(size_t worker = 0; worker < avail[0].size(); ++worker)
    {
      shifts[worker] = 0;
    }
    return scheduleWorkers(avail, sched, shifts, dailyNeed, maxShifts);
}
// Determines is a worker is availible to work during a given day
bool canWork(const Worker_T worker, const size_t day, const AvailabilityMatrix& avail)
{
  return avail[day][worker];
}
// Determiens if a given worker is is over shceduled
bool isOverScheduled(const map<Worker_T, size_t>& shifts, const Worker_T worker, const size_t maxShifts)
{
  return shifts.at(worker) >= maxShifts;
}
bool scheduleWorkers(const AvailabilityMatrix& avail, DailySchedule& sched, map<Worker_T, size_t>& shifts,
                      const size_t dailyNeed, const size_t maxShifts, size_t day, int current_worker)
{
  //Base Case
  if(day >= sched.size())
  {
    return true;
  }
  if(current_worker >= avail[0].size()) 
  {
    if(sched[day].size() <dailyNeed)
    {
      return false;
    }
    else
    {
      return scheduleWorkers(avail, sched, shifts, dailyNeed, maxShifts, day + 1, 0);
    }
  }
  
  if (canWork(current_worker, day, avail) && !isOverScheduled(shifts, current_worker, maxShifts))
  {
    sched[day].push_back(current_worker);
    shifts[current_worker]++;
    if(scheduleWorkers(avail, sched, shifts, dailyNeed, maxShifts, day, current_worker+1))
    {
      return true;
    }
    sched[day].pop_back();
    shifts[current_worker]--;
  }
  
   return scheduleWorkers(avail, sched, shifts, dailyNeed, maxShifts, day, current_worker+1);
}

