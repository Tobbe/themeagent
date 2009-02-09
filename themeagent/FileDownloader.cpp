#include "FileDownloader.h"
#include "URLDownloadCallback.h"
#include <windows.h>
#include <stack>

using namespace std;

FileDownloader::FileDownloader()
{
	timeout = 0;
}

void FileDownloader::downloadFile(const string &url, const string &destPath)
{
	string tmpPath = destPath.substr(0, destPath.find_last_of("\\/"));
	if (GetFileAttributes(tmpPath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		stack<string> pathStack;
		while (CreateDirectory(tmpPath.c_str(), NULL) == FALSE && 
			GetLastError() == ERROR_PATH_NOT_FOUND)
		{
			pathStack.push(tmpPath);
			tmpPath = tmpPath.substr(0, tmpPath.find_last_of("\\/"));
		}
		while (pathStack.size() > 0) {
			string path = pathStack.top();
			pathStack.pop();
			CreateDirectory(path.c_str(), NULL);
		}
	}

	this->url = url;
	this->destPath = destPath;

	threadHandle = CreateThread(NULL, NULL, &FileDownloader::threadRunnerTrampoline, this, 0, NULL);

	WaitForSingleObject(threadHandle, 60*1000);
	CloseHandle(threadHandle);
}

DWORD FileDownloader::threadRunnerTrampoline(LPVOID lpParameters)
{
	return reinterpret_cast<FileDownloader*>(lpParameters)->run();
}

DWORD FileDownloader::run()
{
	URLDownloadCallback udc;

	if (timeout > 0)
	{
		udc = URLDownloadCallback(timeout);
	}

	udc.addObserver(this);

	return URLDownloadToFile(NULL, url.c_str(), destPath.c_str(), 0, &udc);
}

void FileDownloader::update(const Observable *o)
{
	progress = reinterpret_cast<const URLDownloadCallback*>(o)->getProgress();
	notifyObservers(this);
}

int FileDownloader::getProgress() const
{
	return progress;
}

void FileDownloader::setTimeout(int seconds)
{
	timeout = seconds;
}