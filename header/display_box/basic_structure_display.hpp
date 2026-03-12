# pragma once
#include <unordered_map>
#include <string>
#include <iostream>


template <typename K, typename V>
void printUnorderedMap(const std::unordered_map<K, V>& mp,
                       const std::string& name = "unordered_map") {
    std::cout << name << " {\n";
    for (const auto& [key, value] : mp) {
        std::cout << "  [" << key << "] -> " << value << '\n';
    }
    std::cout << "}\n";
}