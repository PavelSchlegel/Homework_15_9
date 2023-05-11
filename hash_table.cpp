#include "hash_table.hpp"
#include <exception>

void HashTable::resize() noexcept {
    Pair* old_array = array;
    std::size_t old_size = mem_size;
    user_count = 0;
    mem_size *= 2;
    array = nullptr;
    while (!array) {
        array = new(std::nothrow) Pair[mem_size];
        if (array) {
            for (std::size_t i = 0; i < old_size; ++i) {
                if (old_array[i].status == enPairStatus::engaged) {
                    std::size_t index = hash_func(old_array[i].user_name, i);
                    add(old_array[i].user_name, old_array[i].sha_hash);
                }
            }
            delete [] old_array;
        }
    }
}

void HashTable::del(User& _name) noexcept {
    // Ваш код
    for (int i = 0; i < mem_size; ++i) {
        int index = hash_func(_name, i);
        if (array[index].status == enPairStatus::engaged) {
            if (array[index].user_name == _name) {
                array[index].status = enPairStatus::deleted;
                delete [] array[index].sha_hash;
                array[index].sha_hash = nullptr;
                user_count--;
                break;
            }
        }
    }
}

uint* HashTable::find(User& _name) { 
    for (int i = 0; i < mem_size; ++i) {
        int index = hash_func(_name, i);
        if (array[index].status == enPairStatus::engaged) {
            if (array[index].user_name == _name) {
                return array[index].sha_hash;
            }
        }    
    }
    throw std::runtime_error("User not fund!");
}

void HashTable::add(User _name, uint* digest) {
    int index = -1, i = 0;

    for(;i < mem_size; i++) {
        index = hash_func(_name, i);
        if(array[index].status != enPairStatus::engaged) { 
            break;
        }
    }
    if(i >= mem_size){
        resize();
        add(_name, digest);
        return;
    }
    
    array[index].user_name = _name;
    array[index].status = engaged;
    array[index].sha_hash = digest;
    user_count++;
}

std::size_t HashTable::hash_func(User _name, std::size_t offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for(; i<_name.size(); i++) {
        sum += _name[i];
    }
    // линейные пробы
    return (sum % mem_size + offset) % mem_size; 
}

const std::size_t HashTable::get_count() noexcept {
    return user_count;
}


void HashTable::table_print() noexcept {
    for (std::size_t i = 0; i < mem_size; ++i) {
        if (array[i].status == engaged) {
            std::cout << array[i].user_name << '\n';
        }
    }
}

void HashTable::table_print_plus_SHA() noexcept {
    for (std::size_t i = 0; i < mem_size; ++i) {
        if (array[i].status == engaged) {
            std::cout << array[i].user_name << '\n';
            for (int j = 0; j < 5; ++j) {
                std::cout << array[i].sha_hash[j] << '\n';
            }
        }
    }
}


HashTable::HashTable() {
    user_count = 0;
    mem_size = 8;
    array = new Pair [mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}