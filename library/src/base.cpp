/**
 * compile with:
 * -fPIC such:
 * 
 * gcc -fPIC -shared -o libxx.dll base.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <unordered_map>
#include <ctime>
#include <cstring>

extern "C" {

// Author Class
struct Author {
    std::string name;
};

// ISBN Class
struct ISBN {
    std::string number;
};

// Title Class
struct Title {
    std::string title;
};

// Book Class
struct Book {
    Author author;
    ISBN isbn;
    Title title;
    bool checkedOut;
    time_t checkoutDate;
};

// Skip List Node
struct SkipListNode {
    ISBN key;
    Book value;
    std::vector<SkipListNode*> forward;
};

// Skip List Class
struct SkipList {
    int maxLevel;
    float probability;
    int level;
    SkipListNode* header;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    std::unordered_map<std::string, SkipListNode*> nodeMap;
};

// Create Book
Book* create_book(const char* author_name, const char* isbn_num, const char* title_str) {
    Book* book = new Book();
    book->author.name = author_name;
    book->isbn.number = isbn_num;
    book->title.title = title_str;
    book->checkedOut = false;
    book->checkoutDate = 0;
    return book;
}

// Check Out Book
bool check_out_book(SkipList* list, const char* isbn_num) {
    std::string isbn_str(isbn_num);
    auto node = list->nodeMap.find(isbn_str);
    if (node != list->nodeMap.end() && !node->second->value.checkedOut) {
        node->second->value.checkedOut = true;
        node->second->value.checkoutDate = std::time(nullptr);
        return true;
    }
    return false;
}

// Return Book
bool return_book(SkipList* list, const char* isbn_num) {
    std::string isbn_str(isbn_num);
    auto node = list->nodeMap.find(isbn_str);
    if (node != list->nodeMap.end() && node->second->value.checkedOut) {
        node->second->value.checkedOut = false;
        node->second->value.checkoutDate = 0;
        return true;
    }
    return false;
}

// Is Book Available
bool is_book_available(SkipList* list, const char* isbn_num) {
    std::string isbn_str(isbn_num);
    auto node = list->nodeMap.find(isbn_str);
    return (node != list->nodeMap.end() && !node->second->value.checkedOut);
}

// Calculate Fine
double calculate_fine(SkipList* list, const char* isbn_num, int overdue_days, double fine_per_day) {
    std::string isbn_str(isbn_num);
    auto node = list->nodeMap.find(isbn_str);
    if (node != list->nodeMap.end() && node->second->value.checkedOut) {
        time_t currentTime = std::time(nullptr);
        time_t checkoutTime = node->second->value.checkoutDate;
        if (currentTime > checkoutTime) {
            int daysOverdue = (currentTime - checkoutTime) / (24 * 60 * 60);
            return daysOverdue * fine_per_day;
        }
    }
    return 0.0;
}

// Add Book to Skip List
void add_book(SkipList* list, Book* book) {
    int newLevel = 1;
    while (list->distribution(list->generator) < list->probability && newLevel < list->maxLevel) {
        newLevel++;
    }

    if (newLevel > list->level) {
        for (int i = list->level + 1; i <= newLevel; ++i) {
            list->header->forward.push_back(nullptr);
        }
        list->level = newLevel;
    }

    SkipListNode* newNode = new SkipListNode();
    newNode->key = book->isbn;
    newNode->value = *book;
    newNode->forward.resize(newLevel, nullptr);

    SkipListNode* current = list->header;
    for (int i = list->level - 1; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key.number < newNode->key.number) {
            current = current->forward[i];
        }
        if (i < newLevel) {
            newNode->forward[i] = current->forward[i];
            current->forward[i] = newNode;
        }
    }

    list->nodeMap[book->isbn.number] = newNode;
}

// Create Skip List
SkipList* create_book_db(int maxLvl, float prob) {
    SkipList* list = new SkipList();
    list->maxLevel = maxLvl;
    list->probability = prob;
    list->level = 0;
    list->header = new SkipListNode();
    list->generator = std::default_random_engine(std::random_device()());
    list->distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
    return list;
}

// Free Skip List Memory
void free_book_db(SkipList* list) {
    if (!list) return;
    SkipListNode* current = list->header;
    while (current) {
        SkipListNode* temp = current;
        current = current->forward[0];
        delete temp;
    }
    delete list;
}

}  // extern "C"
