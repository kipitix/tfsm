#pragma once

#include <type_traits>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <functional>

namespace tfsm
{



template<typename States, typename Inputs, typename Outputs>
class MealyMachine
{
	static_assert(std::is_enum<States>::value, "States must be an enum");
	static_assert(std::is_enum<Inputs>::value, "Inputs must be an enum");
	static_assert(std::is_enum<Outputs>::value, "Outputs must be an enum");

public:

	MealyMachine(std::vector<std::tuple<States, Inputs, Outputs, States>> switchVector,
				 States initState,
				 Outputs voidOutput,
				 std::function<void(Outputs, States)> observer = {})
	{
		std::transform(
					std::begin(switchVector),
					std::end(switchVector),
					std::inserter(_swtichMap, std::end(_swtichMap)),
					[](const std::tuple<States, Inputs, Outputs, States> &switchTuple)
		{
			return std::make_pair(std::tuple<States, Inputs>{std::get<0>(switchTuple), std::get<1>(switchTuple)}, std::tuple<Outputs, States>{std::get<2>(switchTuple), std::get<3>(switchTuple)});
		});

		_currentState = initState;

		_voidOutput = voidOutput;
		_lastOutput = _voidOutput;

		_observer = observer;
	}



	States currentState() const
	{
		return _currentState;
	}



	Outputs lastOutput() const
	{
		return _lastOutput;
	}



	Outputs impact(Inputs input)
	{
		auto it = _swtichMap.find(std::tuple<States, Inputs>{_currentState, input});

		if (it != std::end(_swtichMap))
		{
			auto switchRule = it->second;
			_lastOutput = std::get<0>(switchRule);
			_currentState = std::get<1>(switchRule);

			if (_observer)
			{
				_observer(_lastOutput, _currentState);
			}
		}
		else
		{
			_lastOutput = _voidOutput;
		}

		return _lastOutput;
	}


private:
	std::map<std::tuple<States, Inputs>, std::tuple<Outputs, States>> _swtichMap;

	States _currentState;

	Outputs _voidOutput;
	Outputs _lastOutput;

	std::function<void(Outputs, States)> _observer;
};




template<typename States, typename Inputs>
class MooreMachine
{
	static_assert(std::is_enum<States>::value, "States must be an enum");
	static_assert(std::is_enum<Inputs>::value, "Inputs must be an enum");

public:

	MooreMachine(std::vector<std::tuple<States, Inputs, States>> switchVector,
				 States initState,
				 std::function<void(States)> observer = {})
	{
		std::transform(
					std::begin(switchVector),
					std::end(switchVector),
					std::inserter(_swtichMap, std::end(_swtichMap)),
					[](const std::tuple<States, Inputs, States> &switchTuple)
		{
			return std::make_pair(std::tuple<States, Inputs>{std::get<0>(switchTuple), std::get<1>(switchTuple)}, std::get<2>(switchTuple));
		});

		_currentState = initState;

		_observer = observer;
	}



	States currentState() const
	{
		return _currentState;
	}



	States impact(Inputs input)
	{
		auto it = _swtichMap.find(std::tuple<States, Inputs>{_currentState, input});

		if (it != std::end(_swtichMap))
		{
			_currentState = it->second;

			if (_observer)
			{
				_observer(_currentState);
			}
		}

		return _currentState;
	}


private:
	std::map<std::tuple<States, Inputs>, States> _swtichMap;

	States _currentState;

	std::function<void(States)> _observer;
};

}
