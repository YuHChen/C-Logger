#include <iostream>
//#include <fstream>
#include <string>
//#include <vector>

/* ADD LOCK for thread safety */

class Logger{

 public:
  ///// Types /////

  /*
   * Enumeration for the level at which to log.
   * Lower (finer) levels of logging appear toward the top. 
   * Higher (coarser) level of logging appear toward the bottom.
   */
  enum LogLevel {
    FINEST,
    FINER,
    FINE,
    ALL
  };

  /*
   * Enumeration for the type of logging.
   * Types toward the top are logged at lower levels 
   * than types toward the bottom.
   * ie: CONSTRUCTOR_INFO logs at FINEST, while INFO logs at FINE
   */
  enum LogType {
    CONSTRUCTOR_INFO,  // FINEST
    METHOD_INFO,       // FINER
    DEBUG,             // FINER
    INFO,              // FINE
    ERROR              // ALL
  };
  
  ///// Methods /////

  /* 
   * Sets the logging level of the Logger.
   * Messages logged at levels below (finer than) the level specified
   * will be not displayed, while messages above (coarser than) will
   * be displayed.
   */
  static void setLogLevel(LogLevel level);
  
  // logs an empty line
  static void log(void);
  
  // logs the message at the default level
  static void log(string message);
  
  // logs the message at the level specified
  static void log(string message, LogLevel level);
  
  // logs a formatted message of the type specified at the corresponding level
  static void log(String message, LogType type);

 private:
  ///// Constants /////
  string INDENT = "     ";
  int DEFAULT_INDENT_LEVEL = 1;

  ///// Fields /////
  LogLevel logLevel = FINE;
  boolean logToFile = false;
  //std::vector<string> filenames;

  ///// Methods /////
  //void beginLogging(void);
  //void endLogging(void);

  // Checks if the message is logged at or above (coarser than) the Logger's log level
  boolean canDisplayMessage(LogLevel messageLogLevel);

  // Performs the actual logging to the appropriate stream depending on type
  void performLogging(String message, LogLevel level, LogLevel type);
  
}; // end of class Logger
