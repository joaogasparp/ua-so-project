/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    SwappedProcess *swpPeek(uint32_t idx)
    {
        soProbe(405, "%s(%u)\n", __func__, idx);

        /* TODO POINT: Replace next instruction with your code */
        try
        {
            idx = idx + 1;
            if (swpHead == nullptr || swpTail == nullptr || swpHead->next == nullptr)
            {
                return NULL;
            }

            SwpNode *currentNode = swpHead->next;
            uint32_t currentIndex = 0;

            while (currentIndex < idx && currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
                currentIndex++;
            }

            if (currentIndex != idx)
            {
                return NULL;
            }

            return &(currentNode->process);
        }
        catch (const std::exception &e)
        {
            throw Exception(ENOSYS, __func__);
        }
    }

// ================================================================================== //

} // end of namespace group

