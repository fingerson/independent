#ifndef LISTS_H
#define LISTS_H

#define NULL __null

#include <iostream>
#include "ReturnList.h"

/* NODE CLASS DECLARATION */
template <class T>
class Node{
public:
        T hold;
        Node<T>* next_node;

        Node <T> ();
};

/* Node Constructor() */
template <class T>
Node<T>::Node(){
        hold = 0;
        next_node = NULL;
}

// LIST CLASS DECLARATION
template <class T>
class List : private Node <T>{

protected:
        Node <T>* first_node;

public:
// Constructors
        List();

// Deconstructor
        ~List();

// Operator overloads

        bool operator==(const List<T> &list_to_be_compared);

        bool operator!=(const List<T> &list_to_be_compared);

        bool operator>(const List<T> &list_to_be_compared);

        bool operator>=(const List<T> &list_to_be_compared);

        bool operator<(const List<T> &list_to_be_compared);

        bool operator<=(const List<T> &list_to_be_compared);

        void operator=(const List<T> &list_to_be_copied);

        void operator+=(const List<T> &list_to_be_appended);

        List<T> operator+(const List<T> &list_to_be_appended);


// T-type functions
        T foldl(T (*f)(T, T), T x);

        T foldr(T (*f)(T, T), T x);

        T value_at(int position);

        T value_at(int position) const;

// Bool-type functions
        bool contains(const List<T> &contained_list);

        bool has_elements();

// Int-type functions
        int length();

        int length() const;

// Void-type functions
        void append(T element);

        void append_at(int position, T element);

        void append_list(const List <T> &list_to_be_appended);

        void append_list_at(int position, const List <T> &list_to_be_appended);

        void assign_at(int position, T element);

        void assign_from_array(T assigner_array[], int array_size);

        void copy_list(const List<T> &list_to_be_copied);

        void delete_all();

        void delete_at(int position);

        void filter(bool (*f)(T));

        void map_on(T (*f)(T));

        void prune_at(int position);

        void prune_from_to(int prune_start, int prune_end);

        void switch_holds(int pos1, int pos2);
};

// -------------------------------------------------------------------
// List Constructor()
template <class T>
List<T>::List(){
        first_node = NULL;
}

// List Destructor
template <class T>
List<T>::~List(){
        delete_all();
}

// -------------------------------------------------------------------
// (NOT FROM LIST CLASS) Operator << Overload
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T> &list_to_be_outputed){
        for(int i = 0; i < list_to_be_outputed.length(); i++)
        {
                os << list_to_be_outputed.value_at(i);
        }
        return os;
}

// Operator == Overload
template <class T>
bool List<T>::operator==(const List<T> &list_to_be_compared){
        int this_length = this->length();
        if(this_length != list_to_be_compared.length())
        {
                return false;
        }
        else
        {
                bool is_equal = true;
                for(int i = 0; i < this_length && is_equal; i++)
                {
                        is_equal = (this->value_at(i) != list_to_be_compared.value_at(i));

                }
                return is_equal;
        }
}

template <class T>
bool List<T>::operator!=(const List<T> &list_to_be_compared){
        return !(*this == list_to_be_compared);
}

// Operator > Overload
template <class T>
bool List<T>::operator>(const List<T> &list_to_be_compared){
        return this->length() > list_to_be_compared.length();
}

// Operator >= Overload
template <class T>
bool List<T>::operator>=(const List<T> &list_to_be_compared){
        return this->length() >= list_to_be_compared.length();
}

// Operator < Overload
template <class T>
bool List<T>::operator<(const List<T> &list_to_be_compared){
        return this->length() < list_to_be_compared.length();
}

// Operator <= Overload
template <class T>
bool List<T>::operator<=(const List<T> &list_to_be_compared){
        return this->length() <= list_to_be_compared.length();
}

// Operator = Overload
template <class T>
void List<T>::operator=(const List<T> &list_to_be_copied){
        this->copy_list(list_to_be_copied);
}

// Operator += Overload
template <class T>
void List<T>::operator+=(const List<T> &list_to_be_appended){
        this->append_list(list_to_be_appended);
}

