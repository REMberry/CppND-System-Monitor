#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "system.h"
#include "process.h"
#include "processor.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu()
{
	return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{
  processes_.clear();
  
  vector<int> pids = LinuxParser::Pids();
  
  for (unsigned int i = 0; i < pids.size(); i++) {
    Process p = Process(pids[i]);
    processes_.push_back(p);
  }

  std::sort(processes_.rbegin(), processes_.rend());
  //std::reverse(processes_.begin(), processes_.end());
  
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel()
{
  string kernel;
  kernel = LinuxParser::Kernel();
  return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  float mem = LinuxParser::MemoryUtilization();
  return mem;
}

// TODO: Return the operating system name
std::string System::OperatingSystem()
{
  string os;
  os = LinuxParser::OperatingSystem();
  return os;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses()
{
  int runprocesses = LinuxParser::RunningProcesses();
   return runprocesses; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  int processes = 0;
  
  processes = LinuxParser::TotalProcesses();
  
  return processes;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime()
{
   long uptime;
   uptime = LinuxParser::UpTime();
   //uptime = 845;
   return uptime;
}