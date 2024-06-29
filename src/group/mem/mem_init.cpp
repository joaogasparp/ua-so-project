/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void memInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy policy) 
    {
        const char *pas = policy == FirstFit ? "FirstFit" : policy == BuddySystem ? "BuddySystem" : "Unkown";
        soProbe(501, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);

        require(mSize > osSize, "memory must be bigger than the one use by OS");
        require((mSize % cSize) == 0, "memory size must be a multiple of chunck size");
        require((osSize % cSize) == 0, "memory size for OS must be a multiple of chunck size");
        require(policy == FirstFit or policy == BuddySystem, "policy must be FirstFit or BuddySystem");

        /* TODO POINT: Replace next instruction with your code */
        try {
            // Memory Parameters Setting
            memParameters.chunkSize = cSize;
            memParameters.totalSize = mSize;
            memParameters.kernelSize = osSize;
            memParameters.policy = policy;
    
            // Handling for FirstFit policy
            if (policy == FirstFit)
            {
                MemListNode *headFree = (MemListNode *) malloc(sizeof(MemListNode));
                headFree->block.pid = 0;
                headFree->block.size = mSize - osSize;
                headFree->block.address = osSize;
                headFree->prev = NULL;
                headFree->next = NULL;
                memFreeHead = headFree;
    
                MemListNode *headOccupied = (MemListNode *) malloc(sizeof(MemListNode));
                headOccupied->block.pid = 0;
                headOccupied->block.size = 0;
                headOccupied->block.address = osSize;
                headOccupied->prev = NULL;
                headOccupied->next = NULL;
                memOccupiedHead = headOccupied;
    
                memTreeRoot = NULL;
            }
            // Handling for BuddySystem policy
            else if (policy == BuddySystem)
            {
                MemTreeNode *rootNode = (MemTreeNode *) malloc(sizeof(MemTreeNode));
                rootNode->state = FREE;
                rootNode->block.pid = 0;
                rootNode->block.address = osSize;
                rootNode->block.size = mSize - osSize;
                rootNode->left = NULL;
                rootNode->right = NULL;
                memTreeRoot = rootNode;
    
                memFreeHead = NULL;
                memOccupiedHead = NULL;
            }
        } catch (const std::exception &e) {
            throw Exception(ENOSYS, __func__);
        }
    }

// ================================================================================== //

} // end of namespace group

