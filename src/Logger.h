#include <iostream>
//#include <fstream>
#include <string>
//#include <vector>
#include <type_traits>
#include <mutex>

namespace Logger {

  // ===== Declarations ===== //
  ///// Types /////
  enum class LogLevel;
  enum class LogType;
  ///// Methods /////
  void setLogLevel(LogLevel level);
  void setIndentLevel(int level);
  bool canLogMessage(LogLevel messageLogLevel);
  void beginLogging(void);
  void endLogging(void);
  void performLogging(std::string message, LogLevel level, int indent);
  void log(std::string message, LogType type, int indent);
  void log(std::string message, LogType type);
  void log(std::string message, LogLevel level, int indent);
  void log(std::string message, LogLevel level);
  void log(std::string message, int indent);
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
  
  static const std::string INDENT = "   ";    // size of an indent
  static const int BASE_INDENT_LEVEL = 0;     // lowest indent level
  static const int DEFAULT_INDENT_LEVEL = 0;                   
  static const LogLevel DEFAULT_LOG_LEVEL = LogLevel::FINE;

  ///// Fields /////
  
  static LogLevel logLevel = DEFAULT_LOG_LEVEL;      // current log level of the logger
  static int indentLevel = DEFAULT_INDENT_LEVEL;     // current indent level for messages
  static std::mutex logLevel_lock;
  static std::mutex indentLevel_lock;
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
    logLevel_lock.lock();
    logLevel = level;
    logLevel_lock.unlock();
  }

  /*
   * Sets the indent level of the Logger.
   * Messages without a specified indent level, logged after this method,
   * will be logged at indentLevel specified.
   */
  void setIndentLevel(int level){
    indentLevel_lock.lock();
    indentLevel = level;
    indentLevel_lock.unlock();
  }
  
  // Checks if the message is logged at or above (coarser than) the Logger's log level
  bool canLogMessage(LogLevel messageLogLevel){
    auto mLogLevel = messageLogLevel;
    auto loggerLevel = logLevel;
    
    return (mLogLevel >= loggerLevel);
  }

  void beginLogging(void){
    logLevel_lock.lock();
    indentLevel_lock.lock();
  }
  
  void endLogging(void){
    logLevel_lock.unlock();
    indentLevel_lock.unlock();
  }
  
  // Performs the actual logging to the appropriate stream depending on type
  void performLogging(std::string message, LogLevel level, int indent){
    beginLogging();
    // place the message at the correct indent level
    std::string indentedMessage = "";
    for(int i = BASE_INDENT_LEVEL; i < indent; i++){
      indentedMessage += INDENT;
    }
    indentedMessage += message;
    if(canLogMessage(level)){
      // change implementation here for different behaviors
      std::cout << indentedMessage << std::endl;
    }
    endLogging();
  }

  // Logs the message at the level specified with specified indent level
  void log(std::string message, LogLevel level, int indent){
    performLogging(message, level, indent);
  }

  // Logs the message at the level specified with the current indent level
  void log(std::string message, LogLevel level){
    performLogging(message, level, indentLevel);
  }

  // Logs the message at the default level with specified indent level
  void log(std::string message, int indent){
    log(message, DEFAULT_LOG_LEVEL, indent);
  }

  // Logs the message at the default level with the current indent level
  void log(std::string message){
    log(message, DEFAULT_LOG_LEVEL, indentLevel);
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
