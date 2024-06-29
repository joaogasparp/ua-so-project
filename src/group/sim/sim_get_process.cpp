/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    ForthcomingProcess *simGetProcess(uint32_t pid)
    {
        soProbe(106, "%s(%u)\n", __func__, pid);

        require(pid > 0, "a valid process ID must be greater than zero");

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        for(uint32_t i = 0; i < forthcomingTable.count; ++i)
        {
            if(forthcomingTable.process[i].pid == pid)
                return &forthcomingTable.process[i];
        }

        throw Exception(ENOSYS, __func__);
        return NULL;
    }

// ================================================================================== //

} // end of namespace group

