#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cmath>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string LOG_COMMIT_STARTER = "Commit: ";



// Class implementation
GitInt::GitInt()
{
  head_ = 0;
  std::map<std::string, int> diffs;
  CommitObj dummy("", diffs, 0);
  commits_.push_back(dummy);
}
void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    std::string filename;
    int value;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);

    if (cmd == "quit") {
        quit = true;
    }
    // Continue checking/processing commands
    else if(cmd == "create")
    {
      ss >> filename >> value;
      if(ss.fail())
      {
        throw std::runtime_error(INVALID_COMMAND);
      }
      create(filename, value);
    }
    else if(cmd == "edit")
    {
      ss >> filename >> value;
      if(ss.fail())
      {
        throw std::runtime_error(INVALID_COMMAND);
      }
      edit(filename, value);
    }
    else if(cmd == "display")
    {
      bool check = false;
      if(cmd_line == "display")
      {
        display_all();
        check = true;
      }

      if(check == false)
      {
        int number;
        ss >> number;

        if(ss.fail())
        {
          ss.clear();
          std::stringstream temp(cmd_line);
          std:: string test;

          temp >> test >> filename;
          display(filename);
        }
        else{
          display_commit(number);
        }
      }
    }
    //adds a file every time a file is entered on cmd_line
    else if(cmd == "add")
    {
      while(ss >> filename)
      {
        if(files_.find(filename) == files_.end())
        {
          throw std::runtime_error(INVALID_COMMAND);
        }
        add(filename);
      }
    }
    //still need to check for more errors
    else if(cmd == "commit")
    {
      std::string message;
      std::string skip;
      //skips everything until the first quote then gets everything until the
      // second quote

      std::getline(std::getline(ss, skip, '"'), message, '"');
      if(ss.fail() || message == "")
      {
        throw std::runtime_error(INVALID_COMMAND);
      }
      commit(message);
    }
    else if(cmd == "tag")
    {

      bool check = false;
      std::string skip;

      ss >> skip;

      //will enter if nothiing is entered after tag
      if(cmd_line == "tag")
      {
        tags();
        check = true;
      }
      else if(skip != "-a")
      {
        throw std::runtime_error(INVALID_COMMAND);
      }

      if(!check)
      {
        std::string tagname;

        ss >> tagname;
        create_tag(tagname, head_);
      }

    }
    else if(cmd == "log")
    {
      log();
    }
    else if(cmd == "checkout")
    {
       int commit_num;
       ss >> commit_num;

       if(!ss.fail())
       {
         bool check_ = checkout(commit_num);
       }
       else{
         ss.clear();
         std::stringstream temp(cmd_line);
         std::string tagname;
         std::string throw_away;

         temp >> throw_away >> tagname;
         bool check = checkout(tagname);
       }

    }
    else if(cmd == "diff")
    {
      int from;
      int to;

      if(cmd_line == "diff")
      {
        diff(-1);
      }
      else{
        ss >> from;

        if(ss.fail()){
          //bad index
          throw std::runtime_error(INVALID_COMMAND);
        }

        ss >> to;
        if(ss.fail())
        {
          ss.clear();
          diff(from);
        }
        else{
          diff(from, to);
        }
      }
    }
    else{
      throw std::runtime_error(INVALID_COMMAND);
    }
    return quit;
}



void GitInt::create(const std::string& filename, int value)
{
  std::map<std::string, int>::iterator it = files_.find(filename);
  if(it != files_.end())
  {
    throw std::invalid_argument(INVALID_OPTION);
  }
  files_.insert(make_pair(filename, value));
}



void GitInt::edit(const std::string& filename, int value)
{
  std::map<std::string, int>::iterator it;
  it = files_.find(filename);

  if(it == files_.end())
  {
    throw std::invalid_argument(INVALID_OPTION);
  }
  it->second = value;
}



void GitInt::display(const std::string& filename) const
{
  std::map<std::string, int>::const_iterator it;
  it = files_.find(filename);
  if(it == files_.end())
  {
    throw std::invalid_argument(INVALID_OPTION);
  }
  std::cout << it->first << " : " << it->second <<std::endl;
}

void GitInt::display_all() const
{
  display_helper(files_);
}


void GitInt::display_commit(CommitIdx commit) const
{
    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    display_helper(commits_[commit].diffs_);
}


