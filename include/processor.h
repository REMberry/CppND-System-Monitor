#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
   private:
  long _user;
  long _nice;
  long _system;
  long _idle;
  long _iowait;
  long _irq;
  long _softirq;
  long _steal;
};

#endif