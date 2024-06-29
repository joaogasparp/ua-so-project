/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    /*
     * \brief Init the module's internal data structure
     */
    void swpInit()
    {
        soProbe(401, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        if (swpHead != nullptr || swpTail != nullptr){
            throw Exception(ENOSYS, __func__);
        }

        swpHead = new SwpNode();
        swpTail = new SwpNode();

        swpHead->process = {};
        swpTail->process = {};

        swpHead->next = swpTail;
        swpTail->next = nullptr;
    }

// ================================================================================== //

} // end of namespace group

