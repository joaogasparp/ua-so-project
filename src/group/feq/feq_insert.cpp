/*
 *  \author Joseane Pereira 107474
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void feqInsert(FutureEventType type, uint32_t time, uint32_t pid)
    {
        const char *tas = type == ARRIVAL ? "ARRIVAL" : type == TERMINATE ? "TERMINATE" : "UNKOWN";
        soProbe(204, "%s(%s, %u, %u)\n", __func__, tas, time, pid);

        require(pid > 0, "process ID must be non-zero");

        /* TODO POINT: Replace next instruction with your code */
        //throw Exception(ENOSYS, __func__);

        //the list's elements should be sorted in ascending order of event time;
        //for elements with the same time stamp, TERMINATE events should appear before ARRIVAL events;
        //for elements with the same time stamp and the same type, order of insertion should be preserved.
        //If an anomalous situation occurs, an appropriate exception must be thrown.
        
        // create new node
        FeqEventNode *newNode = new FeqEventNode;
        newNode->event.type = type;
        newNode->event.time = time;
        newNode->event.pid = pid;
        newNode->next = NULL;

        // if the list is empty, insert the new node
        if(feqHead == NULL){
            feqHead = newNode;
            return;
        }

        // if the list is not empty, insert the new node in the right position
        FeqEventNode *current = feqHead;
        FeqEventNode *previous = NULL;

        while(current != NULL){
            // if the new node has a smaller time stamp than the current node, insert the new node before the current node
            if(newNode->event.time < current->event.time){
                // if the new node has a smaller time stamp than the head, insert the new node in the head
                if(current == feqHead){
                    newNode->next = feqHead;
                    feqHead = newNode;
                    return;
                }
                // if the new node has a smaller time stamp than the current node, insert the new node before the current node
                else{
                    newNode->next = current;
                    previous->next = newNode;
                    return;
                }
            }
            // if the new node has a bigger time stamp than the current node, go to the next node
            else if(newNode->event.time > current->event.time){
                previous = current;
                current = current->next;
            }
            // if the new node has the same time stamp as the current node, check the type of the new node and the current node
            else{
                // if the new node has a TERMINATE event and the current node has an ARRIVAL event, insert the new node before the current node
                if(newNode->event.type == TERMINATE && current->event.type == ARRIVAL){
                    // if the new node has a TERMINATE event and the head has an ARRIVAL event, insert the new node in the head
                    if(current == feqHead){
                        newNode->next = feqHead;
                        feqHead = newNode;
                        return;
                    }
                    // if the new node has a TERMINATE event and the current node has an ARRIVAL event, insert the new node before the current node
                    else{
                        newNode->next = current;
                        previous->next = newNode;
                        return;
                    }
                }
                // if the new node has an ARRIVAL event and the current node has a TERMINATE event, go to the next node
                else if(newNode->event.type == ARRIVAL && current->event.type == TERMINATE){
                    previous = current;
                    current = current->next;
                }
                // if the new node has the same time stamp and the same type as the current node, insert the new node after the current node
                else{
                    newNode->next = current->next;
                    current->next = newNode;
                    return;
                }
            }
        }
        // if the new node has a bigger time stamp than all the nodes in the list, insert the new node in the end of the list
        previous->next = newNode;
        return;
    }

// ================================================================================== //

} // end of namespace group

