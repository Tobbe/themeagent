#include "RCFile.h"
#include <UnitTest++.h>
#include <windows.h>
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

class SetupFixtureRCFile
{
public:
	string rc10;

	SetupFixtureRCFile()
	{
		ofstream rcfile;
		rc10 = "rc10.rc";
		rcfile.open(rc10.c_str());

		if (!rcfile.is_open())
		{
			assert(false);
		}
		else
		{
			rcfile << "   \tsettingOne    uno" << endl;
			rcfile << "\t\t settingTwo    dos" << endl;
			rcfile << "     settingThree  tres" << endl;
			rcfile << endl;
			rcfile << "\t   settingFour   red green blue  \t  " << endl;
			rcfile << endl;
			rcfile << "*test MessageBox(NULL, \"message box text\", \"caption\", MB_OK);" << endl;
			rcfile << "*test cout << \"text to standard output\" << endl;" << endl;
			rcfile << "*test fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)" << endl;
			rcfile << endl;
			rcfile << "*single this is the only \"*single\"" << endl;
			rcfile << endl;
			rcfile << "settingFive   cuatro" << endl;
			rcfile << "settingSix    cinco" << endl;

			rcfile.close();
		}
	}

	~SetupFixtureRCFile()
	{
		DeleteFile(rc10.c_str());
	}

};
			

SUITE(RCFile)
{
	TEST_FIXTURE(SetupFixtureRCFile, Constructor)
	{
		RCFile rc(rc10);
		CHECK(rc.lines() == 10);
	}
}