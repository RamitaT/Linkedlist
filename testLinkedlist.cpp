#include <iostream>
#include "linkedlist.h"
using namespace std;

int main()
{
    LinkedList mylst;
    cout << mylst;
    mylst.insert_beginning(4);
    mylst.insert_end(4);
    //mylst.insert_end(4);
    //mylst.insert_beginning(4);
    //cout << "enter number: ";
    cin >> mylst >> mylst >> mylst;
    cout << endl;
    cout << mylst << endl;
    ListNodePtr ptr;
    ptr = mylst.remove_value(6);
    //cout << mylst << endl;
    //mylst.sort_linkedlist();
    cout << mylst << endl;

    return 0;
}
