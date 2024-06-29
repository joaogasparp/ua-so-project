/*
 *  \author Joseane Pereira 107474
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    FutureEvent feqPop()
    {
        soProbe(205, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        //throw Exception(ENOSYS, __func__);

        // if the list is empty, return an empty event
        // if the list is not empty, return the first event and remove it from the list

        if(feqHead == NULL){
            return FutureEvent();
        }
        FeqEventNode *current = feqHead;
        feqHead = feqHead->next;
        FutureEvent event = current->event;
        delete current;
        return event;
        

    }

// ================================================================================== //

    bool feqIsEmpty()
    {
        soProbe(206, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        //throw Exception(ENOSYS, __func__);

        // if the list is empty, return true
        // if the list is not empty, return false

        if(feqHead == NULL){
            return true;
        }
        return false;

    }

// ================================================================================== //

} // end of namespace group

