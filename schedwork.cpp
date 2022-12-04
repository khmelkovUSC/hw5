

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
    // prototype in header

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

    vector<size_t> currShifts(avail[0].size(), 0);
    AvailabilityMatrix isScheduled(avail.size(), std::vector<bool>(avail[0].size(), false));
    sched.push_back(std::vector<Worker_T>());

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, currShifts, isScheduled, 0, 0);


}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& currShifts,
    AvailabilityMatrix& isScheduled,
    size_t day,
    size_t posOfD
)
{
    if (posOfD >= dailyNeed) {
        if (day == avail.size()-1) return true;
        else {
            sched.push_back(std::vector<Worker_T>());
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currShifts, isScheduled, day + 1, 0)) return true;
            else sched.pop_back();
        }
    }
    // Try each worker recursively. The loop is only to make it easier to iterate through the required recursive calls
    for (size_t i = 0; i<avail[0].size(); i++) {
        // Try scheduling worker i
        if (avail[day][i] && !isScheduled[day][i] && currShifts[i] != maxShifts) {
            sched[day].push_back(i);
            isScheduled[day][i] = true;
            currShifts[i]++;

            // If there is a solution down this path, return true
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currShifts, isScheduled, day, posOfD + 1)) return true;
            // Otherwise unschedule worker i and let the next worker be tried
            else {
                sched[day].pop_back();
                isScheduled[day][i] = false;
                currShifts[i]--;
            }
        }
    }
    // If none of the workers can be scheduled for this position in the schedule, return false so that it can be handled higher up the recursive stack
    return false;
}