template <class T>
List<T> List<T>::operator+(const List<T> &list_to_be_appended){
        List<T> return_list;
        for(int i = 0; i < this->length(); i++)
        {
                return_list.append(this->value_at(i));
        }

        for(int i = 0; i < list_to_be_appended.length(); i++)
        {
                return_list.append(list_to_be_appended.value_at(i));
        }

        return return_list;
}
// --------------------------------------------------------------------
// foldl
template <class T>
T List<T>::foldl(T (*f)(T, T), T x){
        int i = length();
        if(i == 0)
        {
                return x;
        }
        T first_iteration = f(x, value_at(1));
        for(int j = 2; j < i; j++)
        {
                first_iteration = f(first_iteration, value_at(j));
        }
        return first_iteration;

}

// foldr
template <class T>
T List<T>::foldr(T (*f)(T, T), T x){
        int i = length() - 2;
        if(i == -2)
        {
                return x;
        }
        T first_iteration = f(value_at(i+1), x);
        for(; i >= 0; i--)
        {
                first_iteration = f(value_at(i), first_iteration);
        }
        return first_iteration;
}

// value_at
template <class T>
T List<T>::value_at(int position){
        if(first_node != NULL)
        {
                Node<T>* down_the_list = first_node;
                for(int i = 0; i < position && down_the_list->next_node != NULL; i++)
                {
                        down_the_list = down_the_list->next_node;
                }
                return down_the_list->hold;
        }
        return -1;
}

// value_at const
template <class T>
T List<T>::value_at(int position) const{
        if(first_node != NULL)
        {
                Node<T>* down_the_list = first_node;
                for(int i = 0; i < position && down_the_list->next_node != NULL; i++)
                {
                        down_the_list = down_the_list->next_node;
                }
                return down_the_list->hold;
        }
        return -1;
}

// --------------------------------------------------------------------
// contain
template <class T>
bool List<T>::contains(const List<T> &contained_list){
        int this_length = this->length();
        int contained_length = contained_list.length();
        bool contain = false;

        for(int i = 0; i <= this_length-contained_length && !contain; i++)
        {
                contain = true;
                for(int j = 0; j < contained_length && contain; j++)
                {
                        contain = (this->value_at(i+j) == contained_list.value_at(j));
                }
        }
        return contain;
}

// has_elements
template <class T>
bool List<T>::has_elements(){
        if(first_node == NULL)
        {
                return false;
        }
        else
        {
                return true;
        }
}

// --------------------------------------------------------------------
// length
template <class T>
int List<T>::length(){
        Node<T>* down_the_list = first_node;
        int counter = 0;
        while(down_the_list != NULL)
        {
                counter++;
                down_the_list = down_the_list->next_node;
        }
        return counter;
}

// length const
template <class T>
int List<T>::length() const{
        Node<T>* down_the_list = first_node;
        int counter = 0;
        while(down_the_list != NULL)
        {
                counter++;
                down_the_list = down_the_list->next_node;
        }
        return counter;
}

// --------------------------------------------------------------------
// append
template <class T>
void List<T>::append(T element){
        if(first_node != NULL)
        {
                Node<T>* down_the_list = first_node;
                Node<T>* before_down_the_list;
                int counter = 0;
                while(down_the_list != NULL)
                {
                        counter++;
                        before_down_the_list = down_the_list;
                        down_the_list = down_the_list->next_node;
                }
                Node<T> &last_element = *before_down_the_list;
                last_element.next_node = new Node <T>;
                (last_element.next_node)->hold = element;
                (last_element.next_node)->next_node = NULL;

        }
        else
        {
                first_node = new Node <T>;
                first_node->hold = element;
                first_node->next_node = NULL;
        }
}

// append_at
template <class T>
void List<T>::append_at(int position, T element){

        if(position == 0)
        {
                Node<T>* temporary_holder = first_node;
                first_node = new Node <T>;
                first_node->next_node = temporary_holder;
                first_node->hold = element;
        }
        else if(position > 0)
        {
                Node<T>* down_the_list = first_node;
                for(int i = 0; i < position-1 && (down_the_list->next_node != NULL); i++)
                {
                        down_the_list = down_the_list->next_node;
                }

                Node<T>* temporary_holder = down_the_list->next_node;
                down_the_list->next_node = new Node <T>;
                (down_the_list->next_node)->next_node = temporary_holder;
                (down_the_list->next_node)->hold = element;

        }
}

