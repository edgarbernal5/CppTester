#include "UnitTest.h"

int main(int argc, char** argv)
{
	using namespace CppTester;

	TestSuite suite = TestSuite::Get();

	suite.Add("Sum two integers", [] {
		int expected = 4;
		int a = 2, b = 1;

		int result = a + b;
		assert_equals(expected, result);
	});

	TestRunner_RunAllTests(suite);

	return 0;
}