#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
  string line;
  string os, version, kernel;
  std::ifstream filestream(kProcDirectory + kVersionFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  string line;
  string key;
  string value;
  
  float memtotal;
  float memfree;
  
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      
      while (linestream >> key >> value)
      {
        if (key == "MemTotal") memtotal = std::stof(value);
        if (key == "MemFree") memfree = std::stof(value);
      }
    }
  }
  return ((memtotal - memfree) / memtotal); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
  string line;
  long time;

  std::ifstream filestream(kProcDirectory +  kUptimeFilename);
   
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> time;
  }

  return time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

long LinuxParser::ActiveJiffies(int pid)
{
  	
	return 0;
}
  
std::vector<int> LinuxParser::ProcessCpuUtilization(int pid)
{
  string line;
  string split;
  std::vector<int> result;
  
  std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) +  LinuxParser::kStatFilename);
  
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    
 	std::istream_iterator<string> beg(linestream), end;
    vector<string> splittedline(beg, end);
    
  result.push_back(stoi(splittedline[13]));
  result.push_back(stoi(splittedline[14]));
  result.push_back(stoi(splittedline[15]));
  result.push_back(stoi(splittedline[16]));
  result.push_back(stoi(splittedline[21]));
    
  }
  return result;
}
/*
  return 0;
  
    if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    
    while (linestream >> split)
    {
      splittedline.push_back(split); 
    }
    
    result =  (std::stol(splittedline[21]) / sysconf(_SC_CLK_TCK));
    
    return result;
  }
  */



// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
  string line, cpu, cpu_time;
  vector<string> cpu_utilizations;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    
    //std::remove(line.begin(), line.end(), 'cpu  ');
    
    std::istringstream linestream(line);
    linestream >> cpu;
	
    
    while (linestream >> cpu_time)
    {
      cpu_utilizations.emplace_back(cpu_time);
    }
  }
 
  return cpu_utilizations;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{  
  string line;
  string key;
  string value;
  
  int processes = 0;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      //std::remove(line.begin(), line.end(), ' ');
      //std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      
      while (linestream >> key >> value)
      {
        if (key == "processes") processes = std::stoi(value);
      }
    }
  }
  return processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string line;
  string key;
  string value;
  
  int processes = 0;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      //std::remove(line.begin(), line.end(), ' ');
      //std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      
      while (linestream >> key >> value)
      {
        if (key == "procs_running") processes = std::stoi(value);
      }
    }
  }
  return processes;

return 0;

}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
  string command;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
    return command;
  }
  return command;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{
  string ram;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "VmSize:")
        {
          ram = std::to_string(int(std::stod(value) / 1000));
        }
      }
    }
  }
  return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
  string uid;
  string line;
  string key;
  string value;
  
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "Uid:")
        {
          uid = value;
        }
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{
  string uid; 
  string line;
  string user;
  string value;
  string spacer;
  string name;
  
  uid = Uid(pid);
  
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      
      while (linestream >> name >> spacer >> value)
      {
        if (value == uid)
        {
          user = name;
        }
      }
    }
  }
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
  string line;
  string split;
  vector<string> splittedline;
  
  long result;
  
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    
    while (linestream >> split)
    {
      splittedline.push_back(split); 
    }
    
    result =  (std::stol(splittedline[21]) / sysconf(_SC_CLK_TCK));
    
  }
  return result;
}

///////////////////////////