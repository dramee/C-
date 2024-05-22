#include <iostream>

template <typename T>
bool isEven(T number)
{
    return number % 2 == 0;
}

template <typename Checker, typename None = void>
bool isMatch(Checker checker, int &index)
{
    return false;
}

template <typename Checker, typename FirstArg, typename... Args>
bool isMatch(Checker checker, int &index, FirstArg &&firstArg, Args... args)
{
    if (checker(std::forward<FirstArg>(firstArg)))
    {
        return true;
    }
    else
    {
        index++;
        return isMatch(checker, index, args...);
    }
}

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker checker, Args... args)
{
    int index = 0;
    return isMatch(checker, index, args...) ? index : -1;
}