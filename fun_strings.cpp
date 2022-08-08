#include <iostream>

int main()
{
    std::string user_input;
    std::string end_result;

    std::cout << "Ievadi simbolus: \n";
    std::cin >> user_input;

    std::cout << "Manipulācija: \n";

    end_result = user_input.at(0);

    std::cout << end_result << "\n\n";

    for (auto &&i : user_input)
        std::cout << i << "\n";
    
    end_result.resize(user_input.length());
    
    for (int i = 0; i < user_input.length(); i++)
        end_result.at(i) = user_input.at(user_input.length() - 1 - i); // (- 1) to not include \0

    std::cout << "\nPuse: " << user_input.substr(0, user_input.length() / 2) << "\n"
            << "Otra Puse: " << user_input.substr(user_input.length() / 2, user_input.length()) << "\n"
            << "\nOtradi: " << end_result << "\n";

    return 0;
}