#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "streetgrid.h"
#include "derived_events.h"
using namespace std;

StreetGrid::StreetGrid(
    const std::vector<unsigned int> rowCapacities,
    const std::vector<unsigned int> colCapacities)
    : rowCapacities_(rowCapacities), colCapacities_(colCapacities)
{
    n = rowCapacities.size();
    m = colCapacities.size();
    expectedVehicles_ = 0;

    // TO BE COMPLETED
    rowSeg_ = new int* [n]; //get the rows
    //set the dynamic array of size[n][m]
    for(size_t i = 0; i<n; i++){
      rowSeg_[i] = new int[m-1];
    }
    //initialize all elements to 0
    for(size_t i = 0; i<n; i++){
      for(size_t j = 0; j<m-1; j++){
        rowSeg_[i][j] = 0;
      }
    }

    colSeg_ = new int* [m]; //get the rows
    //set the dynamic array of size[n][m]
    for(size_t i = 0; i<m; i++){
      colSeg_[i] = new int[n-1];
    }
    //initialize all elements to 0
    for(size_t i = 0; i<m; i++){
      for(size_t j = 0; j<n-1; j++){
        colSeg_[i][j] = 0;
      }
    }
    //setting the initial blockages to 0
    blockages_ = new int* [n];
    for(size_t i = 0; i<n; i++){
      blockages_[i] = new int[m];
    }
    for(size_t i = 0; i<n; i++){
      for(size_t j = 0; j<m; j++){
        blockages_[i][j] = 0;
      }
    }
    //allocating the indicies
    int num = 0;
    indexes_ = new int* [n];
    for(size_t i = 0; i<n; i++){
      indexes_[i] = new int[m];
    }
    for(size_t i = 0; i<n; i++){
      for(size_t j = 0; j<m; j++){
        indexes_[i][j] = num;
        num++;
      }
    }
    // Call monitor state to output starting state
    monitorState();
}

StreetGrid::~StreetGrid(){
  for(size_t i = 0; i<n; i++){
    delete [] rowSeg_[i];
  }
  delete [] rowSeg_;

  for(size_t i = 0; i<m; i++){
    delete [] colSeg_[i];
  }
  delete [] colSeg_;

  for(size_t i = 0; i<n; i++){
    delete [] blockages_[i];
  }
  delete [] blockages_;

  for(size_t i = 0; i<n; i++){
    delete [] indexes_[i];
  }
  delete [] indexes_;

}

size_t StreetGrid::numRows() const
{
    return n;
}
size_t StreetGrid::numCols() const
{
    return m;
}
void StreetGrid::setExpected(size_t expectedVehicles)
{
    expectedVehicles_ = expectedVehicles;
}

void StreetGrid::outputCompletedVehicles(std::ostream& ostr) const
{
    for(auto v : completed_) {
        ostr << v.end << " " << v.id << std::endl;
    }
}

bool StreetGrid::allVehiclesArrived() const
{
    return completed_.size() == expectedVehicles_;
}

void StreetGrid::monitorState()
{
    std::cout << "State: " << std::endl;
    std::cout << std::setw(4) << " ";

    // Print header row with column capacities
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << colCapacities_[cidx] << " " <<  std::setw(4) << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << "====="  << "=====";
    }
    std::cout << std::endl;

    // Start printing grid data
    for(size_t ridx = 0; ridx < n; ++ridx) {
        // Print row capacity
        std::cout << std::setw(2) << rowCapacities_[ridx] << " |";
        // Print row occupancies
        for(size_t cidx = 0; cidx < m; ++cidx) {
            std::cout << std::setw(4) << "+" << " ";
            if(cidx < m-1) {
                if(isBlocked(ridx,cidx,true)) {
                    std::cout << std::setw(3) << getRowOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getRowOccupancy(ridx,cidx);
                }
            }
        }
        std::cout << std::endl;
        std::cout <<  "   |";
        // Print column occupancies
        if(ridx < n-1) {
            for(size_t cidx = 0; cidx < m; ++cidx) {
                if(isBlocked(ridx,cidx,false)) {
                    std::cout << std::setw(3) << getColOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getColOccupancy(ridx,cidx);
                }
                std::cout << std::setw(4) << " " << " " ;
            }
        }
        std::cout << std::endl;

    }
}

size_t StreetGrid::getRowOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    if(row >= n || col >= m || col < 0 || row < 0){
      throw std::logic_error("accessing an invalid row or col index");
    }
    size_t retval = 0;
    for(size_t i = col; i<m-1; i++){
      retval+=rowSeg_[row][i];
    }
    return retval;
}

