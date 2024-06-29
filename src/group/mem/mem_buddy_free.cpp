/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    MemTreeNode* findNode(MemTreeNode* root, unsigned int address);

    // Function to find the parent of a node in the binary tree
    MemTreeNode* findParent(MemTreeNode* root, MemTreeNode* node) {
        if (root == nullptr || root->left == node || root->right == node) {
            return root;
        }

        MemTreeNode* leftParent = findParent(root->left, node);
        if (leftParent != nullptr) {
            return leftParent;
        }

        return findParent(root->right, node);
    }

    // Function to merge adjacent free blocks in the binary tree
    void memBuddySystemMerge(MemTreeNode* root, MemTreeNode* node) {
        if (node == nullptr || node->state != FREE) {
            return;
        }

        if (node->left != nullptr && node->left->state == FREE &&
            node->right != nullptr && node->right->state == FREE) {

            node->state = FREE;
            node->left = nullptr;
            node->right = nullptr;

            MemTreeNode* parent = findParent(root, node);

            memBuddySystemMerge(root, parent);
        }
    }

    void memBuddySystemFree(Address address)
    {
        soProbe(509, "%s(%u)\n", __func__, address);

        /* TODO POINT: Replace next instruction with your code */
        require(memTreeRoot != nullptr, "Binary tree should be initialized");

        if (address == 0)
        {
            throw Exception(EINVAL, __func__);
        }

        MemTreeNode* targetNode = findNode(memTreeRoot, address);

        require(targetNode != nullptr, "Block to be freed not found in the binary tree");

        targetNode->state = FREE;

        memBuddySystemMerge(memTreeRoot, targetNode);
    }

// ================================================================================== //

} // end of namespace group

