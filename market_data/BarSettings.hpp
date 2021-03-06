#pragma once

#include <chrono>
#include <algorithm>

namespace tf
{

enum BarTimeSpan {
   TICK, 
   ONE_SECOND, 
   FIVE_SECONDS,
   FIFTEEN_SECONDS, 
   THIRTY_SECONDS, 
   ONE_MINUTE, 
   TWO_MINUTES, 
   THREE_MINUTES, 
   FIVE_MINUTES, 
   FIFTEEN_MINUTES, 
   THIRTY_MINUTES, 
   ONE_HOUR, 
   ONE_DAY,
   INVALID 
};

/****
 * @brief Convert common strings to their equivalent BarTimeSpan
 * Example: nD= number of Days, nH = number of Hours, nM = number of minutes, nS = number of seconds
 * @param in the string
 * @returns A BarTimeSpan
 */
BarTimeSpan StringToBarTimeSpan(const std::string& in);

class BarSettings
{
   public:
   BarSettings()
      : endDateTime(std::chrono::system_clock::now() ),
      duration( std::chrono::hours(24) )
      {}
   std::chrono::system_clock::time_point endDateTime;
   std::chrono::system_clock::duration duration;
   BarTimeSpan barTimeSpan;
};

BarSettings StringToDefaultBarSettings(const std::string& in);

} // namespace tf