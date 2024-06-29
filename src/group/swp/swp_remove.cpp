/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void swpRemove(uint32_t idx)
    {
        soProbe(406, "%s(%u)\n", __func__, idx);
        idx = idx + 1;
        /* TODO POINT: Replace next instruction with your code */
        try
        {
            // Check if the queue is empty
            if (swpHead == nullptr || swpTail == nullptr || swpHead->next == nullptr)
            {
                throw Exception(EINVAL, __func__);
            }

            SwpNode *prevNode = swpHead;
            SwpNode *currentNode = swpHead->next;
            uint32_t currentIndex = 0;

            while (currentIndex < idx && currentNode->next != nullptr)
            {
                prevNode = currentNode;
                currentNode = currentNode->next;
                currentIndex++;
            }

            if (currentIndex != idx)
            {
                throw Exception(EINVAL, __func__);
            }
            prevNode->next = currentNode->next;

            if (currentNode == swpTail)
            {
                swpTail = prevNode;
            }

            delete currentNode;
        }
        catch (const std::exception &e)
        {
            throw Exception(ENOSYS, __func__);
        }
    }

// ================================================================================== //

} // end of namespace group

