#include <stdio.h>
#include <math.h>
#include "Scheduler.h"





std::vector <JobTuple> jobsVect = {{"b", "a"},
                               {"c","a"},
                               {"d", "a"},
                               {"e", "c"},
                               {"e", "d"}
                               };


Scheduler scheduler(jobsVect);

static bool startup = true;
bool runJobs(std::string jobName);
bool runJobs()
{
    std::string empty;
    return runJobs(empty);
}


bool runJobs(std::string jobName)
{
    std::vector <std::string> next_jobs;

    if(startup)
    {
        next_jobs = scheduler.next_job();
        startup = false;
     }
    else
    {
        next_jobs = scheduler.next_job(jobName);
    }
 
    if(next_jobs.size() > 0)
    {
        printf("%s => [", next_jobs[0].c_str());
        for(size_t i=1; i<next_jobs.size(); i++  )
        {
            printf("%s,", next_jobs[i].c_str());
        }
        printf("]\n");

        for(size_t i=1; i<next_jobs.size(); i++  )
        {
            runJobs(next_jobs[i]);
        }

        return true;
    }


    return false;
}


int main(int argc, char *argv[])
{
    std::vector <std::string> next_jobs;

 

//    scheduler.print();

    runJobs();

    return 0;
}

