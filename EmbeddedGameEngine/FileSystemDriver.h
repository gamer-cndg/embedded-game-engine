#pragma once

#include <string>
#include <inttypes.h>

/* Declares write modes for files */
enum class WriteMode { 
	New,		/* remove old contents */
	Append		/* append to file */
};

/* Describes what we expect from a filesystem */
class FileSystemDriver
{
public:
	/* shall return whether a file exists */
	virtual bool FileExists(std::string file) = 0;
	virtual size_t FileSize(std::string file) = 0;
	virtual bool ReadFile(std::string path, uint8_t* buffer, size_t length) = 0;
	virtual bool WriteFile(std::string path, uint8_t* data, size_t len, WriteMode write_mode = WriteMode::New) = 0;

	FileSystemDriver();
	~FileSystemDriver();
};

