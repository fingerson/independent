#ifndef LISTS_H
#define LISTS_H

#define NULL __null

#include <iostream>
#include <stdexcept>

/* FORWARD DECLARATIONS */

// Classes

template <class T>
class RList;
template <class T>
class Node;
template <class T>
class List;
template <class T, class S>
class Tuple;

// Functions
template <class T>
std::ostream& operator<<(std::ostream& os, const RList<T> &list_to_be_outputed);

template <>
std::ostream& operator<<(std::ostream& os, const RList<char> &list_to_be_outputed);

template <class T, class S>
std::ostream& operator<<(std::ostream& os, const Tuple<T,S> &output_tuple);

template <class T>
T foldl(T (*f)(T, T), T x, const RList<T> &list_to_be_folded);

template <class T>
T foldr(T (*f)(T, T), T x, const RList<T> &list_to_be_folded);

template <class T>
T head(const RList<T> &list_to_be_headed);

template <class T>
RList<T> filter(bool (*f)(T), const RList<T> &list_to_be_filtered);

template <class T>
RList<T> init(const RList<T> &list_to_be_inited);

template <class T>
RList<T> map_on(T (*f)(T), const RList<T> &list_to_be_mapped);

template <class T>
RList<T> reverse_list(const RList<T> list_to_be_reversed);

template <class T, class S>
RList< Tuple<T,S> > zip(const RList<T> &list_1, const RList<S> &list_2);

// --------------------------------------------------------------------
/* CLASS DECLARATIONS */

// RList
template <class T>
class RList{

private:
        // Node
        template <typename S>
        class Node{
        public:
                S hold;
                Node<S>* next_node;

                // Node Constructor
                Node(){
                        hold = S();
                        next_node = NULL;
                }

                // Node Destructor
                ~Node(){
                        hold = S();
                        next_node = NULL;
                }

        };

protected:
        Node <T>* first_node;

public:
// Constructors
        RList();

// Operator overloads

        virtual T& operator[](int i);

        virtual bool operator==(const RList<T> &list_to_be_compared);

        virtual bool operator!=(const RList<T> &list_to_be_compared);

        virtual bool operator>(const RList<T> &list_to_be_compared);

        virtual bool operator>=(const RList<T> &list_to_be_compared);

        virtual bool operator<(const RList<T> &list_to_be_compared);

        virtual bool operator<=(const RList<T> &list_to_be_compared);

        virtual void operator=(const RList<T> &list_to_be_copied);

        virtual void operator+=(const RList<T> &list_to_be_appended);

        virtual void operator+=(T element);

        virtual RList<T> operator+(const RList<T> &list_to_be_appended);

        virtual RList<T> operator+(T element);

// Node<T>* type functions
        virtual Node<T>* first_address() const;

// T-type functions
        virtual T peek();

        virtual T peek() const;

        virtual T pop();

        virtual T value_at(int position);

        virtual T value_at(int position) const;

// Bool-type functions
        virtual bool contains(const RList<T> &contained_list);

        virtual bool has_elements();

        virtual bool has_elements() const;

// Int-type functions
        virtual int length();

        virtual int length() const;

// Void-type functions
        virtual void append(T element);

        virtual void append_at(int position, T element);

        virtual void append_list(const RList <T> &list_to_be_appended);

        virtual void append_list_at(int position, const RList <T> &list_to_be_appended);

        virtual void assign_at(int position, T element);

        virtual void assign_from_array(T assigner_array[], int array_size);

        // virtual void assign_from_array(char assigner_array[]); DEPRECATED

        virtual void copy_list(const RList<T> &list_to_be_copied);

        virtual void delete_all();

        virtual void delete_at(int position);

        virtual void prune_at(int position);

        virtual void prune_from_to(int prune_start, int prune_end);

        virtual void push(T element);

        virtual void switch_holds(int pos1, int pos2);
};

// List
template <class T>
class List : public RList<T>{
public:

        ~List();

        bool operator==(const List<T> &list_to_be_compared);

        bool operator!=(const List<T> &list_to_be_compared);

        bool operator>(const List<T> &list_to_be_compared);

        bool operator>=(const List<T> &list_to_be_compared);

        bool operator<(const List<T> &list_to_be_compared);

        bool operator<=(const List<T> &list_to_be_compared);

        void operator=(const List<T> &list_to_be_copied);

        void operator=(const RList<T> &list_to_be_copied);

        void operator+=(const List<T> &list_to_be_appended);

        void operator+=(T element);

        RList<T> operator+(const List<T> &list_to_be_appended);

