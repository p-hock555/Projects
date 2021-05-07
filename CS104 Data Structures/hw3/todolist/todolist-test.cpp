#include <iostream>
#include "todolist.h"
using namespace std;

void printPriorityList(const DailyTodoList& t)
{
    cout << "Priority items " << endl;
    for (size_t i = 0; i < t.numPriorityItems(); i++)
    {
        cout << t.getPriorityVal(i) << " ";
    }
    cout << endl;

}
void printDailyList(const DailyTodoList& t, size_t day)
{
    cout << "Items on day " << day << endl;
    size_t num = t.numItemsOnDay(day);
    for (size_t i = 0; i < num; i++)
    {
        cout << t.getNormalVal(day,i) << " ";
    }
    cout << endl;

}
int main()
{
    DailyTodoList t1;
    cout << "numDays = " << t1.numDays() << endl; //5
    cout << "numPriority = " << t1.numPriorityItems() << endl; //0
    cout << "numItemsOnDay 4 = " << t1.numItemsOnDay(4) << endl; //0
    t1.insert(6, 0, "6b", false);
    printDailyList(t1, 6);
    t1.push_back(6, "6c", true);
     printDailyList(t1, 6);
    t1.insert(6, 0, "6a", false);
     printDailyList(t1, 6);
     cout << "numItemsOnDay 6 = " << t1.numItemsOnDay(6) << endl; //3
    t1.insert(6, 3, "6d", false);//throw out of range
    t1.insert(2, 0, "2a", true);
    cout << "numItemsOnDay 2 = " << t1.numItemsOnDay(2) << endl; //1
    cout << "numPriority = " << t1.numPriorityItems() << endl; //2
    t1.insert(14, 0, "14a", true);
    cout << "numDays = " << t1.numDays() << endl; //28
    cout << "numPriority = " << t1.numPriorityItems() << endl; //3
    t1.push_back(30, "14a", true);
    cout << "numDays = " << t1.numDays() << endl; //60
    cout << "numDays = " << t1.numItemsOnDay(5) << endl; //0
    cout << "numPriority = " << t1.numPriorityItems() << endl; //4
    printDailyList(t1, 6);
    printPriorityList(t1);
    t1.remove(2, 0);
    cout << "numPriority = " << t1.numPriorityItems() << endl; //0
    printPriorityList(t1);
    t1.remove(14, 0);
    cout << "numPriority = " << t1.numPriorityItems() << endl; //0
    printPriorityList(t1);
    t1.remove(6, 2);
    printPriorityList(t1);
    cout << "numPriority = " << t1.numPriorityItems() << endl;
    printPriorityList(t1);
    return 0;
}