// append_list
template <class T>
void List<T>::append_list(const List <T> &list_to_be_appended){
        for(int i = 0; i < list_to_be_appended.length(); i++)
        {
                this->append(list_to_be_appended.value_at(i));
        }
}

// append_list_at
template <class T>
void List<T>::append_list_at(int position, const List <T> &list_to_be_appended){
        for(int i = 0; i < list_to_be_appended.length(); i++)
        {
                this->append_at(position + i, list_to_be_appended.value_at(i));
        }
}

// assign_at
template <class T>
void List<T>::assign_at(int position, T element){
        Node<T>* down_the_list = first_node;
        for(int i = 0; i < position && down_the_list != NULL; i++)
        {
                down_the_list = down_the_list->next_node;
        }
        if(down_the_list != NULL)
        {
                down_the_list->hold = element;
        }
}

// assign_from_array
template <class T>
void List<T>::assign_from_array(T assigner_array[], int array_size){
        this->delete_all();

        for(int i = 0; i < array_size; i++)
        {
                this->append(assigner_array[i]);
        }
}

// copy_list
template <class T>
void List<T>::copy_list(const List<T> &list_to_be_copied){
        // To avoid memory leaks;
        delete_all();
        int copied_length = list_to_be_copied.length();
        for(int i = 0; i < copied_length; i++)
        {
                append(list_to_be_copied.value_at(i));
        }
}

// delete_all
template <class T>
void List<T>::delete_all(){
        while(length() > 0)
        {
                delete_at(0);
        }
}

// delete_at
template <class T>
void List<T>::delete_at(int position){
        if(position == 0)
        {
                if(first_node != NULL)
                {
                        Node<T>* temporary_holder = first_node->next_node;
                        delete first_node;
                        first_node = temporary_holder;
                }
        }
        else if(position > 0)
        {
                Node<T>* before_down_the_list = NULL;
                Node<T>* down_the_list = first_node;
                for(int i = 0; i < position && down_the_list != NULL; i++)
                {
                        before_down_the_list = down_the_list;
                        down_the_list = down_the_list->next_node;
                }
                if(down_the_list != NULL)
                {
                        Node<T>* temporary_holder = down_the_list->next_node;
                        delete down_the_list;
                        before_down_the_list->next_node = temporary_holder;
                }
        }
}

// filter
template <class T>
void List<T>::filter(bool (*f)(T)){
        int number_of_elements = length();
        int analised_position = 0;
        for(int i = 0; i < number_of_elements; i++)
        {
                if(f(value_at(analised_position)))
                {
                        analised_position++;
                }
                else
                {
                        delete_at(analised_position);
                }
        }
}

// map_on
template <class T>
void List<T>::map_on(T (*f)(T)){
        for(int i = 0; i < length(); i++)
        {
                assign_at(i, f(value_at(i)));
        }
}

// prune_at
template <class T>
void List<T>::prune_at(int position){
        int prune_length = this->length();
        for(int i = position; i < prune_length; i++)
        {
                this->delete_at(position);
        }
}

// prune_from_to
template <class T>
void List<T>::prune_from_to(int prune_start, int prune_end){
       for(int i = prune_start; i <= prune_end; i++)
       {
                this->delete_at(prune_start);
       }
}

// switch_holds
template <class T>
void List<T>::switch_holds(int pos1, int pos2){
        if(pos1 != pos2)
        {
                int first_switch_pos = (pos1 > pos2) ? pos2 : pos1;
                int second_switch_pos = (pos1 < pos2) ? pos2 : pos1;
                bool first_switch_reached = false;
                bool second_switch_reached = false;
                T first_switch_value;
                Node<T>* first_switch_address;
                Node<T>* down_the_list = this->first_node;
                for(int i = 0;  down_the_list != NULL && !second_switch_reached; i++)
                {
                        if(first_switch_reached)
                        {
                                if(i == second_switch_pos)
                                {
                                        first_switch_address->hold = down_the_list->hold;
                                        down_the_list->hold = first_switch_value;
                                        second_switch_reached = true;
                                }

                        }
                        else
                        {
                                if(i == first_switch_pos)
                                {
                                        first_switch_address = down_the_list;
                                        first_switch_value = down_the_list->hold;
                                        first_switch_reached = true;
                                }
                        }

                        down_the_list = down_the_list->next_node;
                }
        }
}

#endif // LISTS_H
