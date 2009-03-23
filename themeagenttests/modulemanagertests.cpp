#include "ModuleManager.h"
#include <UnitTest++.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

SUITE(ModuleManager)
{
	TEST(Constructor)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", "", dlSites);
		ModuleList ml = mm.getModuleList();
		CHECK(ml.size() == 5);
		CHECK(ml.contains(Module("dynamp-0.51.dll")));
		CHECK(ml.contains(Module("lsres.dll")));
		CHECK(ml.contains(Module("lslua-0.7")));
	}

	TEST(UnzipModule)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", "", dlSites);

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

	TEST(DownloadAndExtractModule)
	{
		vector<string> dlSites;
		dlSites.push_back("http://shellfront.org/modules/");
		ModuleManager mm("TestFiles\\Modules", "TestFiles\\NLM\\NetLoadModule.ini", dlSites);

		mm.installModule("one-0.7");

		CHECK(GetFileAttributes("TestFiles\\Modules\\one-0.7.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\one-0.7.html") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\one-0.7") == INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\one-0.7.dll");
		DeleteFile("TestFiles\\Modules\\docs\\one-0.7.html");
		DeleteFile("TestFiles\\Modules\\archive\\one-0.7.zip");

		dlSites.clear();
		for (int i = 0; i < 10; ++i)
		{
			dlSites.push_back("http://modules.does-not-exist.com/here/");
		}
		dlSites.push_back("http://www.ls-themes.org/modules/download/");
		ModuleManager mm2("TestFiles\\Modules", "TestFiles\\NLM\\NetLoadModule.ini", dlSites);

		CHECK(mm2.installModule("lockPC-1.0") == true);

		DeleteFile("TestFiles\\Modules\\lockPC-1.0.dll");
		DeleteFile("TestFiles\\Modules\\docs\\lockPC-1.0.txt");
		DeleteFile("TestFiles\\Modules\\archive\\lockPC-1.0.zip");
	}

	TEST(UpdateNLMList)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", "TestFiles\\NLM\\NetLoadModule2.ini", dlSites);

		CopyFile("TestFiles\\NLM\\NetLoadModule.ini", "TestFiles\\NLM\\NetLoadModule2.ini", FALSE);

		mm.installModule("manyDllsModule-8.0");

		ifstream ifs("TestFiles\\NLM\\NetLoadModule2.ini");

		string line;
		getline(ifs, line);
		CHECK(line == "[NetLoadModule]");
		getline(ifs, line);
		CHECK(line == "lslua-0.7=$litestepdir$modules\\lslua-0.7\\lslua.dll");
		getline(ifs, line);
		CHECK(line == "manyDllsModule-8.0=$litestepdir$modules\\manyDllsModule-8.0\\manyDllsModule.dll");

		ifs.close();

		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\manydllsmodule.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllone.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dlltwo.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllthree.dll");
		DeleteFile("TestFiles\\Modules\\manyDllsModule-8.0\\dllfour.dll");
		DeleteFile("TestFiles\\Modules\\docs\\manyDllsModule-8.0.txt");
		RemoveDirectory("TestFiles\\Modules\\manyDllsModule-8.0");

		DeleteFile("TestFiles\\NLM\\NetLoadModule2.ini");
	}

	TEST(InstallModule)
	{
		vector<string> dlSites;
		dlSites.push_back("http://shellfront.org/modules/");
		ModuleManager mm("TestFiles\\Modules", "TestFiles\\NLM\\NetLoadModule2.ini", dlSites);

		CopyFile("TestFiles\\NLM\\NetLoadModule.ini", "TestFiles\\NLM\\NetLoadModule2.ini", FALSE);

		CHECK(mm.installModule("lslua-0.5"));
		CHECK(mm.getModuleList().contains(Module("lslua-0.5")));

		ifstream ifs("TestFiles\\NLM\\NetLoadModule2.ini");

		string line;
		getline(ifs, line);
		CHECK(line == "[NetLoadModule]");
		getline(ifs, line);
		CHECK(line == "lslua-0.7=$litestepdir$modules\\lslua-0.7\\lslua.dll");
		getline(ifs, line);
		CHECK(line == "lslua-0.5=$litestepdir$modules\\lslua-0.5\\lslua.dll");

		ifs.close();

		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\lslua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\args.lua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\evar.lua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\lua51.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\luainterface.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\textedit.lua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\thread.lua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5\\timer.lua.dll") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\lslua-0.5.dll") == INVALID_FILE_ATTRIBUTES);

		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\lslua-0.5\\history.txt") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\lslua-0.5\\readme.html") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Modules\\docs\\lslua-0.5.html") == INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Modules\\archive\\lslua-0.5.zip");

		DeleteFile("TestFiles\\Modules\\lslua-0.5\\lslua.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\args.lua.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\evar.lua.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\lua51.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\luainterface.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\textedit.lua.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\thread.lua.dll");
		DeleteFile("TestFiles\\Modules\\lslua-0.5\\timer.lua.dll");
		RemoveDirectory("TestFiles\\Modules\\lslua-0.5");

		DeleteFile("TestFiles\\Modules\\docs\\lslua-0.5\\history.txt");
		DeleteFile("TestFiles\\Modules\\docs\\lslua-0.5\\readme.html");
		RemoveDirectory("TestFiles\\Modules\\docs\\lslua-0.5");

		DeleteFile("TestFiles\\NLM\\NetLoadModule2.ini");
	}
}