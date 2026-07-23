/*
Разработать программу для проверки различных свойств простых чисел
с обработкой исключительных ситуаций и оптимизацией вычислений.

Новые темы:
1) try-catch, throw
2) Алгоритм Решето Эратосфена
3) использование INT_MAX из <climits>, обработка переполнения
4) возврат std::vector из функции. Форматированный вывод элементов вектора

Функция bool is_prime(unsigned n) должна возвращать true, если число простое
    1) Если число < 2, генерировать исключение std::invalid_argument
    2) Оптимизация: проверка делителей только до √n

Поиск следующего простого числа (0.5 балла)

*Функция int next_prime(unsigned n) возвращает ближайшее простое число > n
    1) При переполнении (n > INT_MAX-100) возвращает исключение
    2) Должна использовать функцию is_prime

Проверка на числа-близнецы + поиск в диапазоне (2 балла)

*Функция bool is_twin_prime(unsigned n) возвращает true, если n и n+2 оба простые
    1) если n не простое, генерирует исключение

*Функция std::vector<int> primes_in_range(unsigned start, unsigned end) возвращает все простые числа в заданном диапазоне
    1) должна использовать решето Эратосфена
*/
#include <iostream>
#include <vector>
#include <climits>
#include <stdexcept>
#include <cmath>

bool is_prime(unsigned n)
{
    int max_number = INT_MAX;
    unsigned int amount_of_denominators = 0;
    unsigned int denom = 0;
    if (n < 2)
    {
        throw std::invalid_argument("Number must be more than 2");
    }

    if (n > max_number-18)
    {
        throw std::out_of_range("Too large number to process");
    }

    while (denom <= n)
    {
        denom++;
        unsigned int prime_result = n%denom;
        if (prime_result == 0)
        {
            amount_of_denominators++;
        }
    }

    if (amount_of_denominators == 2)
    {
        return true;
    }
    else
    {
        return false;
    }

    return 0;
}

int next_prime(unsigned n)
{
    bool result_is_prime = is_prime(n);
    if (result_is_prime = true)
    {
        unsigned int next_prime_number = n+1;
        while (is_prime(next_prime_number) != true)
        {
            next_prime_number++;
        }
        std::cout << "next prime: " << next_prime_number << '\n';
        return next_prime_number;
    }

    return 0;
}

bool is_twin_prime(unsigned n)
{
    if (is_prime(n) != true)
    {
        throw std::invalid_argument("Don't work with non-prime number");
    }

    return (is_prime(n) == true && is_prime(n+2) == true);
}

std::vector<int> primes_in_range(int start, int end)
{
    std::vector<int> prime_massive;
    while (start <= end)
    {

       int n = start+1;
       prime_massive.push_back(n);
    }

    return prime_massive;
}


int main()
{
    unsigned int number = 0;
    unsigned int start = 0;
    unsigned int end = 0;
    std::cout << "Enter the number: ";
    std::cin >> number;
    try
    {
        bool result_is_prime = is_prime(number);
        if (result_is_prime == true)
        {
            std::cout << number << " is prime\n";
        }
        next_prime(number);

        bool result_is_twin_prime = is_twin_prime(number);
        if (result_is_twin_prime == true)
        {
            std::cout << number << " and " << number+2 << " are twin primes\n";
        }

        std::cout << "enter a range of prime numbers: ";
        std::cin >> start >> end;
        std::vector<int> result_primes_in_range = primes_in_range(start, end);
        for(int prime_value : result_primes_in_range)
        {
            std::cout << prime_value << " ";
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Mistake: " << e.what() << '\n';
    }

    return 0;
}