size_t StreetGrid::getColOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    if(row >= n || col >= m || col < 0 || row < 0){
      throw std::logic_error("accessing an invalid row or col index");
    }
    size_t retval = 0;
    for(size_t i = row; i<n-1; i++){
      retval+=colSeg_[i][col];
    }
    return retval;

}

bool StreetGrid::isBlocked(size_t row, size_t col, bool rowDir) const
{
    // TO BE COMPLETED
    if(row >= n || col >= m || col < 0 || row < 0){
      throw std::logic_error("accessing an invalid row or col index");
    }
    if(rowDir){
      for(size_t i = col; i<m; i++){
        if(blockages_[row][i] == 0)
        {
          return false;
        }
      }
    }
    else{
      for(size_t i = row; i<n; i++){
        if(blockages_[i][col] == 0)
        {
          return false;
        }
      }
    }
    return true;
}

bool StreetGrid::shouldChooseRow(size_t row, size_t col)
{
    // TO BE COMPLETED
    //check if we are at an edge
    bool south = true;
    bool east = true;
    if(row == n-1){
      south = false;
    }
    else if(col == m-1){
      east = false;
    }

    //calculate the times and make a decision
    size_t t = 1;
    int eastTime = std::max(t, (1+getRowOccupancy(row, col)) / rowCapacities_[row]) * SCALE_FACTOR;
    int southTime = std::max(t, (1+getColOccupancy(row, col)) / colCapacities_[col]) * SCALE_FACTOR;
     //if there is a tie with times at an intersection, add to the intersection
      //history and determine if we should go east or south based on that
     if(eastTime == southTime){
       std::map<int, bool>::iterator i = intersectionHistory_.find(indexes_[row][col]);
       //we have come accross a tie before here
       if(i != intersectionHistory_.end()){
         //if they went east last go south
         if(i->second){
           if(south){
             intersectionHistory_.erase(indexes_[row][col]);
             intersectionHistory_.insert(std::make_pair(indexes_[row][col], false));
             return false;
           }
           else{
             intersectionHistory_.erase(indexes_[row][col]);
             intersectionHistory_.insert(std::make_pair(indexes_[row][col], true));
             return true;
           }
         }
         //if they went south last go east if possible
         else{
           if(east)
           {
             intersectionHistory_.erase(indexes_[row][col]);
             intersectionHistory_.insert(std::make_pair(indexes_[row][col], true));
             return true;
           }
           else{
             intersectionHistory_.erase(indexes_[row][col]);
             intersectionHistory_.insert(std::make_pair(indexes_[row][col], false));
             return false;
           }
         }
       }
       //this is the first time dealing with a tie
       else{
         //see if we can go down the row
         if(east){
           intersectionHistory_.insert(std::make_pair(indexes_[row][col], true));
           return true;
         }
         else{
           intersectionHistory_.insert(std::make_pair(indexes_[row][col], false));
           return false;
         }
       }
     }
     else if(eastTime < southTime){
     //check if we are at an egde
        if(east){
          return true;
        }
        //if we cannot choose a row we must choose a col
        else{
          return false;
        }
      }
      else{
      //check if we are at an edge
        if(south){
          return false;
        }
        //if we cannot choose
        return true;
       }
}

void StreetGrid::setBlockage(size_t row, size_t col, bool rowDir, bool val)
{
    // TO BE COMPLETED
    if(row >= n || col >= m || col < 0 || row < 0){
      throw std::logic_error("accessing an invalid row or col index");
    }
    //set the blockage
    if(val){
      if(!rowDir){
         //setting everything from the row down
        for(size_t i = row; i<n; i++){
          blockages_[i][col] = 1;
        }
      }
      else{
         //setting everything from the col down
        for(size_t i = col; i<m; i++){
          blockages_[row][i] = 1;
        }
      }
    }
    //unset the blockage
    else{
      //setting everything from the row down
      if(!rowDir){
        for(size_t i = row; i<n; i++){
          blockages_[i][col] = 0;
        }
      }
      else{
         //setting everything from the col down
        for(size_t i = col; i<m; i++){
          blockages_[row][i] = 0;
        }
      }
    }
}

