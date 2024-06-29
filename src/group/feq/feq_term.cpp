/*
 *  \author Joseane Pereira 107474
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void feqTerm() 
    {
        soProbe(202, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        //throw Exception(ENOSYS, __func__);

        // delete all events
        // if the list is empty, do nothing
        // if the list is not empty, delete all events

        
        while(feqHead != NULL){
            FeqEventNode *current = feqHead;
            feqHead = feqHead->next;
            delete current;
        }
        


    }

// ================================================================================== //

} // end of namespace group