        RList<T> operator+(T element);
};

// Tuple
template <class T, class S>
class Tuple{
private:
        T left_elem;
        S right_elem;

public:

// Constructors
        Tuple();

        Tuple(T left, S right);

// Operators
        bool operator==(const Tuple<T,S> &compare_tuple);
        bool operator!=(const Tuple<T,S> &compare_tuple);

        void operator=(const Tuple<T,S> &assign_tuple);

// T and S functions

        T left();

        T left() const;

        S right();

        S right() const;


};

// --------------------------------------------------------------------

/*RLIST FUNCTIONS*/
// RList Constructor()
template <class T>
RList<T>::RList(){
        first_node = NULL;
}

// --------------------------------------------------------------------

// Operator [] Overload
template <class T>
T& RList<T>::operator[](int i){
        if(i < 0)
        {
                throw std::out_of_range("ERROR: Access request to out of range node.\n");
        }
        else if(this->first_node == NULL)
        {
                this->append(T());
        }

        Node<T>* down_the_list = this->first_node;
        int j;
        T null_append = T();
        for(j = 0; j < i; j++)
        {
                if(down_the_list->next_node == NULL)
                {
                        this->append(null_append);
                }
                down_the_list = down_the_list->next_node;
        }

        return down_the_list->hold;
}

