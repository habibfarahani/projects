#include <stdio.h>
#include <math.h>

class Clock
{
    public:
    Clock()
    {
        m_hr = 0;
        m_min = 0;
        m_sec = 0;
    }

    ~Clock()
    {

    }

    void tick()
    {
        if(m_sec >= 59)
        {
            m_sec = 0;
        }
        else
        {
            m_sec++;
        }


        if(m_min >= 59)
        {
            m_min = 0;
        }
        else
        {
            m_min = m_min + (1.0f/60.0f);
        }

        if(m_hr >= 11)
        {
            m_hr = 0;
        }
        else
        {
            m_hr = m_hr + (5.0f/3600.0f); 
        }

    }

    bool handlesAligned()
    {

return false;
    }

    void print()
    {
//        printf("%02d:%02d:%02d\n", (int)m_hr, (int)m_min, (int)m_sec );
        printf("%6.3f:%6.3f:%6.3f\n", m_hr, m_min, m_sec ); 
    }

    protected:
    float m_hr;
    float m_min;
    float m_sec;

};


int main(char *argv[], int argc)
{
   int i=0;
   Clock clock;

   while(i<9000)
   {
       clock.tick();

       clock.print();

       i++;
   }

    return 0;
}