EventList StreetGrid::processArrival(const std::string& vehicleID, const TimeStamp& ts)
{
    // TO BE COMPLETED
    std::map<std::string, Vehicle>::iterator i =  vehicles_.find(vehicleID);
    if(i == vehicles_.end()){
      throw std::logic_error("vehicle does not exist");
    }
    Event* e;
    std::vector<Event*> elist;

    //if we went down the row last
    if((i->second).rowDir == true){
      rowSeg_[(i->second).rowIndex][(i->second).colIndex]--;
      (i->second).colIndex++;
    }
    else{
      colSeg_[(i->second).rowIndex][(i->second).colIndex]--;
      (i->second).rowIndex++;
    }

    //check if at term location
    if((i->second).rowIndex == n-1 && (i->second).colIndex == m-1){
      (i->second).end += ts;
      completed_.push_back(i->second);
      return elist;
    }
    size_t t = 1;
    int rowTime = std::max(t, (1+getRowOccupancy((i->second).rowIndex, (i->second).colIndex)) / rowCapacities_[(i->second).rowIndex]) * SCALE_FACTOR;
    int colTime = std::max(t, (1+getColOccupancy((i->second).rowIndex, (i->second).colIndex)) / colCapacities_[(i->second).colIndex]) * SCALE_FACTOR;

    if(shouldChooseRow((i->second).rowIndex, (i->second).colIndex) == true){
      //go col
      if(isBlocked((i->second).rowIndex, (i->second).colIndex, true)){
        colSeg_[(i->second).rowIndex][(i->second).colIndex]++;
        (i->second).rowDir = false;
        e = new ArrivalEvent(ts + colTime, *this, vehicleID);
        elist.push_back(e);
      }
      //go row
      else{
        rowSeg_[(i->second).rowIndex][(i->second).colIndex]++;
        (i->second).rowDir = true;
        e = new ArrivalEvent(ts + rowTime, *this, vehicleID);
        elist.push_back(e);
      }
    }
    else{
      //go row
      if(isBlocked((i->second).rowIndex, (i->second).colIndex, false)){
        rowSeg_[(i->second).rowIndex][(i->second).colIndex]++;
        (i->second).rowDir = true;
        e = new ArrivalEvent(ts + rowTime, *this, vehicleID);
        elist.push_back(e);
      }
      //go col
      else{
        colSeg_[(i->second).rowIndex][(i->second).colIndex]++;
        (i->second).rowDir = false;
        e = new ArrivalEvent(ts + colTime, *this, vehicleID);
        elist.push_back(e);
      }
    }
    return elist;
}

EventList StreetGrid::addVehicle(const Vehicle& v)
{
    // TO BE COMPLETED
    std::vector<Event*> elist;
    Event* e;
    std::map<std::string, Vehicle>::iterator it = vehicles_.find(v.id);
    if(it != vehicles_.end()){
      throw std::logic_error("vehicle has already been added");
    }
    vehicles_.insert(std::make_pair(v.id, v));

    //see if we have reached terminal location
    if(v.colIndex == m-1 && v.rowIndex == n-1){
      completed_.push_back(v);
      return elist;
    }
    std::map<std::string, Vehicle>::iterator i = vehicles_.find(v.id);
    size_t t = 1;
    int rowTime = std::max(t, (1+getRowOccupancy(v.rowIndex, v.colIndex)) / rowCapacities_[v.rowIndex]) * SCALE_FACTOR;
    int colTime = std::max(t, (1+getColOccupancy(v.rowIndex, v.colIndex)) / colCapacities_[v.colIndex]) * SCALE_FACTOR;
    //if true then we go down the row;
    bool decision = shouldChooseRow(v.rowIndex, v.colIndex);

    if(decision){
      //if isblocked go south
      if(isBlocked(v.rowIndex, v.colIndex, true)){
        colSeg_[v.rowIndex][v.colIndex]++;
        (i->second).rowDir = false;
        e = new ArrivalEvent(v.start+colTime, *this, v.id);
        elist.push_back(e);
      }
      //go row
      else{
        rowSeg_[v.rowIndex][v.colIndex]++;
        (i->second).rowDir = true;
        e = new ArrivalEvent(v.start+rowTime, *this, v.id);
        elist.push_back(e);
      }
    }
    //going down col
    else{
      //go row
      if(isBlocked(v.rowIndex,v.colIndex, false)){
        rowSeg_[v.rowIndex][v.colIndex]++;
        (i->second).rowDir = true;
        e = new ArrivalEvent(v.start+rowTime, *this, v.id);
        elist.push_back(e);
      }
      //go col
      else{
        colSeg_[v.rowIndex][v.colIndex]++;
        (i->second).rowDir = false;
        e = new ArrivalEvent(v.start+colTime, *this, v.id);
        elist.push_back(e);
      }
    }

    return elist;
}
