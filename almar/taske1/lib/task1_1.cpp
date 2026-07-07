/*Максим забрал у Саши телефон и захотел посмотреть его галерею.
Галерея была запоролена случайным числом с диапазоном 000000 - 999999,
Максим решил написать скрипт, который бы перебирал все возможные пин-коды.*/

#include <iostream>
int main()
{
    int amount_attempts = 3;
    int const real_key = 123456;
    unsigned int input_key = 1000000;
    std::cout << "Write the password (a six-digit code) to unlock the gallery:" << std::endl;
    while ((real_key != input_key) && (amount_attempts != 0))
    {
        std::cin >> input_key;
        if (input_key < 0 || input_key > 999999)
        {
            std::cout << "Invalid passkey. The passkey should contain 6 digits";
            return 0;
        }
        else
        {
            amount_attempts--;
            if (real_key != input_key)
            {
                if (amount_attempts == 0)
                {
                    std::cout << "Gallery is locked.";
                }
                else
                {
                std::cout << "You have only "<< amount_attempts <<" attempts"  << std::endl;
                }
            }
            else
            {
                std::cout << "Gallery is unlocked. Enjoy." << std::endl;
            }
    }
    }
    return 0;
}