//check for errors, not done
void GitInt::add(std::string filename)
{
  std::set<std::string>::iterator it = stagedFiles_.find(filename);
  if(it != stagedFiles_.end())
  {
    throw std::invalid_argument(INVALID_OPTION);
  }
  stagedFiles_.insert(filename);
}




void GitInt::commit(std::string message)
{
  std::stringstream msg(message);
  std::string current;

  CommitIdx parent = head_;

  //the parent has been stored
  //now need to get the diffs_
  std::map<std::string, int> diff_map;

  if(commits_.size() == 1)
  {
    std::set<std::string>::iterator it;
    std::map<std::string, int>::iterator map_it;

    for(it = stagedFiles_.begin(); it != stagedFiles_.end(); it++)
    {
      map_it = files_.find(*it);
      diff_map.insert(make_pair(map_it->first, map_it->second));
    }
    CommitObj comm(message, diff_map, parent);
    commits_.push_back(comm);
  }
  else{
    diff_map = buildState(head_, 0);
    CommitObj new_commit(message, diff_map, parent);
    commits_.push_back(new_commit);
  }
  head_ = commits_.size()-1;
  CommitFiles snapshot(head_, files_);
  commit_files.insert(make_pair(head_, snapshot));
  stagedFiles_.clear();
}



void GitInt::create_tag(const std::string& tagname, CommitIdx commit)
{
  std::map<std::string, int>::iterator it = tag_.find(tagname);
  if(it != tag_.end())
  {
    throw std::invalid_argument(INVALID_OPTION);
  }
  //inserts a tag to the map with the tagname and the currently checked out commit
  tag_.insert(make_pair(tagname, commit));
}



void GitInt::tags() const
{
  std::map<std::string, int>::const_iterator it;
  for(it = tag_.begin(); it != tag_.end(); it++)
  {
    std::cout << it->first << endl;
  }
}


//overwrites files with the commit index passed
bool GitInt::checkout(CommitIdx commitIndex)
{
  std::map<CommitIdx, CommitFiles>::iterator it = commit_files.find(commitIndex);
  if(it == commit_files.end())
  {
    throw std::runtime_error(INVALID_COMMAND);
  }
  files_ = (it->second).currentFiles_;
  head_ = commitIndex;
  return true;
}



//overwrites files_ with  the tag passed
bool GitInt::checkout(std::string tag)
{
  std::map<std::string, CommitIdx>::iterator it = tag_.find(tag);
  if(it == tag_.end())
  {
    throw std::runtime_error(INVALID_COMMAND);
  }
  CommitIdx commitIndex = it->second;
  std::map<CommitIdx, CommitFiles>::iterator i = commit_files.find(commitIndex);
  files_ = (i->second).currentFiles_;
  head_ = commitIndex;
  return true;
}



void GitInt::log() const
{
  CommitIdx parent = head_;
  while(parent != 0)
  {
    std::cout << LOG_COMMIT_STARTER << parent << std::endl;
    std::cout << commits_[parent].msg_ << std::endl;
    std::cout << endl;
    parent = commits_[parent].parent_;
  }
}

void GitInt::diff(CommitIdx to) const
{
  std::map<std::string, int> display_map;
  std::map<std::string, int>::const_iterator file_iterator;
  std::map<CommitIdx, CommitFiles>::const_iterator commit_files_iterator;
  std::map<std::string, int>::const_iterator current_files_iterator;

  if(commits_.size() <= 2){
    display_helper(files_);
  }
  //check of a valid index
  if(int(to) > (int)commits_.size())
  {
    throw std::runtime_error(INVALID_COMMAND);
  }
  //if diff is the only thing entered
  else if(to == -1)
  {
    int num = head_;
    if(num == 0)
    {
      display_helper(files_);
      return;
    }
    for(file_iterator = files_.begin(); file_iterator != files_.end(); file_iterator++)
    {
      commit_files_iterator = commit_files.find(head_);
      current_files_iterator = (commit_files_iterator->second).currentFiles_.find(file_iterator->first);
      if(current_files_iterator == (commit_files_iterator->second).currentFiles_.end())
      {
        display_map.insert(make_pair(file_iterator->first, file_iterator->second));
      }
      else{
        int old_num = current_files_iterator->second;
        int new_num = file_iterator->second;
        int difference = abs(new_num - old_num);
        display_map.insert(make_pair(file_iterator->first, difference));
      }
    }
  }
  else{
  //if the only number passed is the commit-num
  int num = head_;
  if(num == 0)
  {
    display_helper(files_);
    return;
  }
    for(file_iterator = files_.begin(); file_iterator != files_.end(); file_iterator++)
    {
      commit_files_iterator = commit_files.find(to);
      current_files_iterator = (commit_files_iterator->second).currentFiles_.find(file_iterator->first);
      if(current_files_iterator == (commit_files_iterator->second).currentFiles_.end())
      {
        //the file doesnt exist in he prev commit
        display_map.insert(make_pair(file_iterator->first, file_iterator->second));
      }
      else{
        int old_num = current_files_iterator->second;
        int new_num = file_iterator->second;
        int difference = abs(new_num - old_num);
        display_map.insert(make_pair(file_iterator->first, difference));
      }
    }
   }
   display_helper(display_map);
}

