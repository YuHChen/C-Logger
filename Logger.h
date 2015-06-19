#include <iostream>
//#include <fstream>
#include <string>
//#include <vector>
#include <type_traits>

/* ADD LOCK for thread safety */

/*
 * Enumeration for the level at which to log.
 * Lower (finer) levels of logging appear toward the top. 
 * Higher (coarser) level of logging appear toward the bottom.
 * Messages at coarser log levels are more likely to be displayed.
 */
enum class LogLevel : int {
  FINEST,    // best for debugging
  FINER,     // usually for debugging
  FINE,      // usually for output
  INFO,      // usually for output
  OUTPUT,    // best for output
  ERROR,
  ALL
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

class Logger{

 public:
  ///// Methods /////

  /* 
   * Sets the logging level of the Logger.
   * Messages logged at levels below (finer than) the level specified
   * will be not displayed, while messages above (coarser than) will
   * be displayed.
   */
  static void setLogLevel(LogLevel level);
  
  // Logs an empty line at the default level
  static void log(void);
  
  // Logs the message at the default level
  static void log(string message);
  
  // Logs the message at the level specified
  static void log(string message, LogLevel level);
  
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
  static void log(String message, LogType type);

 private:
  ///// Constants /////
  static const string INDENT = "     ";
  static const int DEFAULT_INDENT_LEVEL = 1;
  static const LogLevel DEFAULT_LOG_LEVEL = LogLevel::INFO;

  ///// Fields /////
  static LogLevel logLevel = FINE;
  static boolean logToFile = false;
  //std::vector<string> filenames;

  ///// Methods /////
  //void beginLogging(void);
  //void endLogging(void);

  // Checks if the message is logged at or above (coarser than) the Logger's log level
  boolean canLogMessage(LogLevel messageLogLevel);

  // Performs the actual logging to the appropriate stream depending on type
  void performLogging(String message, LogLevel level);
  
}; // end of class Logger
