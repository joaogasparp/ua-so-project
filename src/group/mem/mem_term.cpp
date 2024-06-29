/*
 *  \author ...
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //
    // Helper function to recursively release memory in the binary tree
    void memTermHelper(MemTreeNode* node)
    {
        if (node == nullptr)
            return;

        memTermHelper(node->left);
        memTermHelper(node->right);
        delete node;
    }

    void memTerm() 
    {
        soProbe(502, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        // Reset the linked lists and free the memory
        while (memFreeHead != nullptr)
        {
            MemListNode* temp = memFreeHead;
            memFreeHead = memFreeHead->next;
            delete temp;
        }

        while (memOccupiedHead != nullptr)
        {
            MemListNode* temp = memOccupiedHead;
            memOccupiedHead = memOccupiedHead->next;
            delete temp;
        }

        // Reset the binary tree and free the memory
        if (memTreeRoot != nullptr)
        {
            memTermHelper(memTreeRoot);
            delete memTreeRoot;
            memTreeRoot = nullptr;
        }
    }

// ================================================================================== //

} // end of namespace group