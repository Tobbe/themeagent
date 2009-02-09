#include <UnitTest++.h>
#include "FileDownloader.h"

SUITE(FileDownloader)
{
	TEST(DownloadFileCreateDir)
	{
		FileDownloader fd;

		CHECK(GetFileAttributes("TestFiles\\FileDownloaderTest\\This\\Does\\Not\\Exist") == INVALID_FILE_ATTRIBUTES);

		fd.downloadFile("", "TestFiles\\FileDownloaderTest\\This\\Does\\Not\\Exist\\archive.zip");

		CHECK(GetFileAttributes("TestFiles\\FileDownloaderTest\\This\\Does\\Not\\Exist") != INVALID_FILE_ATTRIBUTES);

		RemoveDirectory("TestFiles\\FileDownloaderTest\\This\\Does\\Not\\Exist");
		RemoveDirectory("TestFiles\\FileDownloaderTest\\This\\Does\\Not");
		RemoveDirectory("TestFiles\\FileDownloaderTest\\This\\Does");
		RemoveDirectory("TestFiles\\FileDownloaderTest\\This");
		RemoveDirectory("TestFiles\\FileDownloaderTest");
	}

	TEST(DownloadFile)
	{
		FileDownloader fd;

		fd.downloadFile("http://www.does.not.exist.com/archive.zip", "TestFiles\\FileDownloaderTest\\archive.zip");

		CHECK(GetFileAttributes("TestFiles\\FileDownloaderTest\\archive.zip") == INVALID_FILE_ATTRIBUTES);

		fd.downloadFile("http://google.com/index.html", "TestFiles\\FileDownloaderTest\\webpage.html");

		CHECK(GetFileAttributes("TestFiles\\FileDownloaderTest\\webpage.html") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\FileDownloaderTest\\webpage.html");
		RemoveDirectory("TestFiles\\FileDownloaderTest");
	}

	TEST(DownloadFileTimeout)
	{
		FileDownloader fd;
		fd.setTimeout(1);
		fd.downloadFile("http://shellfront.org/Modules/Rainlendar-0.22.zip", "TestFiles\\FileDownloaderTest\\module.zip");

		CHECK(GetFileAttributes("TestFiles\\FileDownloaderTest\\module.zip") == INVALID_FILE_ATTRIBUTES);

		RemoveDirectory("TestFiles\\FileDownloaderTest");
	}
}
