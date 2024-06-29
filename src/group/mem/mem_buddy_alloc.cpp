/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    // Helper function to create a new MemTreeNode
    MemTreeNode* createMemTreeNode(Address address, uint32_t size)
    {
        MemTreeNode* newNode = new MemTreeNode();
        newNode->state = FREE;  // Assuming the new node is initially free
        newNode->block.address = address;
        newNode->block.size = size;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    void splitBlock(MemTreeNode* node)
    {
        require(node != nullptr, "Node should not be nullptr");

        uint32_t subBlockSize = node->block.size / 2;

        // Create the left child node
        MemTreeNode* leftChild = createMemTreeNode(node->block.address, subBlockSize);

        // Create the right child node
        MemTreeNode* rightChild = createMemTreeNode(node->block.address + subBlockSize, subBlockSize);

        // Update the left and right pointers of the parent node
        node->left = leftChild;
        node->right = rightChild;

        // Recursively split the left and right children
        if (leftChild->block.size > 1)
        {
            splitBlock(leftChild);
        }
        if (rightChild->block.size > 1)
        {
            splitBlock(rightChild);
        }
    }

    MemTreeNode* findNode(MemTreeNode* root, Address address) {
        if (root == nullptr || root->block.address == address) {
            return root;
        }

        if (address < root->block.address) {
            return findNode(root->left, address);
        } else {
            return findNode(root->right, address);
        }
    }

    Address allocateBlock(MemTreeNode* node, uint32_t size)
    {

        require(node->block.size >= size, "Node size is not sufficient for allocation");

        require(node->left == nullptr && node->right == nullptr, "Invalid node type for allocation");

        node->state = OCCUPIED;

        if (node->block.size > size)
        {
            splitBlock(node);
        }

        return node->block.address;
    }

    MemTreeNode* findBestFit(MemTreeNode* node, uint32_t size) {
        if (node == nullptr || node->state == OCCUPIED) {
            return nullptr;
        }

        if (node->block.size < size || (node->left != nullptr && node->right != nullptr)) {
            MemTreeNode* leftFit = findBestFit(node->left, size);
            MemTreeNode* rightFit = findBestFit(node->right, size);

            if (leftFit != nullptr) {
                return leftFit;
            } else {
                return rightFit;
            }
        } else {
            return node;
        }
    }

    Address memBuddySystemAlloc(uint32_t pid, uint32_t size) {
        soProbe(506, "%s(%u, %#x)\n", __func__, pid, size);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(size, "the size of a memory segment must be greater than zero");

        MemTreeNode* freeNode = findBestFit(memTreeRoot, size);

        if (freeNode == nullptr) {
            throw Exception(ENOMEM, __func__);
        }

        Address allocatedAddress = allocateBlock(freeNode, size);

        MemListNode* newOccupiedNode = new MemListNode();
        newOccupiedNode->block.pid = pid;
        newOccupiedNode->block.size = size;
        newOccupiedNode->block.address = allocatedAddress;
        newOccupiedNode->next = memOccupiedHead;
        memOccupiedHead = newOccupiedNode;

        return allocatedAddress;
    }


// ================================================================================== //

} // end of namespace group
