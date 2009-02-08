#include "FileDownloader.h"
#include "URLDownloadCallback.h"
#include <windows.h>

using namespace std;

void FileDownloader::downloadFile(const string &url, const string &destPath)
{
	this->url = url;
	this->destPath = destPath;
	threadHandle = CreateThread(NULL, NULL, &FileDownloader::threadRunnerTrampoline, this, 0, NULL);
}

DWORD FileDownloader::threadRunnerTrampoline(LPVOID lpParameters)
{
	return reinterpret_cast<FileDownloader*>(lpParameters)->run();
}

DWORD FileDownloader::run()
{
	URLDownloadCallback udc;

	return URLDownloadToFile(NULL, url.c_str(), destPath.c_str(), 0, &udc);
}

FileDownloader::~FileDownloader()
{
	WaitForSingleObject(threadHandle, 60*1000);
	CloseHandle(threadHandle);
}