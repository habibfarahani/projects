#include <stdio.h>
#include "Job.h"
#include "Scheduler.h"


void Scheduler::print()
{
        std::map<std::string, Job *>::iterator it = m_jobs.begin();

        while(it != m_jobs.end())
        {
            it->second->print();
            it++;
        }
}

