/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */
#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group
{

// ================================================================================== //

    void swpPrint(FILE *fout)
    {
        soProbe(403, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        try
        {
            fprintf(fout, "+===============================================+\n");
            fprintf(fout, "|             Swapped Process Queue             |\n");
            fprintf(fout, "+-------+---------------------------------------+\n");
            fprintf(fout, "|  PID  |         address space profile         |\n");
            fprintf(fout, "+-------+---------------------------------------+\n");

            SwpNode *current = swpHead;
            while (current != nullptr)
            {
                if (current->process.pid != 0)
                {
                    fprintf(fout, "| %5u |", current->process.pid);

                    AddressSpaceProfile profile = current->process.profile;

                    // Iterate over all segments, including empty ones up to 4 (or max segment count)
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        if (i > 0) fprintf(fout, " : ");

                        if (i < profile.segmentCount) {
                            if (i == 0){
                                fprintf(fout, "%8u", profile.size[i]);
                            }
                            else {
                                fprintf(fout, "%7u", profile.size[i]);
                            }
                        } else {
                            fprintf(fout, "  ---  ");
                        }
                    }

                    fprintf(fout, " |\n"); // Add trailing '|'
                }

                current = current->next;
            }
            fprintf(fout, "+===============================================+\n");
            fprintf(fout, "\n");
        }
        catch (const Exception &e)
        {
            throw; // Re-throw the caught exception
        }
    }

// ================================================================================== //

} // end of namespace group
