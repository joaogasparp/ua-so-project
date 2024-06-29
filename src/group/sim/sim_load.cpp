/*
 *  \author Guilherme Santos 107961
 *  \author João Gaspar 107708 
 *  \author Josane Pereira 107474
 */
 

#include "somm23.h"
#include <cstring>


namespace group
{

// ================================================================================== //

    void simLoad(const char *fname)
    {
        soProbe(104, "%s(\"%s\")\n", __func__, fname);

        require(fname != NULL, "fname can not be a NULL pointer");
        require(forthcomingTable.count == 0, "Forthcoming table should be empty");

        /* TODO POINT: Replace next instruction with your code */
        /* throw Exception(ENOSYS, __func__); */

        FILE *file = fopen(fname, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            throw Exception(errno, __func__);
        }

        char line[256];
        uint32_t lineNumber = 0;

        while (fgets(line, sizeof(line), file) != NULL)
        {
            lineNumber++;

            if (line[0] == '%' || line[0] == '\n')
                continue;

            uint32_t pid, arrivalTime, lifetime;
            char segmentCountStr[256];

            int result = sscanf(line, "%u;%u;%u;%s", &pid, &arrivalTime, &lifetime, segmentCountStr);
            if (result != 4)
            {
                fprintf(stderr, "Error parsing line %u: Invalid format\n", lineNumber);
                throw Exception(EINVAL, __func__);
            }

            for (uint32_t i = 0; i < forthcomingTable.count; ++i)
            {
                if (forthcomingTable.process[i].pid == pid)
                {
                    fprintf(stderr, "Error parsing line %u: Duplicate PID\n", lineNumber);
                    throw Exception(EINVAL, __func__);
                }
            }

            if (forthcomingTable.count > 0 && arrivalTime < forthcomingTable.process[forthcomingTable.count - 1].arrivalTime)
            {
                fprintf(stderr, "Error parsing line %u: Arrival times must be in ascending order\n", lineNumber);
                throw Exception(EINVAL, __func__);
            }

            if (lifetime <= 0)
            {
                fprintf(stderr, "Error parsing line %u: Lifetime must be greater than zero\n", lineNumber);
                throw Exception(EINVAL, __func__);
            }

            forthcomingTable.process[forthcomingTable.count].pid = pid;
            forthcomingTable.process[forthcomingTable.count].arrivalTime = arrivalTime;
            forthcomingTable.process[forthcomingTable.count].lifetime = lifetime;

            int segmentCount = 0;
            
            const char outer_delimiters[] = ";";
            const char inner_delimiters[] = ",";
 
            char* token;
            char* outer_saveptr = NULL;
            char* inner_saveptr = NULL;
            
            token = strtok_r(line, outer_delimiters, &outer_saveptr);
    
            int counter = 0; 
            int cnt = 0;   
            while (token != NULL)
            {
                cnt = 0;
                char* inner_token = strtok_r(token, inner_delimiters, &inner_saveptr);
                
                segmentCount++;
                if (segmentCount > MAX_SEGMENTS)
                {
                    fprintf(stderr, "Error parsing line %u: Exceeded maximum segment count\n", lineNumber);
                    throw Exception(EINVAL, __func__);
                }

                if (counter >= 3){
                    while (inner_token != NULL){
                        
                        int size = atoi(inner_token);
                        inner_token = strtok_r(NULL, inner_delimiters, &inner_saveptr);
                        forthcomingTable.process[forthcomingTable.count].addressSpace.size[cnt] = size;
                        cnt++;
                    }
                }
                

                token = strtok_r(NULL, outer_delimiters, &outer_saveptr);  
                counter++;         
            }
            forthcomingTable.process[forthcomingTable.count].addressSpace.segmentCount = segmentCount;

            forthcomingTable.count++;
        }

        fclose(file);
    }

// ================================================================================== //

} // end of namespace group

