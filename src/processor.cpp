#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
  float CPU_Percentage;
  
  
  std::vector<std::string> utilizations = LinuxParser::CpuUtilization();
  
  long user = stol(utilizations[0]);
  long nice = stol(utilizations[1]);
  long system = stol(utilizations[2]);
  long idle = stol(utilizations[3]);
  long iowait = stol(utilizations[4]);
  long irq = stol(utilizations[5]);
  long softirq = stol(utilizations[6]);
  long steal = stol(utilizations[7]);
  
  
  long PrevIdle = _idle + _iowait;
  long Idle = idle + iowait;
  
  
  long PrevNonIdle = _user + _nice + _system + _irq + _softirq + _steal;
  long NonIdle = user + nice + system + irq + softirq + steal;

  long PrevTotal = PrevIdle + PrevNonIdle;
  long Total = Idle + NonIdle;

  // differentiate: actual value minus the previous one
  
  float totald = Total - PrevTotal;
  float idled = Idle - PrevIdle;

  CPU_Percentage = (totald - idled)/totald;
  
  _user = user;
  _nice = nice;
  _system = system;
  _idle = idle;
  _iowait = iowait;
  _irq = irq;
  _softirq = softirq;
  _steal = steal;
  
  return CPU_Percentage;
}