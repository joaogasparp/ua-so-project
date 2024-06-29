/*
 *  \author João Rodrigues 108045
 *  \author Ricardo Dias 108598
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void swpAdd(uint32_t pid, AddressSpaceProfile *profile)
    {
        soProbe(404, "%s(%u, %p)\n", __func__, pid, profile);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        /* TODO POINT: Replace next instruction with your code */
        try
        {
            SwpNode *newNode = new SwpNode();
            newNode->process.pid = pid;
            newNode->process.profile = *profile;
            newNode->next = nullptr;

            if (swpHead == nullptr || swpTail == nullptr)
            {
                swpInit();
            }

            SwpNode *lastNode = swpTail;
            lastNode->next = newNode;
            swpTail = newNode;
        }
        catch (const std::exception &e)
        {
            throw Exception(ENOSYS, __func__);
        }

    }

// ================================================================================== //

} // end of namespace group