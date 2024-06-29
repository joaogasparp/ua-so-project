/*
 *  \author Joseane Pereira 107474
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    bool simStep()
    {
        soProbe(107, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        
            //Process, if possible, a step of the simulation.

            //This function is responsible for fetching an event from the FEQ module and process it, interacting with all the other modules as necessary. If the FEQ queue is empty, nothing should be done and the function must return false. Otherwise, true must be returned after the properly processing.

            ///When processing occurs, the sequence of operation is as follows:

                //An event should be fetched from the future event queue and processed. The processing to be done depends on the event type, ARRIVAL or TERMINATE.

                //An ARRIVAL event firstly cause the addition of a NEW process to the set of active processes. Then, depending on memory requestements and memory availability, the new process changes state to ACTIVE, SWAPPED or DISCARDED.
                
                //A TERMINATE event causes the associated process to change state to FINISHED. Then, because memory is released, some swapped-out processes can now be activated for execution. Processes in the SWP queue must be handled in order, but a previously swapped-out process should not prevent a later one from being activated.

            //Returns

                //true if one step was processed; false otherwise

        
        if (feqIsEmpty()){
            return false;
        }
        
        FutureEvent event = feqPop();

        // new process
        ForthcomingProcess* process = simGetProcess(event.pid);
        pctInsert(process->pid, process->arrivalTime, process->lifetime, &process->addressSpace);
        ProcessState state;
        // try allocate memory
        AddressSpaceMapping* space = memAlloc(process->pid, &process->addressSpace);
        fprintf (stderr, "space: %p\n", space);

        if(event.type == ARRIVAL){
            

            if(space == NULL_ADDRESS){
                // no memory available now
                state = SWAPPED;
                pctUpdateState(process->pid, state);
                // add to swap queue
                swpAdd(process->pid, &process->addressSpace);
                feqInsert(TERMINATE, process->arrivalTime + process->lifetime, process->pid);
                return true;
            }else if (space == IMPOSSIBLE_MAPPING) {
                // no memory available 
                state = DISCARDED;
                pctUpdateState(process->pid, state);
                feqInsert(TERMINATE, process->arrivalTime + process->lifetime, process->pid);
                return true;
            }else{
                // memory available 
                state = ACTIVE;
                
                pctUpdateState(process->pid, state, process->arrivalTime, pctGetAddressSpaceMapping(process->pid));
                feqInsert(TERMINATE, process->arrivalTime + process->lifetime, process->pid);
                return true;
            }

        }

        if (event.type == TERMINATE){
            ForthcomingProcess* process = simGetProcess(event.pid);
            pctInsert(process->pid, process->arrivalTime, process->lifetime, &process->addressSpace);
            pctUpdateState(process->pid, FINISHED, process->lifetime);
            memFree(space);
            feqInsert(TERMINATE, process->arrivalTime + process->lifetime, process->pid);
            return true;
        }
        return false;
    }

// ================================================================================== //

} // end of namespace group

