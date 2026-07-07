/*
После этого случая Саша поменял пин-код (а может и нет).
Максим пытается вспомнить предыдущий пин-код и найти новый.

Поместите свой скрипт в функцию.
Функция принимает 4 параметра: диапазон значений (начало и конец) и пин-код от галереи, script_key.
Функция возвращает вектор интов,
в котором одна запись - правильный пин-код.
Если функция успешно завершила работу, то доступ в галерею разрешается.
(запрещены лямбды)
На выходе (вне функции) вам нужно распарсить этот пин-код из вектора,
который вам вернула функция и сравнить с заранее известным
(правильным пин-кодом).
в мейне бегин-енд не надо. Чел вводит число и там уже проверка на валидность и передача в функцию
и функция возвращает вектор + в функции вернуть return 0 если не совпало или сообщение злое
а если совпало script==real делаем push.back() и возвращаем script_key.
В мейне внизу сразу пишем ты красава
*/

#include <iostream>
#include <vector>
#include <string>
std::vector<unsigned int> finding_password(unsigned int begin, unsigned int end, unsigned int real_key, unsigned int script_key)
{
    std::vector<unsigned int> script_massive;
        if(script_key == real_key)
        {
            script_massive.push_back(script_key);
        }
        else
        {
            std::cout << "You didn't guess ;)\n";
        }
    return script_massive;
};

int main()
{
    std::string script_key;
    unsigned int end;
    unsigned int begin;
    unsigned int const real_key = 999888;
    unsigned int amount_of_attempts = 3;
    bool found_password = 0;
    while (amount_of_attempts > 0 && found_password != true)
    {
        if (amount_of_attempts > 0 && found_password != true)
        {
            std::cout << "You have " << amount_of_attempts << " attempt(s) left.\n";
        }
        else
        {
            std::cout << "Sorry? not today...";
            break;
        }
        std::cout << "Input the script-key (6 digits): ";
        std::cin >> script_key;
        if (script_key.length() != 6)
        {
            std::cout << "Error: you didn't write 6 digits.\n";
            return 1;
        }
        for (char digits : script_key)
        {
            if (!std::isdigit(digits))
            {
                std::cout << "Error: string contains non-numeric characters.\n";
                return 1;
            }
        }

        unsigned int script_key_int = static_cast<unsigned int>(std::stoul(script_key));
        std::vector<unsigned int> result_script_massive = finding_password(begin, end, real_key, script_key_int);
        if (result_script_massive.empty())
        {
            std::cout << "Password haven't been found.\n";
            amount_of_attempts--;
        }
        else
        {
            std::cout << "Check the accuracy of your feelings:\n";
            for (int our_key : result_script_massive)
            {
                std::cout << "Your script key: " << our_key << " = " << real_key << " real key" << std::endl;
                std::cout << "Gallery is unlocked. Enjoy";
                found_password = true;
            }
        }
    }
    return 0;
}
