/*
 * MIT License
 * 
 * Copyright (c) 2023 Ahmad Fauzan <noxindocraft@gmail.com> 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef VAR_DUMP_H
#define VAR_DUMP_H

#include <iostream>
#include <typeinfo>
#include <vector>
#include <map>
#include <unordered_map>

// Forward declarations for custom class output stream operator overloads
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value>& map);

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<Key, Value>& unordered_map);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<T, T>& pair);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& init_list);

// Overload for custom class
class CustomClass
{
public:
    int value;

    CustomClass(int val) : value(val) {}
};

std::ostream& operator<<(std::ostream& os, const CustomClass& custom)
{
    os << "CustomClass(" << custom.value << ")";
    return os;
}

// Overload for vector
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "std::vector [\n";
    for (const auto& element : vec)
    {
        os << "  " << element << "\n";
    }
    os << "]";
    return os;
}

// Overload for map
template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value>& map)
{
    os << "std::map {\n";
    for (const auto& element : map)
    {
        os << "  {" << element.first << ": " << element.second << "}\n";
    }
    os << "}";
    return os;
}

// Overload for unordered_map
template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<Key, Value>& unordered_map)
{
    os << "std::unordered_map {\n";
    for (const auto& element : unordered_map)
    {
        os << "  {" << element.first << ": " << element.second << "}\n";
    }
    os << "}";
    return os;
}

// Overload for pair
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<T, T>& pair)
{
    os << "std::pair(" << pair.first << ", " << pair.second << ")";
    return os;
}

// Overload for initializer_list
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& init_list)
{
    os << "std::initializer_list {\n";
    for (const auto& element : init_list)
    {
        os << "  " << element << "\n";
    }
    os << "}";
    return os;
}

/**

@brief Displays the type and value of a variable using var_dump format.
This function echoes the type and value of the specified variable using the var_dump format.
It does not return a value but prints the information to the standard output stream.
@tparam T The type of the variable.
@param variable The variable to be dumped.
@remarks This function requires the inclusion of the <iostream> and <typeinfo> headers.
@example
int x = 42;
vardump(x);
// Output:
// Type: int
// Value: 42
@note The variable must have a valid overload for the insertion operator (<<).
*/
template <typename T>
void vardump(const T& variable)
{
std::cout << "Type: " << typeid(variable).name() << "\n";
std::cout << "Value: " << variable << "\n\n";
}
#endif // VAR_DUMP_H

