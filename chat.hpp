#ifndef CHAT
#define CHAT

#include "sha1.hpp"
#include "hash_table.hpp"
#include <string>


class Chat {
    public:

        Chat();
        ~Chat();
        void reg(User& login, User& pass);
        bool login(User& login, User& pass);
        std::size_t get_user_count() noexcept;
        void print_user();
        void print_user_hash();
        void del_user(User& user);

    private:

        char* array(User& login) noexcept;
        HashTable* table;
};
#endif