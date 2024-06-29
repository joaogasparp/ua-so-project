#include "somm23.h"
#include <stdint.h>

namespace group {

    void sortFreeBlocksByAddress() {
        if (memFreeHead == nullptr || memFreeHead->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            MemListNode *current = memFreeHead;
            while (current->next != nullptr) {
                if (current->block.address > current->next->block.address) {
                    // Swap the blocks
                    MemBlock tempBlock = current->block;
                    current->block = current->next->block;
                    current->next->block = tempBlock;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }


    void mergeFreeBlocks() {
        if (memFreeHead == nullptr) return;

        // Sort the blocks by address
        sortFreeBlocksByAddress();

        MemListNode *current = memFreeHead;
        while (current != nullptr && current->next != nullptr) {
            Address currentEnd = current->block.address + current->block.size;

            // Merge with adjacent blocks
            while (current->next != nullptr && currentEnd == current->next->block.address) {
                current->block.size += current->next->block.size;
                MemListNode *toDelete = current->next;
                current->next = toDelete->next;
                if (toDelete->next != nullptr) {
                    toDelete->next->prev = current;
                }
                delete toDelete;

                // Update the end address after merging
                currentEnd = current->block.address + current->block.size;
            }

            current = current->next;
        }
    }

    void memFirstFitFree(Address address) {
        soProbe(508, "%s(%u)\n", __func__, address);

        // Ensure that the occupied list is not NULL
        require(memOccupiedHead != nullptr, "Occupied list should contain nodes");

        // Search for the block with the given address in the occupied list
        MemListNode *current = memOccupiedHead;
        MemListNode *prev = nullptr;

        while (current != nullptr) {
            if (current->block.address == address) {
                break;
            }
            prev = current;
            current = current->next;
        }

        // Handle the block not found case
        require(current != nullptr, "Block not found in the occupied list");

        // Remove the block from the occupied list
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            memOccupiedHead = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = prev;
        }

        // Add the block to the free list
        current->next = memFreeHead;
        if (memFreeHead != nullptr) {
            memFreeHead->prev = current;
        }
        current->prev = nullptr;
        memFreeHead = current;

        // Optionally, merge adjacent free blocks to prevent fragmentation
        mergeFreeBlocks();
    }

} // end of namespace group