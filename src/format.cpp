#include <string>
#include <sstream>
#include "format.h"
#include <iomanip>

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  
  string timestring;
  long sec;
  long minutes; 
  long hours;
  
  hours = seconds / 3600;
  minutes = (seconds / 60) % 60;
  sec = seconds % 60;
  
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << hours << ":"
     << std::setw(2) << minutes << ":"
     << std::setw(2) << sec;

  timestring = ss.str();
  //timestring = std::stringstream ss;  
return timestring; 
}