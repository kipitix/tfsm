#include <iostream>

#include "tfsm.hpp"

using namespace std;



enum class S
{
	S0 = 0,
	S1,
	S2
};



enum class X
{
	X0 = 0,
	X1,
	X2
};



enum class Y
{
	Y0 = 0,
	Y1,
	Y2
};



int main()
{
	tfsm::MealyMachine<S, X, Y> mm
	{
		{
			{S::S0, X::X0, Y::Y0, S::S0},
			{S::S0, X::X0, Y::Y0, S::S0},
			{S::S0, X::X0, Y::Y0, S::S0},
		},
		S::S0
	};

	return 0;
}
