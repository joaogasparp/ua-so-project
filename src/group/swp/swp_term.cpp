/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void swpTerm()
    {
        soProbe(402, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        SwpNode* current = swpHead;
        while (current != nullptr)
        {
            SwpNode* next = current->next;
            delete current;
            current = next;
        }

        swpHead = nullptr;
        swpTail = nullptr;
    }

// ================================================================================== //

} // end of namespace group