// Operator == Overload
template <class T>
bool RList<T>::operator==(const RList<T> &list_to_be_compared){
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

// Operator != Overload
template <class T>
bool RList<T>::operator!=(const RList<T> &list_to_be_compared){
        return !(*this == list_to_be_compared);
}

// Operator > Overload
template <class T>
bool RList<T>::operator>(const RList<T> &list_to_be_compared){
        return this->length() > list_to_be_compared.length();
}

// Operator >= Overload
template <class T>
bool RList<T>::operator>=(const RList<T> &list_to_be_compared){
        return this->length() >= list_to_be_compared.length();
}

// Operator < Overload
template <class T>
bool RList<T>::operator<(const RList<T> &list_to_be_compared){
        return this->length() < list_to_be_compared.length();
}

// Operator <= Overload
template <class T>
bool RList<T>::operator<=(const RList<T> &list_to_be_compared){
        return this->length() <= list_to_be_compared.length();
}

// Operator = Overload
template <class T>
void RList<T>::operator=(const RList<T> &list_to_be_copied){
        this->copy_list(list_to_be_copied);
}

// Operator += Overload
template <class T>
void RList<T>::operator+=(const RList<T> &list_to_be_appended){
        this->append_list(list_to_be_appended);
}

// Operator += Overload for single elements
template <class T>
void RList<T>::operator+=(T element){
        this->append(element);
}

// Operator + Overload
template <class T>
RList<T> RList<T>::operator+(const RList<T> &list_to_be_appended){
        RList<T> return_list;
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

// Operator + Overload for single elements
template <class T>
RList<T> List<T>::operator+(T element){
        RList<T> return_list;
        for(int i = 0; i < this->length(); i++)
        {
                return_list.append(this->value_at(i));
        }
        return_list.append(element);

        return return_list;
}

// --------------------------------------------------------------------

template <class T>
RList<T>::Node<T>* RList<T>::first_address() const{
        return this->first_node;
}

// --------------------------------------------------------------------

// peek
template <class T>
T RList<T>::peek(){
        int this_length = this->length();
        if(this_length == 0)
        {
                throw std::domain_error("ERROR: Peek is not defined for empty lists.\n");
        }
        else
        {
                return this->value_at(this_length-1);
        }
}

// peek
template <class T>
T RList<T>::peek() const{
        int this_length = this->length();
        if(this_length == 0)
        {
                throw std::domain_error("ERROR: Peek is not defined for empty lists.\n");
        }
        else
        {
                return this->value_at(this_length-1);
        }
}

// pop
template <class T>
T RList<T>::pop(){
        int this_length = this->length();
        if(this_length == 0)
        {
                throw std::domain_error("ERROR: Cannot pop an empty list.\n");
        }
        else
        {
                T return_value = this->value_at(this_length-1);
                this->delete_at(this_length-1);
                return return_value;
        }
}

// value_at
template <class T>
T RList<T>::value_at(int position){
        if(first_node != NULL)
        {
                Node<T>* down_the_list = first_node;
                int i; // i declared out of the for loop to check errors
                for(i = 0; i < position && down_the_list->next_node != NULL; i++)
                {
                        down_the_list = down_the_list->next_node;
                }

                if(i < position && (down_the_list->next_node == NULL))
                {
                        throw std::out_of_range("ERROR: Access request to out of range node.\n");
                }

                return down_the_list->hold;
        }
        else
        {
                throw std::out_of_range("ERROR: Access request to out of range node.\n");
        }
}

// value_at const
template <class T>
T RList<T>::value_at(int position) const{
        if(first_node != NULL)
        {
                Node<T>* down_the_list = first_node;
                int i; // i declared out of the for loop to check errors
                for(i = 0; i < position && down_the_list->next_node != NULL; i++)
                {
                        down_the_list = down_the_list->next_node;
                }

                if(i < position && (down_the_list->next_node == NULL))
                {
                        throw std::out_of_range("ERROR: Access request to out of range node.\n");
                }

                return down_the_list->hold;
        }
        else
        {
                throw std::out_of_range("ERROR: Access request to out of range node.\n");
        }
}

// --------------------------------------------------------------------
// contain
template <class T>
bool RList<T>::contains(const RList<T> &contained_list){
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
bool RList<T>::has_elements(){
        if(first_node == NULL)
        {
                return false;
        }
        else
        {
                return true;
        }
}

// has_elements const
template <class T>
bool RList<T>::has_elements() const{
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
int RList<T>::length(){
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
int RList<T>::length() const{
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
void RList<T>::append(T element){
        try
        {
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
        catch(std::bad_alloc())
        {
                std::cout << "ERROR: Failure to allocate dinamic memory, trying again..." << std::endl;
                this->append(element);
        }
}

// append_at
template <class T>
void RList<T>::append_at(int position, T element){

        try
        {
                if(position == 0)
                {
                        Node<T>* temporary_holder = this->first_node;
                        first_node = new Node <T>;
                        first_node->next_node = temporary_holder;
                        first_node->hold = element;
                }
                else if(position > 0)
                {
                        Node<T>* down_the_list = this->first_node;
                        int i; // i declared outside of loop to catch exceptions
                        for(i = 0; i < position-1 && (down_the_list->next_node != NULL); i++)
                        {
                                down_the_list = down_the_list->next_node;
                        }

                        if(i < position-1 && down_the_list->next_node == NULL)
                        {
                                throw std::out_of_range("ERROR: Append request at out of range position.\n");
                        }

                        Node<T>* temporary_holder = down_the_list->next_node;
                        down_the_list->next_node = new Node <T>;
                        (down_the_list->next_node)->next_node = temporary_holder;
                        (down_the_list->next_node)->hold = element;

                }
                else
                {
                        throw std::out_of_range("ERROR: Append request at out of range position.\n");
                }
        }
        catch(std::bad_alloc())
        {
                std::cout << "ERROR: Failure to allocate dinamic memory, trying again..." << std::endl;
                this->append_at(position, element);
        }
}

// append_list
template <class T>
void RList<T>::append_list(const RList <T> &list_to_be_appended){
        for(int i = 0; i < list_to_be_appended.length(); i++)
        {
                this->append(list_to_be_appended.value_at(i));
        }
}

// append_list_at
template <class T>
void RList<T>::append_list_at(int position, const RList <T> &list_to_be_appended){
        for(int i = 0; i < list_to_be_appended.length(); i++)
        {
                this->append_at(position + i, list_to_be_appended.value_at(i));
        }
}

// assign_at
template <class T>
void RList<T>::assign_at(int position, T element){
        Node<T>* down_the_list = this->first_node;
        for(int i = 0; i < position && down_the_list != NULL; i++)
        {
                down_the_list = down_the_list->next_node;
        }
        if(down_the_list != NULL)
        {
                down_the_list->hold = element;
        }
        else
        {
                throw std::out_of_range("ERROR: Assign request at out of range node.\n");
        }
}

// assign_from_array
template <class T>
void RList<T>::assign_from_array(T assigner_array[], int array_size){
        this->delete_all();

        for(int i = 0; i < array_size; i++)
        {
                this->append(assigner_array[i]);
        }
}

/* DEPRECATED
// assign_from_array for char arrays
template <>
void RList<char>::assign_from_array(char assigner_array[]){
        int i = 0;
        do
        {
                this->append(assigner_array[i]);
                i++;
        }while (assigner_array[i] != '\0');
}
*/

// copy_list
template <class T>
void RList<T>::copy_list(const RList<T> &list_to_be_copied){
        // To avoid memory leaks;
        this->delete_all();
        int copied_length = list_to_be_copied.length();
        for(int i = 0; i < copied_length; i++)
        {
                this->append(list_to_be_copied.value_at(i));
        }
}

// delete_all
template <class T>
void RList<T>::delete_all(){
        while(length() > 0)
        {
                delete_at(0);
        }
}

// delete_at
template <class T>
void RList<T>::delete_at(int position){
        if(position == 0)
        {
                if(first_node != NULL)
                {
                        Node<T>* temporary_holder = first_node->next_node;
                        delete this->first_node;
                        first_node = temporary_holder;
                }
                else
                {
                        throw std::out_of_range("ERROR: Deletion request at out of range node.\n");
                }
        }
        else if(position > 0)
        {
                Node<T>* before_down_the_list = NULL;
                Node<T>* down_the_list = this->first_node;
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
                else
                {
                        throw std::out_of_range("ERROR: Deletion request at out of range node.\n");
                }
        }
        else
        {
                throw std::out_of_range("ERROR: Deletion request at out of range node.\n");
        }
}

// prune_at
template <class T>
void RList<T>::prune_at(int position){
        int prune_length = this->length();
        for(int i = position; i < prune_length; i++)
        {
                this->delete_at(position);
        }
}

// prune_from_to
template <class T>
void RList<T>::prune_from_to(int prune_start, int prune_end){
       for(int i = prune_start; i <= prune_end; i++)
       {
                this->delete_at(prune_start);
       }
}

// push
template <class T>
void RList<T>::push(T element){
        this->append(element);
}

// switch_holds
template <class T>
void RList<T>::switch_holds(int pos1, int pos2){
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
                if(!second_switch_reached)
                {
                        throw std::out_of_range("ERROR: Switch request to at least one out of range node.\n");
                }
        }
}

// --------------------------------------------------------------------
/* LIST CLASS FUNCTIONS */

// List Class Operators

// List Destructor
template <class T>
List<T>::~List(){
        RList<T>::delete_all();
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

// Operator != Overload
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

// Operator = Overload for RList assignments
template <class T>
void List<T>::operator=(const RList<T> &list_to_be_copied){
        this->first_node = list_to_be_copied.first_address();
}

// Operator += Overload
template <class T>
void List<T>::operator+=(const List<T> &list_to_be_appended){
        this->append_list(list_to_be_appended);
}

// Operator += Overload for single elements
template <class T>
void List<T>::operator+=(T element){
        this->append(element);
}

// Operator + Overload
template <class T>
RList<T> List<T>::operator+(const List<T> &list_to_be_appended){
        RList<T> return_list;
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

// Operator + Overload for single elements
template <class T>
RList<T> RList<T>::operator+(T element){
        RList<T> return_list;
        for(int i = 0; i < this->length(); i++)
        {
                return_list.append(this->value_at(i));
        }
        return_list.append(element);

        return return_list;
}

// --------------------------------------------------------------------
/* TUPLE CLASS FUNCTIONS */

// Tuple Constructor()
template <class T, class S>
Tuple<T,S>::Tuple(){
        right_elem = S();
        left_elem  = T();
}

// Tuple Constructor (T,S)
template <class T, class S>
Tuple<T,S>::Tuple(T left, S right){
        right_elem = right;
        left_elem = left;
}

// --------------------------------------------------------------------

template <class T, class S>
bool Tuple<T,S>::operator==(const Tuple<T,S> &compare_tuple){
        if(this->left_elem == compare_tuple.left())
        {
               if(this->right_elem == compare_tuple.right)
               {
                       return true;
               }
               else
               {
                       return false;
               }
        }
        else
        {
                return false;
        }
}

template <class T, class S>
bool Tuple<T,S>::operator!=(const Tuple<T,S> &compare_tuple){
        return !(*this == compare_tuple);
}

template <class T, class S>
void Tuple<T,S>::operator=(const Tuple<T,S> &assign_tuple){
        this->left_elem = assign_tuple.left();
        this->right_elem = assign_tuple.right();
}

// --------------------------------------------------------------------

// left
template <class T, class S>
T Tuple<T,S>::left(){
        return left_elem;
}

// left const
template <class T, class S>
T Tuple<T,S>::left() const {
        return left_elem;
}

// right
template <class T, class S>
S Tuple<T,S>::right(){
        return right_elem;
}

// right const
template <class T, class S>
S Tuple<T,S>::right() const{
        return right_elem;
}

// --------------------------------------------------------------------
/* FUNCTIONS OUTSIDE OF CLASSES */

// Operator << Overload for RLists
template <class T>
std::ostream& operator<<(std::ostream& os, const RList<T> &list_to_be_outputed){
        std::cout << "[";
        int list_length = list_to_be_outputed.length();
        for(int i = 0; i < list_length-1; i++)
        {
                os << list_to_be_outputed.value_at(i);
                os << ",";
        }
        if(list_length != 0)
        {
                os << list_to_be_outputed.value_at(list_length - 1);
        }
        os << "]";
        return os;
}

// Operator << Overload for RLists char specialization
template <>
std::ostream& operator<<(std::ostream& os, const RList<char> &list_to_be_outputed){
        int list_length = list_to_be_outputed.length();
        for(int i = 0; i < list_length; i++)
        {
                os << list_to_be_outputed.value_at(i);
        }
        return os;
}

// Operator << Overload for Tuples
template <class T, class S>
std::ostream& operator<<(std::ostream& os, const Tuple<T,S> &output_tuple){
        os << "(";
        os << output_tuple.left();
        os << ",";
        os << output_tuple.right();
        os << ")";
        return os;
}

// --------------------------------------------------------------------
// foldl
template <class T>
T foldl(T (*f)(T, T), T x, const RList<T> &list_to_be_folded){
        int i = list_to_be_folded.length();
        if(i == 0)
        {
                return x;
        }
        T first_iteration = f(x, list_to_be_folded.value_at(1));
        for(int j = 2; j < i; j++)
        {
                first_iteration = f(first_iteration, list_to_be_folded.value_at(j));
        }
        return first_iteration;

}

// foldr
template <class T>
T foldr(T (*f)(T, T), T x, const RList<T> &list_to_be_folded){
        int i = list_to_be_folded.length() - 2;
        if(i == -2)
        {
                return x;
        }
        T first_iteration = f(list_to_be_folded.value_at(i+1), x);
        for(; i >= 0; i--)
        {
                first_iteration = f(list_to_be_folded.value_at(i), first_iteration);
        }
        return first_iteration;
}

// head
template <class T>
T head(const RList<T> &list_to_be_headed){
        if(list_to_be_headed.has_elements())
        {
                return list_to_be_headed.value_at(0);
        }
        else
        {
                throw std::domain_error("ERROR: Head not defined for empty lists.\n");
        }
}

// --------------------------------------------------------------------

// filter
template <class T>
RList<T> filter(bool (*f)(T), const RList<T> &list_to_be_filtered){
        RList<T> return_list;
        int number_of_elements = list_to_be_filtered.length();
        for(int i = 0; i < number_of_elements; i++)
        {
                if(f(list_to_be_filtered.value_at(i)))
                {
                        return_list.append(list_to_be_filtered.value_at(i));
                }
        }
        return return_list;
}

// init
template <class T>
RList<T> init(const RList<T> &list_to_be_inited){
        RList<T> return_list;
        return_list = list_to_be_inited;
        return_list.delete_at(return_list.length() - 1);
        return return_list;
}

// map_on
template <class T>
RList<T> map_on(T (*f)(T), const RList<T> &list_to_be_mapped){
        RList<T> return_list;
        for(int i = 0; i < list_to_be_mapped.length(); i++)
        {
                return_list.append(f(list_to_be_mapped.value_at(i)));
        }
        return return_list;
}

// reverse_list
template <class T>
RList<T> reverse_list(const RList<T> list_to_be_reversed){
        RList<T> return_list;
        int list_length = list_to_be_reversed.length();
        for(int i = 0; i < list_length; i++)
        {
                return_list.append(list_to_be_reversed.value_at(list_length -1 -i));
        }
        return return_list;
}

// tail
template <class T>
RList<T> tail(const RList<T> &list_to_be_tailed){
        if(list_to_be_tailed.has_elements())
        {
                RList<T> return_list;
                return_list = list_to_be_tailed;
                return_list.delete_at(0);
                return return_list;
        }
        else
        {
                throw std::domain_error("ERROR: Tail is not defined for empty lists.\n");
        }
}

// zip
template <class T, class S>
RList< Tuple<T,S> > zip(const RList<T> &list_1, const RList<S> &list_2){
        RList< Tuple<T,S> > return_list;
        Tuple<T,S> return_tuple;

        int list_length = int();
        {
                int length1 = list_1.length();
                int length2 = list_2.length();
                list_length = length1 < length2 ? length1 : length2;
        }

        for(int i = 0; i < list_length; i++){
                return_tuple = Tuple<T,S>(list_1.value_at(i), list_2.value_at(i));
                return_list.append(return_tuple);
        }

        return return_list;
}

#endif // LISTS_H
