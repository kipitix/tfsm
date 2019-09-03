#include <QtTest>

// add necessary includes here

#include "tfsm.hpp"



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
	Y2,
	YV = -1
};



class tfsm_tests : public QObject
{
	Q_OBJECT

public:
	tfsm_tests();
	~tfsm_tests();

private slots:
	void mealy_init();
	void mealy_impact();
	void mealy_observer();

	void moore_init();
	void moore_impact();
	void moore_observer();
};



tfsm_tests::tfsm_tests()
{

}



tfsm_tests::~tfsm_tests()
{

}



void tfsm_tests::mealy_init()
{
	tfsm::MealyMachine<S, X, Y> mm
	{
		{
			{S::S0, X::X1, Y::Y1, S::S1},
			{S::S1, X::X2, Y::Y2, S::S2},
			{S::S2, X::X0, Y::Y0, S::S0}
		},
		S::S0,
				Y::YV
	};

	QCOMPARE(mm.currentState(), S::S0);
	QCOMPARE(mm.lastOutput(), Y::YV);
}



void tfsm_tests::mealy_impact()
{
	tfsm::MealyMachine<S, X, Y> mm
	{
		{
			{S::S0, X::X1, Y::Y1, S::S1},
			{S::S1, X::X2, Y::Y2, S::S2},
			{S::S1, X::X0, Y::Y0, S::S0},
			{S::S2, X::X0, Y::Y0, S::S0}
		},
		S::S0,
				Y::YV
	};

	QCOMPARE(mm.currentState(), S::S0);
	QCOMPARE(mm.lastOutput(), Y::YV);



	{ // NO SWITCH
		auto output = mm.impact(X::X0);

		QCOMPARE(output, Y::YV);
		QCOMPARE(mm.currentState(), S::S0);
		QCOMPARE(mm.lastOutput(), Y::YV);
	}

	{ // NO SWITCH
		auto output = mm.impact(X::X2);

		QCOMPARE(output, Y::YV);
		QCOMPARE(mm.currentState(), S::S0);
		QCOMPARE(mm.lastOutput(), Y::YV);
	}

	{ // SWITCH !!!
		auto output = mm.impact(X::X1);

		QCOMPARE(output, Y::Y1);
		QCOMPARE(mm.currentState(), S::S1);
		QCOMPARE(mm.lastOutput(), Y::Y1);
	}



	{ // NO SWITCH
		auto output = mm.impact(X::X1);

		QCOMPARE(output, Y::YV);
		QCOMPARE(mm.currentState(), S::S1);
		QCOMPARE(mm.lastOutput(), Y::YV);
	}

	{ // SWITCH !!!
		auto output = mm.impact(X::X2);

		QCOMPARE(output, Y::Y2);
		QCOMPARE(mm.currentState(), S::S2);
		QCOMPARE(mm.lastOutput(), Y::Y2);
	}

	{ // SWITCH !!!
		auto output = mm.impact(X::X0);

		QCOMPARE(output, Y::Y0);
		QCOMPARE(mm.currentState(), S::S0);
		QCOMPARE(mm.lastOutput(), Y::Y0);
	}

	{ // SWITCH !!!
		auto output = mm.impact(X::X1);

		QCOMPARE(output, Y::Y1);
		QCOMPARE(mm.currentState(), S::S1);
		QCOMPARE(mm.lastOutput(), Y::Y1);
	}

	{ // SWITCH !!!
		auto output = mm.impact(X::X0);

		QCOMPARE(output, Y::Y0);
		QCOMPARE(mm.currentState(), S::S0);
		QCOMPARE(mm.lastOutput(), Y::Y0);
	}
}



void tfsm_tests::mealy_observer()
{
	Y targetOutput = Y::Y0;
	S targetState = S::S0;

	tfsm::MealyMachine<S, X, Y> mm
	{
		{
			{S::S0, X::X1, Y::Y1, S::S1},
			{S::S1, X::X2, Y::Y2, S::S2},
			{S::S2, X::X0, Y::Y0, S::S0}
		},
		S::S0,
		Y::YV,
		[&](Y y, S s)
		{
			QCOMPARE(y, targetOutput);
			QCOMPARE(s, targetState);
		}
	};

	QCOMPARE(mm.currentState(), S::S0);
	QCOMPARE(mm.lastOutput(), Y::YV);

	targetOutput = Y::Y1;
	targetState = S::S1;
	mm.impact(X::X1);

	targetOutput = Y::Y2;
	targetState = S::S2;
	mm.impact(X::X2);

	targetOutput = Y::Y0;
	targetState = S::S0;
	mm.impact(X::X0);
}



void tfsm_tests::moore_init()
{
	tfsm::MooreMachine<S, X> mm
	{
		{
			{S::S0, X::X1, S::S1},
			{S::S1, X::X2, S::S2},
			{S::S1, X::X0, S::S0},
			{S::S2, X::X0, S::S0}
		},
		S::S0
	};

	QCOMPARE(mm.currentState(), S::S0);
}



void tfsm_tests::moore_impact()
{
	tfsm::MooreMachine<S, X> mm
	{
		{
			{S::S0, X::X1, S::S1},
			{S::S1, X::X2, S::S2},
			{S::S1, X::X0, S::S0},
			{S::S2, X::X0, S::S0}
		},
		S::S0
	};

	QCOMPARE(mm.currentState(), S::S0);



	{ // NO SWITCH
		auto state = mm.impact(X::X0);

		QCOMPARE(state, S::S0);
		QCOMPARE(mm.currentState(), S::S0);
	}

	{ // NO SWITCH
		auto state = mm.impact(X::X2);

		QCOMPARE(state, S::S0);
		QCOMPARE(mm.currentState(), S::S0);
	}

	{ // SWITCH !!!
		auto state = mm.impact(X::X1);

		QCOMPARE(state, S::S1);
		QCOMPARE(mm.currentState(), S::S1);
	}



	{ // NO SWITCH
		auto state = mm.impact(X::X1);

		QCOMPARE(state, S::S1);
		QCOMPARE(mm.currentState(), S::S1);
	}

	{ // SWITCH !!!
		auto state = mm.impact(X::X2);

		QCOMPARE(state, S::S2);
		QCOMPARE(mm.currentState(), S::S2);
	}

	{ // SWITCH !!!
		auto state = mm.impact(X::X0);

		QCOMPARE(state, S::S0);
		QCOMPARE(mm.currentState(), S::S0);
	}

	{ // SWITCH !!!
		auto state = mm.impact(X::X1);

		QCOMPARE(state, S::S1);
		QCOMPARE(mm.currentState(), S::S1);
	}

	{ // SWITCH !!!
		auto state = mm.impact(X::X0);

		QCOMPARE(state, S::S0);
		QCOMPARE(mm.currentState(), S::S0);
	}
}



void tfsm_tests::moore_observer()
{
	S targetState = S::S0;

	tfsm::MooreMachine<S, X> mm
	{
		{
			{S::S0, X::X1, S::S1},
			{S::S1, X::X2, S::S2},
			{S::S2, X::X0, S::S0}
		},
		S::S0,
		[&](S s)
		{
			QCOMPARE(s, targetState);
		}
	};

	QCOMPARE(mm.currentState(), S::S0);

	targetState = S::S1;
	mm.impact(X::X1);

	targetState = S::S2;
	mm.impact(X::X2);

	targetState = S::S0;
	mm.impact(X::X0);
}



QTEST_APPLESS_MAIN(tfsm_tests)

#include "tst_tfsm.moc"
