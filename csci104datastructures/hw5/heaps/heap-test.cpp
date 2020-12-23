#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
#include "heap.h"
using namespace std;

int main()
{
    Heap<int> h(2);
    for(int i=20; i > 0; i--) {
        h.push(i);
    }
    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
    cout << endl;
    //
    // Heap<int> h2(3);
    // for(int i=20; i > 0; i++) {
    //     h2.push(i);
    // }
    // while(!h2.empty()) {
    //     cout << h2.top() << " ";
    //     h2.pop();
    // }
    // cout << endl;
    return 0;
}
