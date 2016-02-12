/**
 * @file avl_tree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "avl_tree.h"

template <class K, class V>
const V& avl_tree<K, V>::find(const K& key) const
{
    return find(root_.get(), key);
}

template <class K, class V>
const V& avl_tree<K, V>::find(const node* subtree, const K& key) const
{
    if (!subtree)
    {
        throw std::out_of_range{"invalid key"};
    }
    else if (key == subtree->key)
    {
        return subtree->value;
    }
    else if (key < subtree->key)
    {
        return find(subtree->left.get(), key);
    }
    else
    {
        return find(subtree->right.get(), key);
    }
}

template <class K, class V>
void avl_tree<K, V>::rotate_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    auto newSubRoot = std::move(t->right);
    auto temporary = std::move(newSubRoot->left);

    newSubRoot->left = std::move(t);
    newSubRoot->left->right = std::move(temporary);
    t = std::move(newSubRoot);

    t->left->height = max(heightOrNeg1(t->left->left.get()),
                          heightOrNeg1(t->left->right.get())) +
                      1;
    t->height =
        max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
}

template <class K, class V>
void avl_tree<K, V>::rotate_left_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotate_left(t->left);
    rotate_right(t);
}

template <class K, class V>
void avl_tree<K, V>::rotate_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    auto newSubRoot = std::move(t->left);
    auto temporary = std::move(newSubRoot->right);

    newSubRoot->right = std::move(t);
    newSubRoot->right->left = std::move(temporary);
    t = std::move(newSubRoot);

    t->right->height = 1 + std::max(heightOrNeg1(t->right->left.get()),
                                    heightOrNeg1(t->right->right.get()));
    t->height =
        1 + max(heightOrNeg1(t->right.get()), heightOrNeg1(t->left.get()));
}

template <class K, class V>
void avl_tree<K, V>::rotate_right_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotate_right(t->right);
    rotate_left(t);
}

template <class K, class V>
void avl_tree<K, V>::insert(K key, V value)
{
    insert(root_, std::move(key), std::move(value));
}

template <class K, class V>
void avl_tree<K, V>::insert(std::unique_ptr<node>& subtree, K key, V value)
{
    if (!subtree)
    {
        subtree = std::make_unique<node>(std::move(key), std::move(value));
    }
    else if (key < subtree->key)
    {
        insert(subtree->left, std::move(key), std::move(value));
    }
    else
    {
        insert(subtree->right, std::move(key), std::move(value));
    }
    rebalance(subtree);
}

template <class K, class V>
void avl_tree<K, V>::rebalance(std::unique_ptr<node>& subroot)
{
    auto balance =
        heightOrNeg1(subroot->left.get()) - heightOrNeg1(subroot->right.get());

    if (balance == 2)
    {
        rebalance_left(subroot);
    }
    else if (balance == -2)
    {
        rebalance_right(subroot);
    }
    subroot->height = 1 + std::max(heightOrNeg1(subroot->left.get()),
                                   heightOrNeg1(subroot->right.get()));
}

template <class K, class V>
void avl_tree<K, V>::rebalance_left(std::unique_ptr<node>& subroot)
{
    auto left = subroot->left.get();
    auto balance_left =
        heightOrNeg1(left->left.get()) - heightOrNeg1(left->right.get());

    if (balance_left >= 0)
    {
        rotate_right(subroot);
    }
    else
    {
        rotate_left_right(subroot);
    }
}

template <class K, class V>
void avl_tree<K, V>::rebalance_right(std::unique_ptr<node>& subroot)
{
    auto right = subroot->right.get();
    auto balance_right =
        heightOrNeg1(right->left.get()) - heightOrNeg1(right->right.get());

    if (balance_right <= 0)
    {
        rotate_left(subroot);
    }
    else
    {
        rotate_right_left(subroot);
    }
}