#include <string>

/*
You've created a popular app that makes requests to a server. Sometimes, the server sends back error messages.
You want to print these error messages out to the user, but only if you haven't already printed the same message in the last 10 seconds.
Each error message from the server contains a string and a timestamp (in seconds). 

Write a function that, given a message, determines whether or not we should print it.

Example:

Logger logger = new Logger();

// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true; 

// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;

// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;

// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;

// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;

// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;
*/

class Logger {
public:
    /** Initialize any necessary data structures here. */
    Logger();
    
    bool shouldPrintMessage(int timestamp, std::string message);
};
