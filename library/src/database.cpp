// /**
//  * skiplist implementation of database
// */

// #include <iostream>
// #include <string>
// #include <vector>
// #include <random>
// #include <unordered_map>
// #include <ctime>

// #include "headers/book.hpp"

// template <typename keyType = std::string,typename ValueType = std::string>
// class SkipListNode{
//     KeyType key;
//     ValueType value;
//     std::vector<SkipListNode*> forward;

//     SkipListNode(
//         const keyType& k, 
//         const ValueType& v, 
//         int level
//         ):
//         key(k), 
//         value(v), 
//         forward(level, nullptr){}
// };

// template<typename KeyType, typename ValueType>
// class SkipList
// {
// private:
//     int maxLevel;
//     float probability;
//     int level;
//     SkipListNode<keyType, ValueType*> header;
//     std::default_random_engine generator;
//     std::uniform_real_distribution<float> distribution;
//     std::unordered_map<keyType, SkipListNode<KeyType>, ValueType>*> nodeMap;

//     int randomLevel(){
//         int lvl = 1;
//         while(distribution(generator) < probability && lvl < maxLevel){
//             lvl++;
//         }
//         return lvl;
//     }

// public:
//     SkipList(
//         int maxLvl, 
//         float (prob)): 
//         maxLevel(maxLvl), 
//         probability(prob), 
//         level(0), 
//         header(new SkipListNode<KeyType, ValueType>(KeyType(), maxLvl)), 
//         generator(std::random_device()()), 
//         distribution(0.0f, 1.0f){}

//     void insert(const KeyType& key, const ValueType& value){
//         int newLevel = randomLevel();
//         if(newLevel > level){
//             for(int i = level + 1; i <= newLevel; ++i){
//                 header.forward.push_back(nullptr);
//             }
//             level = newLevel;
//         }

//         SkipListNode<KeyType, ValueTypr>* newNode = new SkipListNode<KeyType, ValueType>(key, value, newLevel);
//         SkipListNode<KeyType, ValueType>* current = header;

//         for (int i = level; i >= 0; --i) {
//             while (current->forward[i] != nullptr && current->forward[i]->key < key) {
//                 current = current->forward[i];
//             }
//             if (i <= newLevel) {
//                 newNode->forward[i] = current->forward[i];
//                 current->forward[i] = newNode;
//             }
//         }
        
//         nodeMap[key] = newNode;
//     }   //insert

//     ValueType* search(const KeyType& key) {
//         if (nodeMap.find(key) != nodeMap.end()) {
//             return &nodeMap[key]->value;
//         }
//         return nullptr;
//     }   // search

//     bool checkOutBook(const KeyType& key) {
//         auto node = nodeMap.find(key);
//         if (node != nodeMap.end()) {
//             if (!node->second->value.isCheckedOut()) {
//                 node->second->value.checkOut();
//                 return true;
//             }
//         }
//         return false;
//     }   // checkout

//     bool returnBook(const KeyType& key) {
//         auto node = nodeMap.find(key);
//         if (node != nodeMap.end()) {
//             if (node->second->value.isCheckedOut()) {
//                 node->second->value.returnBook();
//                 return true;
//             }
//         }
//         return false;
//     }   // return

//     bool isBookAvailable(const KeyType& key) {
//         auto node = nodeMap.find(key);
//         if (node != nodeMap.end()) {
//             return !node->second->value.isCheckedOut();
//         }
//         return false;
//     }   // availability

//     double calculateFine(const KeyType& key, int overdueDays, double finePerDay) {
//         auto node = nodeMap.find(key);
//         if (node != nodeMap.end()) {
//             time_t currentTime = std::time(nullptr);
//             time_t checkoutTime = node->second->value.getCheckoutDate();
//             if (checkoutTime != 0 && currentTime > checkoutTime) {
//                 int daysOverdue = (currentTime - checkoutTime) / (24 * 60 * 60);
//                 return daysOverdue * finePerDay;
//             }
//         }
//         return 0.0;
//     }   // fine

//     ~SkipList(){
//         SkipListNode<KeyType, ValueType>* current = header;
//         while (current != nullptr) {
//             SkipListNode<KeyType, ValueType>* temp = current;
//             current = current->forward[0];
//             delete temp;
//         }
//     }   // destructor
// };

// /**
//  * database complete as above
// */

// /**
//  * functions to be called from main.py
//  * 
//  * search
//  * checkoutbook
//  * returnbook
//  * isbookavailable
//  * calculatefine
// */

// int main(){
//     std::string author, isbn, title;
//     std::cout << "enter author, isbn, title : " << std::endl;
//     std::cin >> author >> title >> isbn;
//     SkipList<std::string, Book<std::string, std::string, std::string>> library(5, 0.5);
//     Book<std::string, std::string, std::string> book1(author, isbn, title);

//     library.insert(isbn, book1);
// }