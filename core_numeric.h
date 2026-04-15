#ifndef CORE_NUMERIC_H
#define CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace core_numeric {

    template <typename C>
    concept Iterable = requires(C c) {
        std::begin(c);
        std::end(c);
    };

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
    };

    template <typename T>
    concept Divisible = requires(T a, std::size_t n) {
        { a / n } -> std::same_as<T>;
    };

    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a < b } -> std::same_as<bool>;
    };

    template <Iterable C>
    requires Addable<std::ranges::range_value_t<C>>
    auto sum(const C& container) {
        using T = std::ranges::range_value_t<C>;
        T result = T{};

        for (const auto& elemento : container) {
            result = result + elemento;
        }
        return result;
    }

    template <Iterable C>
    requires Addable<std::ranges::range_value_t<C>> && Divisible<std::ranges::range_value_t<C>>
    auto mean(const C& container) {
        auto total = sum(container);
        return total / std::size(container);
    }

    template <Iterable C>
    requires Comparable<std::ranges::range_value_t<C>>
    auto max(const C& container) {
        auto it = std::begin(container);
        auto max_val = *it;
        ++it;

        for (; it != std::end(container); ++it) {
            if (max_val < *it) {
                max_val = *it;
            }
        }
        return max_val;
    }

    template <Iterable C>
    requires Addable<std::ranges::range_value_t<C>> && Divisible<std::ranges::range_value_t<C>>
    auto variance(const C& container) {
        auto m = mean(container);
        using T = std::ranges::range_value_t<C>;
        T sum_cuadrados = T{};

        for (const auto& elemento : container) {
            auto diferencia = elemento - m;
            sum_cuadrados = sum_cuadrados + (diferencia * diferencia);
        }
        return sum_cuadrados / std::size(container);
    }

    template <Iterable C, typename F>
    auto transform_reduce(const C& container, F funcion_transformadora) {
        using ResultType = decltype(funcion_transformadora(*std::begin(container)));
        ResultType acumulador = ResultType{};

        for (const auto& elemento : container) {
            acumulador = acumulador + funcion_transformadora(elemento);
        }
        return acumulador;
    }

    template <typename... Args>
    requires (Addable<Args> && ...)
    auto sum_variadic(Args... args) {
        return (args + ...);
    }

    template <typename... Args>
    requires (Addable<Args> && ...)
    auto mean_variadic(Args... args) {
        auto total = sum_variadic(args...);

        if constexpr (std::is_integral_v<decltype(total)>) {
            return static_cast<double>(total) / sizeof...(args);
        } else {
            return total / sizeof...(args);
        }
    }

    template <typename... Args>
    requires (Addable<Args> && ...)
    auto variance_variadic(Args... args) {
        auto m = mean_variadic(args...);
        return (((args - m) * (args - m)) + ...) / sizeof...(args);
    }

    template <typename First, typename... Rest>
    requires (Comparable<First> && (Comparable<Rest> && ...))
    auto max_variadic(First first, Rest... rest) {
        auto max_val = first;
        ([&] {
            if (max_val < rest) max_val = rest;
        }(), ...);
        return max_val;
    }

}

#endif