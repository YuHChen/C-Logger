#include <iostream>
//#include <fstream>
#include <string>
//#include <vector>
#include <type_traits>

/* ADD LOCK for thread safety */

namespace Logger {

  // ===== Declarations ===== //
  ///// Types /////
  enum class LogLevel;
  enum class LogType;
  ///// Methods /////
  void setLogLevel(LogLevel level);
  bool canLogMessage(LogLevel messageLogLevel);
  //void beginLogging(void);
  //void endLogging(void);
  void performLogging(std::string message, LogLevel level);
  void log(std::string message, LogType type);
  void log(std::string message, LogLevel level);
  void log(std::string message);
  void log(void);

  // ===== Definitions ===== //
  ///// Types /////

  /*
   * Enumeration for the level at which to log.
   * Lower (finer) levels of logging appear toward the top. 
   * Higher (coarser) level of logging appear toward the bottom.
   * Messages at coarser log levels are more likely to be displayed.
   */
  enum class LogLevel : int {
    ALL = 0,
    FINEST = 10,    // best for debugging
    FINER = 20,     // usually for debugging
    FINE = 30,      // usually for output
    INFO = 30,      // usually for output
    OUTPUT = 999,   // best for output
    ERROR = 999,
  };

  /*
   * Enumeration for special types of logging messages.
   * Types toward the top are logged at lower levels 
   * than types toward the bottom.
   * ie: CONSTRUCTOR logs at FINEST, while DEBUG logs at FINER
   */
  enum class LogType : int {
    CONSTRUCTOR,   // FINEST
    OPERATOR,      // FINEST
    METHOD,        // FINER
    DEBUG,         // FINER
  };

  ///// Constants /////
  
  static const std::string INDENT;
  static const int DEFAULT_INDENT_LEVEL = 1;
  static const LogLevel DEFAULT_LOG_LEVEL = LogLevel::FINE;
  
  ///// Fields /////
  
  static LogLevel logLevel = DEFAULT_LOG_LEVEL;
  //static bool logToFile = false;
  //std::vector<std::string> filenames;
  
  ///// Methods /////
  
  /* 
   * Sets the logging level of the Logger.
   * Messages logged at levels below (finer than) the level specified
   * will be not displayed, while messages above (coarser than) will
   * be displayed.
   */
  void setLogLevel(LogLevel level){
    logLevel = level;
  }
  
  // Checks if the message is logged at or above (coarser than) the Logger's log level
  bool canLogMessage(LogLevel messageLogLevel){
    auto mLogLevel = messageLogLevel;
    auto loggerLevel = logLevel;
    
    return (mLogLevel >= loggerLevel);
  }

  //void beginLogging(void);
  //void endLogging(void);

  
  // Performs the actual logging to the appropriate stream depending on type
  void performLogging(std::string message, LogLevel level){
    // beginLogging();
    if(canLogMessage(level)){
      // test
      std::cout << message << std::endl;
    }
    // endLogging();
  }

  // Logs the message at the level specified
  void log(std::string message, LogLevel level){
    performLogging(message, level);
  }

  // Logs the message at the default level
  void log(std::string message){
    log(message, DEFAULT_LOG_LEVEL);
  }

  // Logs an empty line at the default level
  void log(void){
    log("");
  }
    
  /*
   * Logs a formatted message according to the type specified, 
   * at the corresponding level. 
   * Messages are expected to have the following format 
   * for the corresponding type:
   * CONSTRUCTOR: SCOPE::CONSTRUCTOR(PARAMS) [type of constructor]
   * OPERATOR: SCOPE::OPERATOR(PARAMS)
   * METHOD: SCOPE::FUNCTION_NAME(PARAMS)
   * DEBUG: NO FORMAT
   */
  void log(std::string message, LogType type){
    LogType messageType = type;
    std::string formattedMessage = "Called ";
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
  
} // end of namespace Logger
