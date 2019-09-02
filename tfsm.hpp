#pragma once

#include <type_traits>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

namespace tfsm
{



template<typename States, typename Inputs, typename Outputs>
class MealyMachine
{
	static_assert(std::is_enum<States>::value, "States must be an enum");
	static_assert(std::is_enum<Inputs>::value, "Inputs must be an enum");
	static_assert(std::is_enum<Outputs>::value, "Outputs must be an enum");

public:

	MealyMachine(std::vector<std::tuple<States, Inputs, Outputs, States>> switchVector, States initState)
	{
		std::transform(
					std::begin(switchVector),
					std::end(switchVector),
					std::inserter(_swtichMap, std::end(_swtichMap)),
					[](const std::tuple<States, Inputs, Outputs, States> &switchTuple)
		{
			return std::make_pair(std::tuple<States, Inputs>{std::get<0>(switchTuple), std::get<1>(switchTuple)}, std::tuple<Outputs, States>{std::get<2>(switchTuple), std::get<3>(switchTuple)});
		});
		int x;
		x = 0;
		x++;
	}



	States state() const
	{

	}



	Outputs impact(Inputs in)
	{

	}


private:
	std::map<std::tuple<States, Inputs>, std::tuple<Outputs, States>> _swtichMap;
	States _currentState;
};






}
