#include "UnitTest.h"

int main(int argc, char** argv)
{
	using namespace CppTester;

	TestSuite& suite = TestSuite::Get();

	suite.Add("Sum two integers", [] {
		int expected = 3;
		int a = 2, b = 1;

		int result = a + b;
		assert_equals(expected, result);
	});

	suite.Add("Booleans not equals", [] {
		bool expected = false;

		int result = true;
		assert_not_equals(expected, result);
	});

	suite.Add("Assert true", [] {
		int result = true;
		assert_true(result);
	});

	TestRunner_RunAllTests(suite);

	return 0;
}