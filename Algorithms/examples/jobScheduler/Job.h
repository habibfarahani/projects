#ifndef __JOBS__
#define __JOBS__

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

// dependencies = [('b', 'a'), ('c', 'a'), ('d', 'a'), ('e', 'd'), ('e', 'c')]

// scheduler = Scheduler(dependencies)
// scheduler.next_jobs() => ['a']
// scheduler.next_jobs('a') => ['b', 'c', 'd']
// scheduler.next_jobs('b') => []
// scheduler.next_jobs('c') => []
// scheduler.next_jobs('d') => ['e']
// scheduler.next_jobs('e') => []
// '''



class Job
{
    public:

    Job(std::string name)
    {
        m_name  = name;
        m_completed = false;
    }

    ~Job(){};


    std::string &getName()
    {
        return m_name;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  returns true only if all prerequisites have been executed (completed)
    //////////////////////////////////////////////////////////////////////////////
    bool preReqCompleted()
    {
        size_t i = 0;

        while(i < m_prerequisite.size())
        {
            if(!m_prerequisite[i]->isCompleted())
            {
                return false;
            }

            i++;
        }

        return true;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  returns true only if this job is ready to run.
    //      1. All prerequisites are complted.
    //      2. The job itself is not completed
    //////////////////////////////////////////////////////////////////////////////
    bool isReady()
    {
        if(!m_completed)
        {
            if(!m_prerequisite.size() || preReqCompleted())
            {
                return true;
            }
        }

        return false;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  Sets the completed flag of this job
    //////////////////////////////////////////////////////////////////////////////
    void completed(bool set)
    {
        m_completed = set;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  returns true if the job is completed
    //////////////////////////////////////////////////////////////////////////////
    bool isCompleted()
    {
        return m_completed;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  Adds a job as a prerequisite of the current job
    //////////////////////////////////////////////////////////////////////////////
    bool addPrereq(Job *pJob)
    {
        if(pJob)
        {
            m_prerequisite.push_back(pJob);

            return true;
        }

        return false;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  returns true only if pJob is a prequisite for this job instance
    //////////////////////////////////////////////////////////////////////////////
    bool isPrereq(Job *pJob)
    {
        bool found = false;
        if(pJob)
        {
            size_t i=0;
            while((i<m_prerequisite.size()) && (!found))
            {
                if(pJob->getName() == m_prerequisite[i]->getName())
                {
                    found = true;
                }
                i++;
            }
        }

        return found;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  Prints all the information about this job
    //////////////////////////////////////////////////////////////////////////////
    void print();
    protected:
    std::string m_name;
    bool          m_completed;
    std::vector <Job *> m_prerequisite;
};



#endif  // __JOBS__