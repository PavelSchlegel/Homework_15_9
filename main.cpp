#include "chat.hpp"

int main() {

    Chat chat;

    User Anton {"Anton"};
    User Apass {"Ghfdlf"};
    chat.reg(Anton, Apass);

    User Maria {"Maria"};
    User Mpass = {"123456789"};
    chat.reg(Maria, Mpass);
    
    std::cout << chat.login(Anton, Apass) << std::endl;

    chat.print_user();
    //chat.print_user_hash();
    chat.del_user(Maria);
    chat.print_user();

    return 0;
}