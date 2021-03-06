#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Action.hpp"
#include "FiniteAction.hpp"
#include "InstantAction.hpp"
#include "RepeatingAction.hpp"

class FiniteTestAction : public FiniteAction
{
public:
	FiniteTestAction(float duration) :
		FiniteAction("FiniteTestAction", duration)
	{}
	~FiniteTestAction() {}

	void update() {}
};

class InstantTestAction : public InstantAction
{
public:
	InstantTestAction() :
		InstantAction("InstantTestAction")
	{}
	~InstantTestAction() {}

	void update() {}
};

class RepeatingTestAction : public RepeatingAction
{
public:
	RepeatingTestAction() :
		RepeatingAction("RepeatingTestAction", 10)
	{}
	~RepeatingTestAction() {};

	void update() {}
};

TEST_CASE("Standard Action", "[standard][construction]")
{
	FiniteTestAction test(10.f);

	REQUIRE(test.name() == "FiniteTestAction");
	REQUIRE(test.status() == ActionStatus::FRESH);
}

TEST_CASE("Finite Action", "[finite][construction]")
{
	FiniteTestAction test(10.f);
	Node node;

	SECTION("Time elapses grows each step by delta")
	{
		test.execute(&node);
		test.step(5);

		REQUIRE(test.timeElapsed() == 5);
		REQUIRE(test.status() == ActionStatus::RUNNING);

		test.step(5);

		REQUIRE(test.timeElapsed() == 10);
		REQUIRE(test.status() == ActionStatus::SUCCEEDED);
		REQUIRE(test.isDone() == true);

		test.step(5);

		REQUIRE(test.timeElapsed() == 10);
	}
}

TEST_CASE("Instant Action", "[instant][construction]")
{
	InstantTestAction test;
	Node node;

	SECTION("Instant actions succeed after first step")
	{
		test.execute(&node);
		REQUIRE(test.status() == ActionStatus::RUNNING);

		test.step(5);
		REQUIRE(test.status() == ActionStatus::SUCCEEDED);
		REQUIRE(test.isDone() == true);
	}
}

TEST_CASE("Repeating Action", "[repeating][construction]")
{
	RepeatingTestAction test;
	Node node;

	SECTION("Repeating action never stops!")
	{
		test.execute(&node);
		test.step(6);

		REQUIRE(test.timeElapsed() == 6);
		REQUIRE(test.status() == ActionStatus::RUNNING);

		test.step(5);

		REQUIRE(test.timeElapsed() == 1);
		REQUIRE(test.status() == ActionStatus::RUNNING);
		REQUIRE(test.repeatCount() == 1);
	}
}
