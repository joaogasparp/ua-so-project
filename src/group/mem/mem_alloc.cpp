/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    AddressSpaceMapping *memAlloc(uint32_t pid, AddressSpaceProfile *profile)
    {
        soProbe(504, "%s(%u, %p)\n", __func__, pid, profile);

        require(pid > 0, "process ID must be non-zero");
        require(profile != NULL, "profile must be a valid pointer to an AddressSpaceProfile variable");

        /* The mapping to be filled and whose pointer should be returned */
        static AddressSpaceMapping theMapping = {0, {0}};

        /* TODO POINT: Replace next instructions with your code */
        uint32_t totalRequiredMemory = 0;
        for (uint32_t i = 0; i < profile->segmentCount; ++i) {
            uint32_t roundedSize = ((profile->size[i] + memParameters.chunkSize - 1) / memParameters.chunkSize) * memParameters.chunkSize;
            totalRequiredMemory += roundedSize;

            if (totalRequiredMemory > (memParameters.totalSize - memParameters.kernelSize)) {
                return IMPOSSIBLE_MAPPING;
            }
        }

        theMapping.blockCount = 0;
        for (uint32_t i = 0; i < profile->segmentCount; ++i) {
            uint32_t roundedSize = ((profile->size[i] + memParameters.chunkSize - 1) / memParameters.chunkSize) * memParameters.chunkSize;

            Address alloc_address = (memParameters.policy == FirstFit) ? memFirstFitAlloc(pid, roundedSize) : memBuddySystemAlloc(pid, roundedSize);

            if (alloc_address == NULL_ADDRESS) {
                // Free previously allocated segments
                memFree(&theMapping);
                return NO_MAPPING;
            }

            theMapping.address[i] = alloc_address;
            theMapping.blockCount += 1;
        }

        return &theMapping;
    }

// ================================================================================== //

} // end of namespace group