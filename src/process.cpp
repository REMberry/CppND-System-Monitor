#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "system.h"
#include <iomanip>

using std::string;
using std::to_string;
using std::vector;

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
{
  _pid = pid;
  _user = LinuxParser::User(_pid);
  _command = LinuxParser::Command(_pid);
  _ram = LinuxParser::Ram(_pid);
  _upTime = LinuxParser::UpTime() - LinuxParser::UpTime(_pid);
  _cpuUtilization = Process::CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid()
{
	return _pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
  std::vector<int> time = LinuxParser::ProcessCpuUtilization(_pid);
  long uptime = LinuxParser::UpTime();
  
  int utime		= time[0];
  int stime		= time[1];
  int cutime	= time[2];
  int cstime	= time[3];
  int starttime = time[4];
  
  float cps = sysconf(_SC_CLK_TCK);
  
  float total_time = utime + stime + cutime + cstime;
  float scps       = (starttime / cps);
  float seconds    = uptime - scps;
  float cpu        = 1.0*(total_time / cps) / seconds;
  
  _cpuUtilization = cpu;
  
  
  
  //float total_time = utime_ + stime_ + cutime_ + cstime_;
  //float seconds = uptime - (starttime_ / hertz_);
  //float cpu_usage = (total_time / hertz_) / seconds;
  
  return _cpuUtilization;
}

// TODO: Return the command that generated this process
string Process::Command()
{
  //only for debug
  //std::stringstream stream;
  //stream << std::fixed << _cpuUtilization;
  //std::string s = stream.str();
  //return s;
  return _command;
}

// TODO: Return this process's memory utilization
string Process::Ram()
{ 
  return _ram;
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
  //return LinuxParser::Uid(_pid);
  return _user;  
}

// TODO: Return the age of this process (in seconds)

long int Process::UpTime()
{
  return _upTime;
}


// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function

bool Process::operator<(Process const& a) const
{
  return  _cpuUtilization < a._cpuUtilization;
}