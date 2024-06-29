/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708 
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctUpdateState(uint32_t pid, ProcessState state, uint32_t time = NO_TIME, AddressSpaceMapping *mapping = NULL)
    {
        soProbe(309, "%s(%d, %u, %u)\n", __func__, pid, state, time);

        require(pid > 0, "a valid process ID must be greater than zero");

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        PctNode *current = pctHead;
        while (current != NULL) {
            if(current->pcb.pid == pid) {
                current->pcb.state = state;
                if(state == ACTIVE) {
                    current->pcb.activationTime = time;
                    if(mapping != NULL) {
                        current->pcb.memMapping = *mapping;
                    } else {
                        throw Exception(EINVAL, "Mapping not defined for the ACTIVE state");
                    }
                } else if (state == FINISHED){
                    current->pcb.finishTime = time;
                }
            }
            current = current->next;
        }

        

    }

// ================================================================================== //

} // end of namespace group

