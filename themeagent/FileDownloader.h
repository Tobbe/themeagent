#ifndef FILE_DOWNLOADER_H_
#define FILE_DOWNLOADER_H_

#include <string>
#include <windows.h>

class FileDownloader
{
private:
	std::string url;
	std::string destPath;
	HANDLE threadHandle;

	static DWORD CALLBACK threadRunnerTrampoline(LPVOID lpParameters);
	DWORD __stdcall run();
public:
	~FileDownloader();
	void downloadFile(const std::string &url, const std::string &destPath);
};

#endif