#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {

    private:
        BSNode<T> *root;
        int nelementos;

        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (!n) {
                throw std::runtime_error("No se encuentra el elemento.");
            } else if (e < n->elem) {
                return search(n->left, e);
                } else if (e > n->elem) {
                return search(n->right, e);
            } else {
                return n;
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (!n) {
                nelementos++;
                return new BSNode<T>(e);
            } else if (e == n->elem) {
                throw std::runtime_error("El elemento estÃ¡ duplicado");
            } else if (e < n->elem) {
                n->left = insert(n->left, e);
            } else {
                n->right = insert(n->right, e);
            }
            return n;
        }

        void imprimir_orden(std::ostream &out, BSNode<T>* n) const {
            if (n) {
                imprimir_orden(out, n->left);
                out << n->elem << " ";
                imprimir_orden(out, n->right);
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (!n) {
                throw std::runtime_error("Elemento no encontrado");
            } else if (e < n->elem) {
                n->left = remove(n->left, e);
                } else if (e > n->elem) {
                n->right = remove(n->right, e);
            } else {
                if (n->left && n->right) {
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);

                } else {
                    BSNode<T>* temp = n;
                    n = (n->left) ? n->left : n->right;
                    delete temp;
                    nelementos--;
                }
            }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (!n) {
                throw std::runtime_error("El subÃ¡rbol estÃ¡ vacÃ­o.");
            } else if (n->right) {
                return max(n->right);
            } else {
                return n->elem;
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (!n->right) {
                BSNode<T>* temp = n;
                n = n->left;
                delete temp;
                nelementos--;
            } else {
                n->right = remove_max(n->right);
            }
            return n;
        }

        T min(BSNode<T>* n) const {
            if (!n) {
                throw std::runtime_error("El subÃ¡rbol estÃ¡vacÃ­o");
            } else if (n->left) {
                return min(n->left);
            } else {
                return n->elem;
            }
        }

        BSNode<T>* remove_min(BSNode<T>* n) {
            if (!n->left) {
                BSNode<T>* temp = n;
                n = n->right;
                delete temp;
                nelementos--;
            } else {
                n->left = remove_min(n->left);
            }
            return n;
        }

        void delete_cascade(BSNode<T>* n) {
            if (n) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }


    public:
        BSTree() {
            nelementos = 0;
            root = nullptr;
        }

        int size() const {
            return nelementos;
        }

        T search(T e) const {
            BSNode<T>* result = search(root, e);
            return result->elem;
        }

        T operator[](T e) const {
            return search(e);
        }

        void insert(T e) {
            root = insert(root, e);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.imprimir_orden(out, bst.root);
            return out;
        }

        void remove(T e) {
            root = remove(root, e);
        }

        T max() const {
            return max(root);
        }

        T min() const {
            return min(root);
        }

        void prune() {
            if (!root) {
                throw std::runtime_error("El árbol está vacío.");
            }
            root = remove_max(root);
            if (root) {
                root = remove_min(root);
            }
        }

        ~BSTree() {
            delete_cascade(root);
        }
};

#endif