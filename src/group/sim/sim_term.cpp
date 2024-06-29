/*
 *  \author Guilherme Santos 107961
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void simTerm() 
    {
        soProbe(102, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        pctTerm();
        //feqTerm();
        //swpTerm();
        //memTerm();

        forthcomingTable.count = 0;
        stepCount = 0;
        simTime = 0;
    }

// ================================================================================== //

} // end of namespace group

