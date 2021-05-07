#include <iostream>
#include "gitint.h"
// Add any necessary headers
using namespace std;

void print_exception_message(const std::string& what_msg);

int main()
{

    GitInt g;
    string cmd_line;
    bool quit = false;
    const string PROMPT_STARTER = "$ ";

    g.print_menu();
    cout << PROMPT_STARTER;
    getline(cin, cmd_line);
    // Add your code here
    try {
      quit = g.process_command(cmd_line);
    }
    catch (const std::runtime_error& msg) {
      string s = msg.what();
      print_exception_message(s);
    }
    catch (const std::invalid_argument& msg) {
      string s = msg.what();
      print_exception_message(s);
    }
    while(!quit)
    {
      cout << PROMPT_STARTER;
      getline(cin, cmd_line);
      try {
        quit = g.process_command(cmd_line);
      }
      catch (const std::runtime_error& msg) {
        string s = msg.what();
        print_exception_message(s);
      }
      catch (const std::invalid_argument& msg) {
        string s = msg.what();
        print_exception_message(s);
      }
    }
    return 0;

}

void print_exception_message(const std::string& what_msg)
{
  cout << "Error - " << what_msg << endl;
}
