#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace CppTester
{
	typedef std::function<void()> TestCaseCallback;
	//using TestCaseCallback = void(*)();

	class TestFailure : std::exception
	{
	public:
		TestFailure(const char* message)
		{
			std::ostringstream builder;
			builder << "Details => " << message;
			m_message = builder.str();
		}
		
		char const* what() const override
		{
			
			return m_message.c_str();
		}

	private:
		std::string m_message;
	};

	class TestRunner;

	class TestSuite
	{
	public:
		struct TestCase
		{
			std::string name;
			TestCaseCallback body;
		};

		static TestSuite& Get() { 
			static TestSuite g_testSuite;
			return g_testSuite;
		}

		void Add(std::string name, TestCaseCallback testCaseBody)
		{
			m_testCases.push_back(TestCase{ name, testCaseBody });
		}

		friend class TestRunner;
	private:

		std::vector<TestCase> m_testCases;

		const std::vector<TestCase>& GetTestCases() const { return m_testCases; }
	};

	class TestRunner
	{
	public:
		void RunAllTests(TestSuite& testSuite) {
			std::cout << "Running test cases..." << std::endl << std::endl;

			int testCasesFailures = 0;
			auto testsCases = testSuite.GetTestCases();
			for (auto& testCase : testsCases)
			{
				std::cout << "- Test case: " << testCase.name << std::endl;
				try {
					testCase.body(); 
					std::cout << "PASS." << std::endl << std::endl;
				}
				catch (TestFailure failureException) {
					std::cout << "FAILURE: " << failureException.what() << std::endl << std::endl;
					++testCasesFailures;
				}
			}

			std::cout << "Test cases summary:" << std::endl;
			std::cout << "- PASSED: " << (testsCases.size() - testCasesFailures) << std::endl;
			std::cout << "- FAILURES: " << testCasesFailures << std::endl;
		}
	};

	template<typename First, typename Second>
	void assert_equals(First expected, Second result) {
		if (expected == result) {
			return;
		}

		//std::cout << "Assert FAILS" << std::endl;
		throw TestFailure("Assert equals FAILS.");
	}

	template<typename First, typename Second>
	void assert_not_equals(First expected, Second result) {
		if (expected != result) {
			return;
		}

		//std::cout << "Assert FAILS" << std::endl;
		throw TestFailure("Assert not equals FAILS.");
	}

	void assert_true(bool condition) {
		if (condition) {
			return;
		}

		//std::cout << "Assert FAILS" << std::endl;
		throw TestFailure("Assert true FAILS.");
	}

	void assert_false(bool condition) {
		if (!condition) {
			return;
		}

		//std::cout << "Assert FAILS" << std::endl;
		throw TestFailure("Assert false FAILS.");
	}
}