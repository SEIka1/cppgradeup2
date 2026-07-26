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
    int max_number = INT_MAX - 18;
    unsigned int amount_of_denominators = 0;
    unsigned int denom = 1;
    if (n < 2)
    {
        throw std::invalid_argument("Number must be more than 2");
    }

    if (n > max_number)
    {
        throw std::out_of_range("Too large number to process");
    }

    unsigned int limit_n = std::sqrt(n);
    while (denom <= limit_n)
    {
        denom++;
        if (n % denom == 0)
        {
            amount_of_denominators++;
            break;
        }
    }

    return (amount_of_denominators == 0);
}

int next_prime(unsigned n)
{
    bool result_is_prime = is_prime(n);
    if (result_is_prime)
    {
        unsigned int next_prime_number = n+2;
        while (!is_prime(next_prime_number))
        {
            next_prime_number++;
        }
        std::cout << "next prime: " << next_prime_number << '\n';
        return next_prime_number;
    }
    else
    {
        std::cout << "There is no next prime number for this :(\n";
    }
    return 0;
}

bool is_twin_prime(unsigned n)
{
    if (!is_prime(n))
    {
        throw std::invalid_argument("Don't work with non-prime number");
    }

    return (is_prime(n) && is_prime(n+2));
}

std::vector<int> primes_in_range(int start, int end)
{
    if (end < 2 || start > end)
    {
        return {};
    }
    std::vector<bool> is_prime(end + 1, true);
    for (int denom_eratosphene = 2; denom_eratosphene <= std::sqrt(end); ++denom_eratosphene)
    {
        if (is_prime[denom_eratosphene])
        {
            int start_multiplicity = std::max(denom_eratosphene * denom_eratosphene, (start + denom_eratosphene - 1) / denom_eratosphene * denom_eratosphene);
            for (int i = start_multiplicity; i <= end; i += denom_eratosphene)
            {
                is_prime[i] = false;
            }
        }
    }

    std::vector<int> prime_massive;
    int true_start = std::max(start, 2);
    for (int i = true_start; i <= end; ++i)
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
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Mistake: " << e.what() << '\n';
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Mistake: " << e.what() << '\n';
    }

    return 0;
}
