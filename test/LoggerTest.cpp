#include <string>

#include "../src/Logger.h"

int main(int argc, char **argv){
  std::string logLevelString;
   
  if(argv[1] != NULL)
    logLevelString = argv[1];
  else
    logLevelString = "fine";
    

  using namespace Logger;
  LogLevel logLevel;

  if(logLevelString.compare("all") == 0){
    logLevel = LogLevel::ALL;
  }
  else if(logLevelString.compare("finest") == 0){
    logLevel = LogLevel::FINEST;
  }
  else if(logLevelString.compare("finer") == 0){
    logLevel = LogLevel::FINER;
  }
  else if(logLevelString.compare("fine") == 0){
    logLevel = LogLevel::FINE;
  }
  else if(logLevelString.compare("info") == 0){
    logLevel = LogLevel::INFO;
  }
  else if(logLevelString.compare("output") == 0){
    logLevel = LogLevel::OUTPUT;
  }
  else if(logLevelString.compare("error") == 0){
    logLevel = LogLevel::ERROR;
  }
  else{
    logLevel = DEFAULT_LOG_LEVEL;
  }

  setLogLevel(logLevel);

  log("Hello World!");
  log("INFO message!", LogLevel::INFO);
  log("t = 5", LogType::DEBUG);

  log("ClassA::setData(const int)", LogType::METHOD);
  log("ClassA::ClassA() [default constructor]", LogType::CONSTRUCTOR);

}
