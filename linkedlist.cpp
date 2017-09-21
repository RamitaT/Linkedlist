#include <iostream>
#include <stdlib.h>
#include "linkedlist.h"
using namespace std;

LinkedList::LinkedList()
{
   front = NULL;
   back = NULL;
}

LinkedList::~LinkedList()
{

}

void LinkedList::set_position()
{
    ListNodePtr temp_ptr;
    temp_ptr = front;
    int i(1);
    temp_ptr->position = i;
    while(temp_ptr->next != NULL)
    {
        i++;
        temp_ptr = temp_ptr->next;
        temp_ptr->position = i;
    }
}

ListNodePtr LinkedList::copy_node(ListNodePtr ptr)
{
    ListNodePtr new_node = new ListNode;
    new_node->value = ptr->value;
    new_node->position = ptr->position;
    new_node->next = ptr->next;
    return new_node;
}

void LinkedList::swap(int& m, int& n)
{
    int temp;
    temp = m;
    m = n;
    n = temp;
}

void LinkedList::insert_beginning(int value)
{
    ListNodePtr temp_ptr = new ListNode;
    temp_ptr->value = value;
    temp_ptr->position = 1;
    temp_ptr->next = front;
    front = temp_ptr;
    if(front->next == NULL)
        back = front;
    set_position();
}

void LinkedList::insert_end(int value)
{
    if(front == NULL)
    {
        insert_beginning(value);
        return;
    }
    ListNodePtr temp_ptr = new ListNode;
    temp_ptr->value = value;
    if(front->next == NULL)
    {
        temp_ptr->position = 2;
        front->next = temp_ptr;
    }
    else
    {
        temp_ptr->position = back->position + 1;
        back->next = temp_ptr;
    }
    temp_ptr->next = NULL;
    back = temp_ptr;
}

ListNodePtr LinkedList::remove_value(int val)
{
    if(front == NULL)
        return NULL;
    ListNodePtr result, hold;
    ListNodePtr before_ptr, search_ptr;
    before_ptr = front;
    search_ptr = front->next;
    result = new ListNode;
    result->position = -1;
    if(search_ptr == NULL && before_ptr->value == val)
    {
        ListNodePtr discard_ptr;
        discard_ptr = before_ptr;
        front = NULL;
        back = front;
        result = copy_node(before_ptr);
        delete discard_ptr;
        return result;
    }
    else if(search_ptr == NULL && before_ptr->value != val)           //for the linkedlist with one node and doesnt have that value
        return NULL;
    while(search_ptr != NULL)
    {
        if(before_ptr->value == val)
        {
            ListNodePtr discard;
            discard = before_ptr;
            front = front->next;
            if(result->position == -1)
                {
                    hold = copy_node(before_ptr);
                    result = hold;
                }
            else if(result->position != -1)
                {
                    hold->next = copy_node(before_ptr);
                    hold = hold->next;
                }
            before_ptr = before_ptr->next;
            search_ptr = search_ptr->next;
            delete discard;
        }
        else if(search_ptr->value == val)
        {
            if(search_ptr == back)      //in case the target is located at the last node
            {
                if(result->position == -1)
                {
                    hold = copy_node(search_ptr);
                    result = hold;
                }
                else if(result->position != -1)
                {
                    hold->next = copy_node(search_ptr);
                    hold = hold->next;
                }
                back = before_ptr;
                back->next = NULL;
                delete search_ptr;
            }
            else
            {
                before_ptr->next = search_ptr->next;
                if(result->position == -1)
                {
                    hold = copy_node(search_ptr);
                    result = hold;
                }
                else if(result->position != -1)
                {
                    hold->next = copy_node(search_ptr);
                    hold = hold->next;
                }
                ListNodePtr discard;
                discard = search_ptr;
                search_ptr = search_ptr->next;
                delete discard;
            }
        }
        else
        {
            search_ptr = search_ptr->next;
            before_ptr = before_ptr->next;
        }
    }
    if(before_ptr != NULL && before_ptr->next == NULL && before_ptr->value == val)        //for all of them has the wanted length
    {
        ListNodePtr discard;
        discard = before_ptr;
        front = front->next;
        back = front;
        hold->next = copy_node(before_ptr);
        hold = hold->next;
        before_ptr = before_ptr->next;
        delete discard;
    }
    if(hold->next != NULL)
        hold->next = NULL;
    if(front != NULL)
        set_position();
    return result;
}

int LinkedList::removefront()
{
    if(front == NULL)
        return NULL;
    int value;
    value = front->value;
    ListNodePtr discard;
    discard = front;
    front = front->next;
    delete discard;
    if(front == NULL)
        return value;
    front->position = 1;
    set_position();
    return value;
}

bool LinkedList::empty()
{
    return (front == NULL);
}

void LinkedList::sort_linkedlist()
{
    if(front == NULL)
        return;
    int smallest;
    ListNodePtr hold_ptr, search_ptr, begin_ptr;
    begin_ptr = front;
    while(begin_ptr != NULL)
    {
        hold_ptr = begin_ptr;
        smallest = begin_ptr->value;
        search_ptr = begin_ptr->next;
        while(search_ptr != NULL)
        {
            if(search_ptr->value < smallest)
            {
                smallest = search_ptr->value;
                hold_ptr = search_ptr;
            }
            search_ptr = search_ptr->next;
        }
        if(hold_ptr->value == smallest)
            swap(begin_ptr->value,hold_ptr->value);
        begin_ptr = begin_ptr->next;
    }
}

ostream &operator<<(ostream & outs, LinkedList & lst)
{
    ListNodePtr temp_ptr;
    temp_ptr = lst.front;
    if(temp_ptr == NULL)
        outs << "this list is empty" << endl;           //Not sure about the output;
    while(temp_ptr != NULL)
    {
        outs << "<" << temp_ptr->position << ">" << "." << "<" << temp_ptr->value << ">" << endl;
        temp_ptr = temp_ptr->next;
    }
    return outs;
}

istream &operator>>(istream & in, LinkedList & lst)
{
    int hold;
    in >> hold;
    if(lst.front == NULL)
        lst.insert_beginning(hold);
    else
        lst.insert_end(hold);
    return in;
}
