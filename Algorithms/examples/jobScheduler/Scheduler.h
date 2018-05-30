#ifndef __SCHDULER__
#define __SCHDULER__

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "Job.h"

struct JobTuple
{
    std::string next;
    std::string completed;
};



class Scheduler{

    public:
    Scheduler()
    {
        m_bInitialized = true;
    }
    
    Scheduler(std::vector <JobTuple> jobList)
    {
        m_bInitialized = true;
        for(size_t i=0; i<jobList.size(); i++ )
        {
            if(createJob(jobList[i].completed) && 
                createJob(jobList[i].next))
                {
                    if(false == addPrereq(jobList[i].next, jobList[i].completed))
                    {
                        m_bInitialized = false;
                    }
                }
        }
    }
    ~Scheduler(){}

    void print();

    std::vector< std::string> &next_job()
    {
        std::string empty;
        return next_job(empty);
    }


    std::vector< std::string> &next_job(std::string jodId)
    {
        Job *jobToRun = getJob(jodId);

        m_nextJobs.clear();

        if(jobToRun)
        {
            if(jobToRun)
            {
                jobToRun->completed(true);
                m_nextJobs.push_back(jobToRun->getName());

                std::map<std::string, Job *>::iterator it = m_jobs.begin();

                while(it != m_jobs.end())// && (readyJob == NULL))
                {
                    Job *jobToCheck = it->second;
                    if((jobToCheck->getName() != jobToRun->getName()) && (jobToCheck->isPrereq(jobToRun)) && (jobToCheck->isReady()))
                    {
                        m_nextJobs.push_back(jobToCheck->getName());
                    }

                    it++;
                }
            }
        }
        return m_nextJobs;
    }

    protected:



    bool createJob(std::string &name)
    {
        if(m_jobs.empty() || (m_jobs.find(name) == m_jobs.end()))
        {
            Job *newJob = new Job(name);
            if(!newJob)
            {
                return false;
            }
            m_jobs.insert(std::pair<std::string, Job *>(name, newJob));
       }
        return true;
    }

    bool addPrereq(std::string &jobId, std::string &preReqId)
    {
        std::map<std::string, Job *>::iterator it = m_jobs.find(jobId);

        if(it != m_jobs.end())
        {
            it->second->addPrereq(m_jobs.find(preReqId)->second);
        }

        return false;
    }

    Job *getJob(std::string jobId)
    {
        Job *readyJob = NULL;

        if(jobId.size())
        {
            std::string jobName = jobId;

            std::map<std::string, Job *>::iterator it = m_jobs.find(jobName);
            if(it != m_jobs.end())
            {
                readyJob = it->second;
            }
        }
        else
        {
            std::map<std::string, Job *>::iterator it = m_jobs.begin();

            while(it != m_jobs.end() && (readyJob == NULL))
            {
                if(it->second->isReady())
                {
                    readyJob = it->second;
                }

                it++;
            }
        }        
        return readyJob;
    }

    

    bool m_bInitialized;
    std::map<std::string, Job *> m_jobs;
    std::vector<std::string > m_nextJobs;


};


#endif //__SCHDULER__