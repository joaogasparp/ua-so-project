/*
 *  \author Joseane Pereira 107474
 *  \author Gonçalo Oliveira 108405
 *  \author João Gaspar 107708
*/

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void feqPrint(FILE *fout) {
        soProbe(203, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL && fileno(fout) != -1, "fout must be a valid file stream");

        if (feqHead == NULL) {
            fprintf(fout, "+==============================+\n");
            fprintf(fout, "|      Future Event Queue      |\n");
            fprintf(fout, "+----------+-----------+-------+\n");
            fprintf(fout, "|   time   |   type    |  PID  |\n");
            fprintf(fout, "+----------+-----------+-------+\n");
            fprintf(fout, "+==============================+\n");
            return;
        }

        fprintf(fout, "+==============================+\n");
        fprintf(fout, "|      Future Event Queue      |\n");
        fprintf(fout, "+----------+-----------+-------+\n");
        fprintf(fout, "|   time   |   type    |  PID  |\n");
        fprintf(fout, "+----------+-----------+-------+\n");

        FeqEventNode *current = feqHead;
        while (current != NULL) {
            const char *tas = current->event.type == ARRIVAL ? "ARRIVAL" : "TERMINATE";
            fprintf(fout, "| %8u | %-9s | %5u |\n", current->event.time, tas, current->event.pid);
            current = current->next;
        }

        fprintf(fout, "+==============================+\n");
        fprintf(fout, "\n");
    }

// ================================================================================== //

} // end of namespace group

