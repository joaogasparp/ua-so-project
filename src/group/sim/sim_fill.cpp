/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708
 */

#include "somm23.h"
#include <unistd.h>

namespace group
{

// ================================================================================== //

    void simRandomFill(uint32_t n, uint32_t seed)
    {
        soProbe(105, "%s(%u, %u)\n", __func__, n, seed);

        require(n == 0 or n >= 2, "At least 2 processes are required");
        require(n <= MAX_PROCESSES, "More than MAX_PROCESSES processes not allowed");

        /* TODO POINT: Replace next instruction with your code */
        //  throw Exception(ENOSYS, __func__);

        if(n == 0){
            n = rand() % MAX_PROCESSES + 2;
        }
            forthcomingTable.count = n;

        if(seed == 0){
            seed = getpid();
        }

        srand(seed);

    	uint32_t arrivalTime = 0;
        for(uint32_t i = 0; i < n; ++i){
            uint32_t pid = rand() % 65535 + 1;
            uint32_t t = 1;
            while(!t){
                t = 1;
                for(uint32_t k = 0; k < i; k++){
                    if(forthcomingTable.process[k].pid == pid){
                        t = 0;
                        pid = rand() % 65535 + 1;
                    }
                }
            }

            forthcomingTable.process[i].pid = pid;

            arrivalTime += rand() % 101;
            forthcomingTable.process[i].arrivalTime = arrivalTime;

            forthcomingTable.process[i].lifetime = rand() % 991 + 10;

            forthcomingTable.process[i].addressSpace.segmentCount = rand() % MAX_SEGMENTS + 1;

            for (uint32_t j = 0; j < forthcomingTable.process[j].addressSpace.segmentCount; ++j){
                forthcomingTable.process[i].addressSpace.size[j] = rand() % 1793 + 256; 
            }

        }
    }

// ================================================================================== //

} // end of namespace group

