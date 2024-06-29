/*
 *  \author ...
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group
{
    // Helper function to print the linked list
    void memPrintList(FILE *fout, MemListNode *head)
    {
        if (head == nullptr)
        {
            fprintf(fout, "|   ---   |     ---     |     ---    |\n");
        }
        else
        {
            MemListNode *current = head;
            while (current != nullptr)
            {
                if (current->block.size != 0)
                {
                    if (current->block.pid == 0) // If PID is 0, it's a free block
                    {
                        fprintf(fout, "|   ---   |   0x%X |   %u   |\n",
                                current->block.address,
                                current->block.size);
                    }
                    else
                    {
                        fprintf(fout, "|    %u    |   0x%X |   %u   |\n",
                                current->block.pid,
                                current->block.address,
                                current->block.size);
                    }
                }
                current = current->next;
            }
        }
    }

    void memPrint(FILE *fout)
    {
        soProbe(503, "%s(\"%p\")\n", __func__, fout);
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        // Print occupied blocks
        fprintf(fout, "+====================================+\n");
        fprintf(fout, "|   FirstFit memory occupied blocks  |\n");
        fprintf(fout, "+---------+-------------+------------+\n");
        fprintf(fout, "|   PID   |   address   |    size    |\n");
        fprintf(fout, "+---------+-------------+------------+\n");
        memPrintList(fout, memOccupiedHead);
        fprintf(fout, "+====================================+\n");
        fprintf(fout, "\n");

        // Print free blocks
        fprintf(fout, "+====================================+\n");
        fprintf(fout, "|     FirstFit memory free blocks    |\n");
        fprintf(fout, "+---------+-------------+------------+\n");
        fprintf(fout, "|   PID   |   address   |    size    |\n");
        fprintf(fout, "+---------+-------------+------------+\n");
        memPrintList(fout, memFreeHead);
        fprintf(fout, "+====================================+\n");
        fprintf(fout, "\n");
    }
} // end of namespace group