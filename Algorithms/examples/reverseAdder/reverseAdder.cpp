#include <stdio.h>


#include <vector>

using namespace std;


// Submit a working solution and we'll reach out to setup an interview. Correctness matters more than speed. We don't care how long you take.

// Write a function to add digits left to right AND carry the right digit rather than carrying the left digit.

// For example:

// 1 + 10 = 20 // Add digits left to right
// 51 + 51 = 12 // 5 + 5 = 10, so carry the right digit, 0, to get 0 + 1 + 1 = 2
// 99 + 99 = 126 // 9 + 9 = 18, carrying the 8, we get 8 + 9 + 9 = 26 for the rightmost digits


int fillIn(int num, vector<int> &numVec)
{
	int res = num / 10;

	if(num < 10)
	{
		numVec.push_back(num);
		return 0;
	}
	else
	{

		numVec.push_back(num % 10);
		if(0 != fillIn(res, numVec))
		{
			return -1;
		}

		return 0;

	}
}

int add(vector<int> &lhs, vector<int> &rhs, int carry)
{
	int sum = 0;

	if(lhs.size())
	{
//		printf("%d + ", lhs.back());
		sum += lhs.back();
		lhs.pop_back();
	}

	if(rhs.size())
	{
//		printf("%d ", rhs.back());
		sum += rhs.back();
		rhs.pop_back();
	}

//	printf("[%d] = ", carry);
	if(carry > 0)
	{
		return sum + carry;
	}

	return sum;
}

int getNum(const vector<int> &numVect)
{
	int tally = 0;

	for(size_t i=0; i<numVect.size(); i++)
	{
		tally *= 10;
		tally += numVect[i];
	}

	return tally;
}


// Fill in the code
int leftToRightAddition(int x, int y) {

	// vectors containig each element of input numbers
	vector<int> lhs;
	vector<int> rhs;

	// Fill in the vectors
	if( 0 == fillIn(x, lhs))
	{
		if(0 == fillIn(y, rhs))
		{
			// initialzie carry to -1 for no carry
			int carry = -1;
			// Vector containig the results
			vector<int> result;

			while((lhs.size()) || (rhs.size()))
			{
				// Add the two numbers, taking into account the carry
				int sum = add(rhs, lhs, carry);
				
				carry = -1;
				// Calculate the carry based on the new sum
				if(sum > 9)
				{
					carry = sum % 10;
					sum = sum / 10;
				}

				result.push_back(sum);
			}

			if(carry > -1)
			{
				result.push_back(carry);
			}

			printf("%d + %d = %d\n", x, y, getNum(result));
			return getNum(result);


		}

	}







}


int main(int argc, int *argv[])
{

	leftToRightAddition(987654, 4321);

	leftToRightAddition(1, 10);

	leftToRightAddition(99, 99);

	leftToRightAddition(51, 51);

	leftToRightAddition(1, 1);

	leftToRightAddition(1, 0);

	leftToRightAddition(5, 5);

}


