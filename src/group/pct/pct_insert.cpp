/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708 
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctInsert(uint32_t pid, uint32_t time, uint32_t lifetime, AddressSpaceProfile *profile)
    {
        soProbe(304, "%s(%d, %u, %u, %p)\n", __func__, pid, time, lifetime, profile);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(time >= 0, "time must be >= 0");
        require(lifetime > 0, "lifetime must be > 0");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        PctNode *newNode = new PctNode;
        newNode->pcb.pid = pid;
        newNode->pcb.state = NEW;
        newNode->pcb.arrivalTime = time;
        newNode->pcb.lifetime = lifetime;
        newNode->pcb.activationTime = NO_TIME;
        newNode->pcb.finishTime = NO_TIME;
        newNode->pcb.memProfile = *profile;
        newNode->next = NULL;

        if(pctHead == NULL || pctHead->pcb.pid > pid){
            newNode->next = pctHead;
            pctHead = newNode;
        }
        else{
            PctNode *node = pctHead;
            while(node->next != NULL && node->next->pcb.pid < pid){
                node = node->next;
            }
            if(node->next != NULL && node->next->pcb.pid == pid){
                throw Exception(EINVAL, "PID already exists");
            }
            newNode->next = node->next;
            node->next = newNode;
        }

    }

// ================================================================================== //

} // end of namespace group

