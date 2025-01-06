#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree; 

    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict(){
            delete tree;
        }
        
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out << *(bs.tree);
            return out;
        }

        V operator[](std::string key){
            TableEntry<V> entry(key);
            TableEntry<V> result = tree -> search(entry);
            return result.value;
        }

        int entries(){
            return tree -> size();
        }
        
        void insert(std::string key, V value){
            TableEntry<V> entry(key, value);
            tree -> insert(entry);
        }

        V search(std::string key){
            TableEntry<V> entry(key);
            TableEntry<V> result = tree -> search(entry);
            return result.value;
        }

        V remove(std::string key){
            TableEntry<V> entry(key);
            TableEntry<V> result = tree -> search(entry);
            tree -> remove(entry);
            return result.value;
        }
};

#endif