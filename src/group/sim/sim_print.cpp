/*
 *  \author João Gaspar 107708 
 *  \author Josane Pereira 107474
 */

#include "somm23.h"

#include <cstdint>
#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void simPrint(FILE *fout)
    {
        soProbe(103, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        fprintf(fout, "+====================================================================+\n");
        fprintf(fout, "|                          forthcomingTable                          |\n");
        fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");
        fprintf(fout, "|    Simulation step: %6u |              Simulation time: %7u |\n", stepCount, simTime);
        fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");
        fprintf(fout, "|  PID  | arrival | lifetime |         address space profile         |\n");
        fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");

        for (uint32_t i = 0; i < forthcomingTable.count; ++i)
        {
            uint32_t sizes[forthcomingTable.process[i].addressSpace.segmentCount];   
            fprintf(fout, "| %5u | %7u | %8u |", forthcomingTable.process[i].pid, forthcomingTable.process[i].arrivalTime, forthcomingTable.process[i].lifetime);
            
            for (uint32_t j = 0; j < 4; ++j) {
                if (j < forthcomingTable.process[i].addressSpace.segmentCount && forthcomingTable.process[i].addressSpace.size[j] != 0) {
                    sizes[j] = forthcomingTable.process[i].addressSpace.size[j];
                    fprintf(fout, " %7u", sizes[j]);
                } else {
                    fprintf(fout, "   ---  ");
                }
                if (j < 3) {
                    fprintf(fout, " :");
                }
            }
            fprintf(fout," |\n");            
        }

        fprintf(fout, "+====================================================================+\n");
        fprintf(fout, "\n");

    }

// ================================================================================== //

} // end of namespace group

