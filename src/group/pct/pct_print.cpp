/*
 *  \author João Gaspar 107708 
 *  \author Joseane Pereira 107474
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

namespace group 
{

// ================================================================================== //

    void pctPrint(FILE *fout)
    {
        soProbe(303, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        if(fout == NULL){
            throw Exception(ENOSYS, __func__);
        }

        fprintf(fout, "+====================================================================================================================================================+\n");
        fprintf(fout, "|                                                                  Process Control Table                                                             |\n");
        fprintf(fout, "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n");
        fprintf(fout, "|  PID  |   state   | arrival | lifetime | active  | finish  |         address space profile         |             address space mapping             |\n");
        fprintf(fout, "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n");
        
        PctNode *current = pctHead;
        uint32_t maxBlocks = 4;

        current = pctHead;
        while (current != NULL) {
            fprintf(fout, "| %5u |", current->pcb.pid);
            fprintf(fout, " %-8s  |",pctGetStateAsString(current->pcb.pid));
            fprintf(fout, " %7u |", current->pcb.arrivalTime);
            fprintf(fout, " %8u |", current->pcb.lifetime);
            fprintf(fout, " %7u |", current->pcb.activationTime);
            if (strcmp(pctGetStateAsString(current->pcb.pid), "ACTIVE") == 0) {
                fprintf(fout, "   ---   |");
            } else {
                fprintf(fout, " %7u |", current->pcb.finishTime);
            }

            for (uint32_t j = 0; j < maxBlocks; ++j){
                if (j < current->pcb.memProfile.segmentCount) {
                    fprintf(fout, " %7u", current->pcb.memProfile.size[j]);
                } else {
                    fprintf(fout, "   ---  ");
                }
                if (j < maxBlocks - 1) {
                    fprintf(fout, " :");
                }
            }
            fprintf(fout, " |");

            for (uint32_t j = 0; j < maxBlocks; ++j){
                if (j < current->pcb.memMapping.blockCount) {
                    fprintf(fout, " 0x%07x", current->pcb.memMapping.address[j]);
                } else {
                    fprintf(fout, "    ---   ");
                }
                if (j < maxBlocks - 1) {
                    fprintf(fout, " :");
                }
            }
            fprintf(fout, " |\n");
            current = current->next;
        }

        fprintf(fout, "+====================================================================================================================================================+\n");
        fprintf(fout, "\n");
    }

// ================================================================================== //

} // end of namespace group

