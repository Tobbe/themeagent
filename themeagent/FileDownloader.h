#ifndef FILE_DOWNLOADER_H_
#define FILE_DOWNLOADER_H_

#include "Observable.h"
#include "Observer.h"
#include <string>
#include <windows.h>

class FileDownloader : public Observable, public Observer
{
private:
	std::string url;
	std::string destPath;
	HANDLE threadHandle;
	int progress;

	static DWORD CALLBACK threadRunnerTrampoline(LPVOID lpParameters);
	DWORD __stdcall run();
public:
	~FileDownloader();
	void downloadFile(const std::string &url, const std::string &destPath);
	void update(Observable *o);
	int getProgress();
};

#endif