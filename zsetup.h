#pragma once

#include <string>

class zip_excp : public std::exception
{
public:
	zip_excp(const std::string& str) : msg(str)
	{}

	virtual const char* what() const noexcept
	{
		return msg.c_str();
	}
private:
	std::string msg;
};

class zsetup {
public:
	enum class zip_types : unsigned {
		GZIP_FILE = 0,
		BZIP_FILE,
		XZIP_FILE,
		NON_ZIP
	};

private:
	static void init(zip_types);

public:
	static bool has_zip(zip_types);
	static const std::string& zip_path(zip_types);
	static const std::string& unzip_path(zip_types);
	static bool set_zip_path(const std::string&, zip_types);
	static bool set_unzip_path(const std::string&, zip_types);
	static std::string zip_file(const std::string&, zip_types);
	static std::string unzip_file(const std::string&, zip_types);
	static std::string missing_zip_error(zip_types);
	static zip_types check_zip_type(const std::string&);

private:
	static std::string m_gzip_path;
	static std::string m_bzip_path;
	static std::string m_xzip_path;

	static std::string m_gunzip_path;
	static std::string m_bunzip_path;
	static std::string m_xunzip_path;
};
