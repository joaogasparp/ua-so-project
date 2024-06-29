/*
 *  \author João Gaspar 107708 
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    /*
     * \brief Init the module's internal data structure
     */
    void simInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy policy)
    {
        const char *pas = policy == FirstFit ? "FirstFit" : policy == BuddySystem ? "BuddySystem" : "Unkown";
        soProbe(101, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        forthcomingTable.count = 0;
        stepCount = 0;
        simTime = 0;

        pctInit();
        feqInit();
        swpInit();
        memInit(mSize, osSize, cSize, policy);
    }

// ================================================================================== //

} // end of namespace group

