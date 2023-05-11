#ifndef HASH_TABLE
#define HASH_TABLE

#include <string.h>
#include <iostream>
#include "sha1.hpp"

typedef std::string User;

class HashTable {
    public:
    
        HashTable();
        ~HashTable();
        void add(User _name , uint* digest);
        void table_print() noexcept;
        void del(User& _name) noexcept;
        uint* find(User& _name);
        const std::size_t get_count() noexcept;
        void table_print_plus_SHA() noexcept;

    private:
    
        enum enPairStatus {
            free,
            engaged,
            deleted
        };
    
        struct Pair {
            
            Pair()
            : user_name("")
            , sha_hash(nullptr)
            , status(enPairStatus::free) {

            }

            Pair(User _name, uint* digest)
            : status(enPairStatus::engaged) 
            , user_name(_name)
            , sha_hash(digest) {
            
            }

            ~Pair() {
                if (sha_hash) {
                    delete [] sha_hash;
                }
            }

            Pair& operator = (const Pair& other) = delete;
            
            User user_name;
            uint* sha_hash;
            enPairStatus status;
        };

        void resize() noexcept;
        std::size_t hash_func(User _name, std::size_t offset);
        
        Pair* array;
        std::size_t mem_size;
        std::size_t user_count;
};
#endif