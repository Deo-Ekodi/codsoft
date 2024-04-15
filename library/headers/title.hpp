#pragma once

#include <iostream>
#include <string>

template <typename T>
class Title {
private:
    T title;
public:
    Title() = default;
    Title(T t) : title(t) {}
    T getTitle() const { return title; }
};