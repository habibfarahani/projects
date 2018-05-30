#include <stdio.h>
#include "Job.h"

//////////////////////////////////////////////////////////////////////////////
//  Prints all the information about this job
//////////////////////////////////////////////////////////////////////////////
void Job::print()
{
    printf("id: %s [%d] => [ ", m_name.c_str(), m_completed);
//    for(size_t i=0; i<m_prerequisite.size(); i++)
//    {
//        printf("%s,", m_prerequisite[i]->getName().c_str());
//    }

    printf("]\n");  
}