//if there are two arguments passed commit-n and commit-m
//should subtract the files in commit n from m
//from - to
void GitInt::diff(CommitIdx from, CommitIdx to) const
{
  std::map<std::string, int> display_map;
  std::map<CommitIdx, CommitFiles>::const_iterator x = commit_files.find(from);
  std::map<CommitIdx, CommitFiles>::const_iterator y = commit_files.find(to);
  std::map<std::string, int> from_map = (x->second).currentFiles_;
  std::map<std::string, int> to_map = (y->second).currentFiles_;
  std::map<std::string, int>::const_iterator for_loop;
  std::map<std::string, int>::const_iterator map_it;

  for(for_loop = from_map.begin(); for_loop != from_map.end(); for_loop++)
  {
    map_it = to_map.find(for_loop->first);
    //the file isnt in a previous commit
    if(map_it == to_map.end())
    {
      display_map.insert(make_pair(for_loop->first, for_loop->second));
    }
    else{
      int m_int = map_it->second;
      int n_int = for_loop->second;
      int difference = n_int - m_int;
      if(difference < 0)
      {
        throw std::runtime_error(INVALID_COMMAND);
      }
      display_map.insert(make_pair(for_loop->first, difference));
    }
  }
  display_helper(display_map);
}


bool GitInt::valid_commit(CommitIdx commit) const
{
  int size = commits_.size();
  if(commit > size || commit == 0)
  {
    return false;
  }
  return true;
}

std::map<std::string, int> GitInt::buildState(CommitIdx from, CommitIdx to)
  const
{
  std::map<std::string, int> return_map;
  std::map<std::string, int>::const_iterator map_it;
  std::map<std::string, int> temp_map;
  std::map<CommitIdx, CommitFiles>::const_iterator commit_files_iterator;
  std::set<std::string>::const_iterator set_it;
  std::map<std::string, int>::const_iterator current_files_iterator;
  std::map<std::string, int>::const_iterator files_iterator;

  //iterate through the staged files
  for(set_it = stagedFiles_.begin(); set_it != stagedFiles_.end(); set_it++)
  {
    //iterate through the commit diffs_ until we fild a matching file to *it
    CommitIdx parent = from;
    bool found = false;
    while(!found && parent != 0){
      map_it = commits_[parent].diffs_.find(*set_it);
      if(map_it != commits_[parent].diffs_.end())
      {
        //we found the file
        //find the file in commit_files
        commit_files_iterator = commit_files.find(parent);
        //find file in commit_files' currentFiles_
        current_files_iterator = (commit_files_iterator->second).currentFiles_.find(*set_it);
        //store that number
        int old_num = current_files_iterator->second;
        //find the most recent file and its content
        files_iterator = files_.find(*set_it);
        int new_num  = files_iterator->second;
        int difference = abs(new_num - old_num);
        //insert the value in the map and continue to the next iteration
        return_map.insert(make_pair(*set_it, difference));
        found = true;
      }
      else{
        //next iteration
        parent = commits_[parent].parent_;
      }
    }
    if(!found)
    {
      std::map<std::string, int>::const_iterator n = files_.find(*set_it);
      return_map.insert(make_pair(*set_it, n->second));
    }
  }
  return return_map;
}

void GitInt::display_helper(const std::map<std::string, int>& dat) const
{
    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}


void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}
