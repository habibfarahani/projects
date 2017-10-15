#include <stdio.h>
#include <math.h>


unsigned long long getFibonacciNum(const unsigned long long buffer[2])
{

    return (buffer[0] + buffer[1]);

}


bool isPrime(unsigned long long number)
{
    if(number <= 1)
    {
        return false;
    }
    
    if((number % 2 == 0) && (number > 2))
    {
        return false;
    }

    for(int i = 3; i < number; i += 2)
    {
        if(number % i == 0)
        {
            return false;
        }
    }

    return true;
    
}

int main(char *argv[], int argc)
{
    unsigned long long buffer[2] = {0, 1};
    unsigned long long currentNum;
    
    do{
        currentNum = getFibonacciNum(buffer);

        buffer[0] = buffer[1];
        buffer[1] = currentNum;


        if(isPrime(currentNum))
        {
            printf("BuzzFizz");
        }
        else
        {
            int printNum = 1;

            if((currentNum % 5) == 0)
            {
                printf("Fizz");
                printNum = 0;
            }

            if((currentNum % 3) == 0)
            {
                printf("Buzz");
                printNum = 0;
            }

            if(printNum)
            {
                printf("%llu", currentNum);
            }
        }

        printf("\n");


    }while(1);





    return 0;
}