/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group
{

// ================================================================================== //

    void memFree(AddressSpaceMapping *mapping) {
            soProbe(507, "%s(mapping: %p)\n", __func__, mapping);

            require(mapping != NULL, "mapping must be a valid pointer to an AddressSpaceMapping");

            try {
                for (uint32_t i = 0; i < mapping->blockCount; ++i) {
                    Address blockAddress = mapping->address[i];

                    if (memParameters.policy == FirstFit) {
                        memFirstFitFree(blockAddress);
                    } else if (memParameters.policy == BuddySystem) {
                        memBuddySystemFree(blockAddress);
                    }
                }
            } catch (Exception &e) {
                throw e; // Consider more specific error handling
            }

            // Optionally, after freeing all blocks, deallocate the mapping itself if dynamically allocated
            // delete mapping; // Uncomment if applicable
        }

// ================================================================================== //

} // end of namespace group