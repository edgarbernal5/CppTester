#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>

namespace CppTester
{
	class TestSuite
	{
	public:
		typedef std::function<void()> TestCaseCallback;
		//using TestCaseCallback = void(*)();

		struct TestCase
		{
			std::string name;
			TestCaseCallback body;
		};

		static TestSuite& Get()
		{
			return g_testSuite;
		}

		void Add(std::string name, TestCaseCallback testCaseBody)
		{
			m_testCases.push_back(TestCase{ name, testCaseBody });
		}

		const std::vector<TestCase>& GetTestCases() const {
			return m_testCases;
		}
	private:
		static TestSuite g_testSuite;

		std::vector<TestCase> m_testCases;
	};
	TestSuite TestSuite::g_testSuite;

	void TestRunner_RunAllTests(TestSuite& testSuite) {
		std::cout << "Running test cases..." << std::endl << std::endl;

		for (auto& testCase : testSuite.GetTestCases()) {
			std::cout << "- Test case: " << testCase.name << std::endl;
			testCase.body();
		}

		std::cout << std::endl << "Test cases summary:" << std::endl;
	}

	template<typename First, typename Second>
	void assert_equals(First expected, Second result) {
		if (expected == result) {
			std::cout << "PASS" << std::endl;
			return;
		}

		std::cout << "Assert FAILS" << std::endl;
	}

	template<typename First, typename Second>
	void assert_not_equals(First expected, Second result) {
		if (expected != result) {
			std::cout << "PASS" << std::endl;
			return;
		}

		std::cout << "Assert FAILS" << std::endl;
	}

	void assert_true(bool condition) {
		if (condition) {
			std::cout << "PASS" << std::endl;
			return;
		}

		std::cout << "Assert FAILS" << std::endl;
	}

	void assert_false(bool condition) {
		if (!condition) {
			std::cout << "PASS" << std::endl;
			return;
		}

		std::cout << "Assert FAILS" << std::endl;
	}
}