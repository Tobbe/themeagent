#include "RCFile.h"
#include <UnitTest++.h>

SUITE(RCFile)
{
	TEST(Constructor)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");
		CHECK(rc.lines() == 13);
	}

	TEST(Get)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.get("settingone") == "uno");
		CHECK(rc.get("doesntexist") == "");
		CHECK(rc.get("settingFour") == "red green blue");
		CHECK(rc.get("settingQuote") == "\"");
	}

	TEST(IsSet)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.isSet("doesntexist") == false);
		CHECK(rc.isSet("settingone") == true);
		CHECK(rc.isSet("settingSix") == true);
	}

	TEST(GetMultiple)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.getMultiple("settingOne") == "uno");

		// Should reset settingOne counter when we reach the end of the 
		// settings with that name
		CHECK(rc.getMultiple("settingOne") == ""); 
		CHECK(rc.getMultiple("settingOne") == "uno");

		// Should reset settingOne's counter as soon as we access some other
		// setting
		CHECK(rc.getMultiple("doesntexist") == ""); 
		CHECK(rc.getMultiple("settingOne") == "uno");
		CHECK(rc.getMultiple("settingOne") == ""); 

		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
		CHECK(rc.getMultiple("*test") == "cout << \"text to standard output\" << endl;");
		CHECK(rc.getMultiple("*test") == "fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)");
		CHECK(rc.getMultiple("*test") == "");
		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
	}

	TEST(isTrue)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.isTrue("settingSix"));
		CHECK(rc.isTrue("settingTrue"));
		CHECK(rc.isTrue("settingFalse") == false);
	}

	TEST(CommentsInFile)
	{
		RCFile rc("TestFiles//RCFiles//comments.rc");

		CHECK(rc.lines() == 7);
		CHECK(rc.get("settingSet") == "");
		CHECK(rc.isTrue("settingTrue"));
		CHECK(rc.isSet(";EOF") == false);
	}

	TEST(ExpandEvars)
	{
		RCFile rc("TestFiles//RCFiles//advanced.rc");

		CHECK(rc.get("TestEvar") == "testing");
		CHECK(rc.get("EvarValue") == "testing");
		CHECK(rc.get("EvarValue2") == "testingtesting");
		CHECK(rc.get("EvarValue3") == "Testing testing");
		CHECK(rc.get("EvarValue4") == "Foo Bar");
		CHECK(rc.get("EvarValue5") == "Foo Bar Foo");
		CHECK(rc.get("EvarValue6") == "Test testingTestEvar Test");
	}

	TEST(IncludeFiles)
	{
		RCFile rc("TestFiles//RCFiles//advanced.rc");

		CHECK(rc.get("settingone") == "uno");
		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
		CHECK(rc.getMultiple("*test") == "cout << \"text to standard output\" << endl;");
	}

	TEST(CopyConstructor)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
		CHECK(rc.getMultiple("*test") == "cout << \"text to standard output\" << endl;");

		RCFile rc2 = rc;

		CHECK(rc2.getMultiple("*test") == "fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)");
		CHECK(rc2.getMultiple("*test") == "");
		CHECK(rc2.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
	}

	TEST(AssignmentOperator)
	{
		RCFile rc("TestFiles//RCFiles//basic.rc");

		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
		CHECK(rc.getMultiple("*test") == "cout << \"text to standard output\" << endl;");

		RCFile rc2("");
		rc2 = rc;

		CHECK(rc2.getMultiple("*test") == "fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)");
		CHECK(rc2.getMultiple("*test") == "");
		CHECK(rc2.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
	}
}