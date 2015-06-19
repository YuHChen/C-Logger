#include "Logger.h"

/***** Public Methods *****/
static void Logger::setLogLevel(LogLevel level){
  logLevel = level;
}

static void Logger::log(void){
  log("");
}

static void Logger::log(string message){
  log(message, DEFAULT_LOG_LEVEL);
}

static void Logger::log(string message, LogLevel level){
  performLogging(message, level);
}

static void Logger::log(string message, LogType type){
  LogType messageType = type;
  string formattedMessage = "Called ";
  switch(messageType){
  case LogType::CONSTRUCTOR:
  case LogType::OPERATOR:
    formattedMessage += message;
    log(formattedMessage, LogLevel::FINEST);
    break;
  case LogType::METHOD:
    formattedMessage += message;
    log(formattedMessage, LogLevel::FINER);
    break;
  case LogType::DEBUG:
    log(message, LogLevel::FINER);
    break;
  default:
    log(message);
  }
    
}

/***** Private Methods *****/
boolean Logger::canLogMessage(LogLevel messageLogLevel){
  std::underlying_type<LogLevel> mLogLevel = messageLogLevel;
  std::underlying_type<LogLevel> loggerLevel = logLevel;
  
  return (mLogLevel >= loggerLevel);
}

void Logger::performLogging(String message, LogLevel level){
  // beginLogging();
  if(canLogMessage(level)){
    // test
    std::cout << message << std::endl;
  }
  // endLogging();
}

