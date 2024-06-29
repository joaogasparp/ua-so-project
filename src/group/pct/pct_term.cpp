/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708 
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void pctTerm() 
    {
        soProbe(302, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        PctNode *current = pctHead;
        while (current != NULL) {
            PctNode *next = current->next;
            free(current);
            current = next;
        }

        pctHead = NULL;
    }

// ================================================================================== //

} // end of namespace group

