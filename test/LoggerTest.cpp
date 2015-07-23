#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>

#include "../src/Logger.h"

#define NUM_THREADS 2
#define NUM_MESSAGES 5
#define TS_BUF_SIZE 100

void threadedMessageFINE(long id);
void threadedMessageFINEST(long id);

int main(int argc, char **argv){
  std::string logLevelString;

  // Grab log level string
  if(argv[1] != NULL)
    logLevelString = argv[1];
  else
    logLevelString = "fine";
    

  using namespace Logger;
  LogLevel logLevel;

  // Convert log level string to LogLevel
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

  // Test message LogLevel/LogType/indent
  setIndentLevel(2);
  log("Hello \tWorld!\n");
  log("INFO message!", LogLevel::INFO, 1);
  log("DEBUG: t = 5", LogType::DEBUG);

  setIndentLevel(1);
  log("ClassA::setData(const int)", LogType::METHOD);
  log("ClassA::ClassA() [default constructor]", LogType::CONSTRUCTOR);

  // Threaded test
  setIndentLevel(0);
  std::vector<std::thread> threads;
  
  for(int i = 0; i < NUM_THREADS; i++){
    log("main() create thread: " + std::to_string(i), LogType::DEBUG);
    if(i%2 == 0){
      threads.push_back(std::thread(threadedMessageFINE, (long)i));
    }
    else{
      threads.push_back(std::thread(threadedMessageFINEST, (long)i));
    }
  }
  
  log();
  log("synching threads...\n", LogLevel::INFO);
  for(auto& th : threads){
    th.join();
  }
}

void threadedMessageFINE(long id){
  long tid = id;
  Logger::log("Thread id: " + std::to_string(tid));

  for(int i = 0; i < NUM_MESSAGES; i++){
    Logger::setLogLevel(Logger::LogLevel::FINE);
    auto t = std::time(nullptr);
    //auto tm = *std::localtime(&t);
    auto tm = std::localtime(&t);

    char timestamp[TS_BUF_SIZE];

    std::stringstream buf;
    //buf << std::put_time(&tm, "%m/%d/%y");
    if(std::strftime(timestamp, sizeof(timestamp), "%T", tm)){
      buf << timestamp;
    }

    Logger::log("Thread " + std::to_string(tid) + " log at " + buf.str() + " FINE", Logger::LogLevel::FINE);

  }
}

void threadedMessageFINEST(long id){
  long tid = id;
  Logger::log("Thread id: " + std::to_string(tid));

  for(int i = 0; i < NUM_MESSAGES; i++){
    Logger::setLogLevel(Logger::LogLevel::FINEST);
    auto t = std::time(nullptr);
    //auto tm = *std::localtime(&t);
    auto tm = std::localtime(&t);

    char timestamp[TS_BUF_SIZE];

    std::stringstream buf;
    //buf << std::put_time(&tm, "%m/%d/%y");
    if(std::strftime(timestamp, sizeof(timestamp), "%T", tm)){
      buf << timestamp;
    }

    Logger::log("Thread " + std::to_string(tid) + " log at " + buf.str() + " FINEST", Logger::LogLevel::FINEST);
  }
  
}
