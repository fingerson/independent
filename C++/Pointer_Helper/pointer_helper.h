#ifndef POINTER_HELPER_H
#define POINTER_HELPER_H
#include <iostream>
#include "lists.h"

namespace{
        static List<void*>  addresses;
        static List<String> names;
}

void add_address(void* address_to_add, String sname);
void clean_addresses();
void print_name(void* address);
RString get_name(void* address);

inline void add_address(void* address_to_add, String sname){
        addresses.append(address_to_add);
        names.append(sname);
}

inline void clean_addresses(){
        names.delete_all();
        addresses.delete_all();
}

inline void print_name(void* address){
        int add_length = addresses.length();
        bool found = false;
        for(int i = 0; i < add_length; i++)
        {
                if(address == addresses.value_at(i)){
                        found = true;
                        std::cout << names[i] << std::endl;
                }
        }
        if(found == false)
        {
                std::cout << "Address not found" << std::endl;
        }
}

inline RString get_name(void* address){
        int add_length = addresses.length();
        for(int i = 0; i < add_length; i++)
        {
                if(address == addresses.value_at(i)){
                        RString ret_s;
                        ret_s = names[i];
                        return ret_s;
                }
        }
        RString ret_s = "";
        return ret_s;

}

#endif // POINTER_HELPER_H
