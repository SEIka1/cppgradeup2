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
#include <algorithm>

bool is_prime(unsigned n)
{
    unsigned int amount_of_denominators = 0;
    unsigned int denom = 2;
    if (n < 2)
    {
        throw std::invalid_argument("Number must be at least 2");
    }

    if (n > INT_MAX - 18)
    {
        throw std::out_of_range("Too large number to process");
    }

    unsigned int limit_n = std::sqrt(n);
    while (denom <= limit_n)
    {
        if (n % denom == 0)
        {
            return false;
        }
    }
    return true;
}

int next_prime(unsigned n)
{
    if (n > INT_MAX - 18)
    {
        throw std::out_of_range("Number is too close to INT_MAX");
    }
    if (n == 2)
    {
        return 3;
    }
    unsigned next_number = n;
    if (n % 2 == 0)
    {
        next_number += 1;
    }
    else
    {
        next_number += 2;
    }
    while (next_number <= INT_MAX)
    {
        if (is_prime(next_number))
        {
            return next_number;
        }
        else
        {
            next_number += 2;
        }
    }
    throw std::out_of_range("No next prime number for this...sorry..");
}

bool is_twin_prime(unsigned n)
{
    if (n > INT_MAX - 18)
    {
        throw std::out_of_range("Number is too large to proceed");
    }
    if (!is_prime(n))
    {
        throw std::invalid_argument("is_twin_prime function doesn't work with non-prime number");
    }
    return (is_prime(n+2));
}

std::vector<int> primes_in_range(unsigned start, unsigned end)
{
    if (end < 2 || start > end)
    {
        return {};
    }
    std::vector<bool> is_prime(end + 1, true);
    is_prime[0] = is_prime[1] = false;
    unsigned limit_of_filtration = std::sqrt(end);
    for (unsigned denom_eratosphene = 2; denom_eratosphene <= limit_of_filtration; ++denom_eratosphene)
    {
        if (is_prime[denom_eratosphene])
        {
            unsigned start_multiplicity = std::max(denom_eratosphene * denom_eratosphene, ((start + denom_eratosphene - 1) / denom_eratosphene) * denom_eratosphene);
            for (unsigned i = start_multiplicity; i <= end; i += denom_eratosphene)
            {
                is_prime[i] = false;
            }
        }
    }

    std::vector<int> prime_massive;
    unsigned true_start = std::max(start, 2u);
    for (unsigned i = true_start; i <= end; ++i)
    {
        if (is_prime[i])
        {
            prime_massive.push_back(i);
        }
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
        if (result_is_prime)
        {
            std::cout << number << " is prime\n";
        }
        else
        {
            std::cout << number << " isn't prime\n";
        }
        next_prime(number);
        try
        {
            bool result_is_twin_prime = is_twin_prime(number);
            if (result_is_twin_prime)
            {
                std::cout << number << " and " << number+2 << " are twin primes\n";
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Mistake: " << e.what() << '\n';
        }

        std::cout << "enter a range of prime numbers: ";
        std::cin >> start >> end;

        std::vector<int> result_primes_in_range = primes_in_range(start, end);
        unsigned int size_result_primes_in_range = result_primes_in_range.size();

        std::cout << "prime numbers from the range:\n";
        std::cout << '[';
        for(int prime_value = 0; prime_value < size_result_primes_in_range; ++prime_value)
        {
            std::cout << result_primes_in_range[prime_value];
            if (prime_value < result_primes_in_range.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << ']';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Mistake: " << e.what() << '\n';
    }

    return 0;
}
