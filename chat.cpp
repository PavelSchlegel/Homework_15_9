#include "chat.hpp"
#include "iostream"
#include "string.h"

char* Chat::array(User& login) noexcept {
    char* array = new char[login.size()];
    for (std::size_t i = 0; i < login.size(); ++i) {
        array[i] = login[i];
    }
    return array;
}

void Chat::del_user(User& user) {
    table->del(user);
}

Chat::Chat() {
    table = new HashTable();
}

Chat::~Chat() {
    delete table;
}

void Chat::reg(std::string& login, std::string& pass) {
    char* password = array(pass);
    uint* digest = sha1(password, pass.size());
    table->add(login, digest);
    delete [] password;
}

bool Chat::login(std::string& login, std::string& pass) {
    char* password = array(pass);
    uint* digest = sha1(password, pass.size());
    if (auto search = table->find(login)) {
        for (int j = 0; j < 5; ++j) {
            if (digest[j] != search[j]) {
                delete [] digest;
                delete [] password;
                return false;
            }
        }
        delete [] digest;
        delete [] password;
        return true;
    }
    delete [] digest;
    delete [] password;
    return false;
}

std::size_t Chat::get_user_count() noexcept {
    return table->get_count();
}

void Chat::print_user() {
    table->table_print();
}

void Chat::print_user_hash() {
    table->table_print_plus_SHA();
}