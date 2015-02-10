#include "lexical_cast.hpp"

#include <tut/tut.hpp>
#include <tut/tut_main.hpp>
#include <tut/tut_xml_reporter.hpp>

#include <exception>
#include <iostream>

namespace tut
{

	struct test
	{
		virtual ~test()
		{
		}
	};

	typedef test_group<test> tf;
	typedef tf::object object;
	tf fail_test("test()");

	template<>
	template<>
	void object::test<1>()
	{
		set_test_name("char* -> int");
		ensure_equals(lexical_cast<int>("0"), 0);
		ensure_equals(lexical_cast<int>("-0"), 0);
		ensure_equals(lexical_cast<int>(" 100 "), 100);
		ensure_equals(lexical_cast<int>("2147483647"), 2147483647);
		ensure_equals(lexical_cast<int>("-2147483647"), -2147483647);
	}
	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("string -> int");
		ensure_equals(lexical_cast<int>(std::string("0")), 0);
		ensure_equals(lexical_cast<int>(std::string("-0")), 0);
		ensure_equals(lexical_cast<int>(std::string(" 100 ")), 100);
		ensure_equals(lexical_cast<int>(std::string("2147483647")), 2147483647);
		ensure_equals(lexical_cast<int>(std::string("-2147483647")), -2147483647);
	}

	template<>
	template<>
	void object::test<3>()
	{
		set_test_name("same type");
		ensure_equals(lexical_cast<int>(10), 10);
		ensure_equals(lexical_cast<float>(10.0f), 10.0f);
		ensure_equals(lexical_cast<std::string>(std::string("ABc")), "ABc");
	}

	template<>
	template<>
	void object::test<4>()
	{
		set_test_name("int -> string");
		ensure_equals(lexical_cast<std::string>(123456789), "123456789");
		ensure_equals(lexical_cast<std::string>(-123456789), "-123456789");
	}

	template<>
	template<>
	void object::test<5>()
	{
		set_test_name("float -> string");
		ensure_equals(lexical_cast<std::string>(1.23423), "1.23423000");
		ensure_equals(lexical_cast<std::string>(-1.23423), "-1.23423000");
		ensure_equals(lexical_cast<std::string>(0.000001), "0.00000100");
		ensure_equals(lexical_cast<std::string>(-0.000001), "-0.00000100");
		ensure_equals(lexical_cast<std::string>(1.23423e15), "1.234230e+015");
		ensure_equals(lexical_cast<std::string>(-1.23423e15), "-1.234230e+015");
	}


	test_runner_singleton runner;
}

int main(int argc, const char *argv[])
{
	using namespace std;
	tut::console_reporter reporter;
	tut::runner.get().set_callback(&reporter);

	try
	{
		if (tut::tut_main(argc, argv))
		{
			if (reporter.all_ok())
			{
				return 0;
			}
			else
			{
				std::cerr << "\nFAILURE and EXCEPTION in these tests are FAKE ;)" << std::endl;
			}
		}
	}
	catch (const tut::no_such_group &ex)
	{
		std::cerr << "No such group: " << ex.what() << std::endl;
	}
	catch (const tut::no_such_test &ex)
	{
		std::cerr << "No such test: " << ex.what() << std::endl;
	}
	catch (const tut::tut_error &ex)
	{
		std::cout << "General error: " << ex.what() << std::endl;
	}

	return 0;
}
