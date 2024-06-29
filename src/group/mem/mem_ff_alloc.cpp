/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group
{

// ================================================================================== //

    Address memFirstFitAlloc(uint32_t pid, uint32_t size) {
        soProbe(505, "%s(%u, %#x)\n", __func__, pid, size);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(size, "the size of a memory segment must be greater than zero");

        MemListNode* currentNode = memFreeHead;
        MemListNode* prevNode = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->block.size >= size) {
                Address allocatedAddress = currentNode->block.address;

                // Create a new occupied block node
                MemListNode* newOccupiedNode = new MemListNode();
                newOccupiedNode->block.pid = pid;
                newOccupiedNode->block.size = size;
                newOccupiedNode->block.address = allocatedAddress;
                newOccupiedNode->next = memOccupiedHead;
                memOccupiedHead = newOccupiedNode;

                // Split the block if it's larger than the requested size
                if (currentNode->block.size > size) {
                    MemListNode* newFreeNode = new MemListNode();
                    newFreeNode->block.size = currentNode->block.size - size;
                    newFreeNode->block.address = allocatedAddress + size;
                    newFreeNode->next = currentNode->next;

                    currentNode->block.size = size;

                    if (prevNode == nullptr) {
                        memFreeHead = newFreeNode;
                    } else {
                        prevNode->next = newFreeNode;
                    }
                } else {
                    if (prevNode == nullptr) {
                        memFreeHead = currentNode->next;
                    } else {
                        prevNode->next = currentNode->next;
                    }
                }

                delete currentNode;
                return allocatedAddress;
            }

            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        throw Exception(NULL_ADDRESS, __func__);
    }


// ================================================================================== //

} // end of namespace group