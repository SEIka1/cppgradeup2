/*
После этого случая Саша поменял пин-код (а может и нет).
Максим пытается вспомнить предыдущий пин-код и найти новый.

Поместите свой скрипт в функцию.
Функция принимает 3 параметра: диапазон значений (начало и конец) и пин-код от галереи.
Функция возвращает вектор интов,
в котором одна запись - правильный пин-код.
Если функция успешно завершила работу, то доступ в галерею разрешается.
(запрещены лямбды)
На выходе (вне функции) вам нужно распарсить этот пин-код из вектора,
который вам вернула функция и сравнить с заранее известным
(правильным пин-кодом).
*/

#include <iostream>
#include <vector>
#include <string>
std::vector<int> finding_password(unsigned int begin, unsigned int end, unsigned int real_key)
{
    std::vector<int> script_massive;
    for ( unsigned int script_key = end; script_key >= begin && script_key <= end; script_key--)
    {
        if(script_key == real_key)
        {
            script_massive.push_back(script_key);
            std::cout << "Gallery is unlocked. Enjoy";
            break;
        }
    }
    std::cout << '\n';
    return script_massive;
};

int main()
{
    std::string begin;
    std::string end;
    unsigned int const real_key = 999888;
    std::cout << "Input the begining of range (6 digits): ";
    std::cin >> begin;
    for (char digits : begin)
        {
            if (!std::isdigit(digits))
            {
                std::cout << "Error: string contains non-numeric characters." << std::endl;
                return 1;
            }
        }
    if (begin.length() != 6)
    {
        std::cout << "Error: you didn't write 6 digits." << std::endl;
        return 1;
    }

    std::cout << "Input the end of range (6 digits): ";
    std::cin >> end;
    for (char digits : end)
        {
            if (!std::isdigit(digits))
            {
                std::cout << "Error: string contains non-numeric characters." << std::endl;
                return 1;
            }
        }
    if (end.length() != 6)
    {
        std::cout << "Error: you didn't write 6 digits." << std::endl;
        return 1;
    }

    unsigned int begin_int = static_cast<unsigned int>(std::stoul(begin));
    unsigned int end_int = static_cast<unsigned int>(std::stoul(end));
     if(end_int < begin_int)
    {
        std::cout << "Error: begining must be less than end of out range." << std::endl;
        return 1;
    }

    std::vector<int> result_script_massive = finding_password(begin_int, end_int, real_key);
    if (result_script_massive.empty())
    {
        std::cout << "Password haven't been found." << "\n";
    }
    else
    {
        std::cout << "Check the accuracy of our function: " << '\n';
    }

    for (int our_key : result_script_massive)
    {
        if (our_key == real_key)
        {
            std::cout << "Our script key: " << our_key << " = " << real_key << " real key" << std::endl;
        }
        else
        {
            std::cout << "didn't find :-(";
        }
    }
    return 0;
}
