/*Максим забрал у Саши телефон и захотел посмотреть его галерею.
Галерея была запоролена случайным числом с диапазоном 000000 - 999999,
Максим решил написать скрипт, который бы перебирал все возможные пин-коды.*/

#include <iostream>
int main()
{
    int amount_attempts = 3;
    int const real_key = 123456;
    int max_key = -1;
    std::cout << "Write the password to unlock the gallery:" << std::endl;
    while ((real_key != max_key) && (amount_attempts != 0))
    {
        std::cin >> max_key;
        amount_attempts--;
        if (real_key != max_key)
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
    std::cout << "Build Time: " << __TIME__ << '\n';
    return 0;
}