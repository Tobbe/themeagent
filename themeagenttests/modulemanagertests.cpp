#include "ModuleManager.h"
#include <UnitTest++.h>
#include <vector>
#include <string>

using namespace std;

SUITE(ModuleManager)
{
	TEST(Constructor)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", dlSites);
		ModuleList ml = mm.getModuleList();
		CHECK(ml.size() == 5);
		CHECK(ml.contains(Module("dynamp-0.51.dll")));
		CHECK(ml.contains(Module("lsres.dll")));
		CHECK(ml.contains(Module("lslua-0.7")));
	}

	TEST(UnzipModule)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", dlSites);

		mm.installModule("moduleZip-1.4.2");

		CHECK(GetFileAttributes("TestFiles\\Modules\\modulezip-1.4.2.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\modulezip-1.4.2.chm") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\modulezip-1.4.2.dll");
		DeleteFile("TestFiles\\Modules\\docs\\modulezip-1.4.2.chm");

		mm.installModule("docsFolderModule-1.79");

		CHECK(GetFileAttributes("TestFiles\\Modules\\docsfoldermodule-1.79.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\readme.html") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\docs.gif") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\folder.png") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\module.jpg") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\docsfoldermodule-1.79.dll");
		DeleteFile("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\readme.html");
		DeleteFile("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\docs.gif");
		DeleteFile("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\folder.png");
		DeleteFile("TestFiles\\Modules\\docs\\docsfoldermodule-1.79\\module.jpg");
		RemoveDirectory("TestFiles\\Modules\\docs\\docsfoldermodule-1.79");

		mm.installModule("noVersionModule");

		CHECK(GetFileAttributes("TestFiles\\Modules\\noversionmodule.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\noversionmodule.txt") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\noversionmodule.dll");
		DeleteFile("TestFiles\\Modules\\docs\\noversionmodule.txt");

		mm.installModule("manyDllsModule-8.0");

		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0.dll") == INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0\\manydllsmodule.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0\\dllone.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0\\dlltwo.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0\\dllthree.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\manyDllsModule-8.0\\dllfour.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\manyDllsModule-8.0.txt") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\dontextract.txt") == INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\dontextract-8.0.txt") == INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\manydllsmodule.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllone.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dlltwo.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllthree.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllfour.dll");
		DeleteFile("TestFiles\\Modules\\docs\\manyDllsModule-8.0.txt");
		RemoveDirectory("TestFiles\\Modules\\manyDllsModule-8.0");
	}

	TEST(InstallModule)
	{
		vector<string> dlSites;
		dlSites.push_back("http://shellfront.org/modules/");
		ModuleManager mm("TestFiles\\Modules", dlSites);

		mm.installModule("one-0.7");

		CHECK(GetFileAttributes("TestFiles\\Modules\\one-0.7.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\one-0.7.html") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\one-0.7.dll");
		DeleteFile("TestFiles\\Modules\\docs\\one-0.7.html");
		DeleteFile("TestFiles\\Modules\\archive\\one-0.7.zip");
	}
}