#include "Header.h"

std::string zsetup::m_gzip_path{};
std::string zsetup::m_bzip_path{};
std::string zsetup::m_xzip_path{};

std::string zsetup::m_gunzip_path{};
std::string zsetup::m_bunzip_path{};
std::string zsetup::m_xunzip_path{};


namespace {
	using uint = unsigned int;
	bool str_ends_with(const std::string& s, const std::string& suffix)
	{
		uint len1 = (uint)(s.length());
		uint len2 = (uint)(suffix.length());
		return (len1 >= len2) && (s.substr(len1 - len2) == suffix);
	}
} //unnamed namespace


void zsetup::init(zip_types zip_type)
{
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		static bool initialized = false;
		if (initialized) {
			return;
		}
		initialized = true;
		if (::system("which gzip > /dev/null") == 0) {
			m_gzip_path = "gzip";
			m_gunzip_path = "gunzip";
		}
		break;
	}
	case zip_types::BZIP_FILE: {
		static bool initialized = false;
		if (initialized) {
			return;
		}
		initialized = true;
		if (::system("which bunzip2 > /dev/null") == 0 &&
			::system("which bzip2 > /dev/null") == 0)
		{
			m_bzip_path = "bzip2";
			m_bunzip_path = "bunzip2";
		}
		break;
	}
	case zip_types::XZIP_FILE: {
		static bool initialized = false;
		if (initialized) {
			return;
		}
		initialized = true;
		if (::system("which unxz > /dev/null") == 0 &&
			::system("which xz > /dev/null") == 0)
		{
			m_xzip_path = "xz";
			m_xunzip_path = "unxz";
		}
		break;
	}
	default: {
		(false);
	}
	}
}

bool zsetup::has_zip(zip_types zip_type)
{
	init(zip_type);
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return !m_gzip_path.empty() && !m_gunzip_path.empty();
	}
	case zip_types::BZIP_FILE: {
		return !m_bzip_path.empty() && !m_bunzip_path.empty();
	}
	case zip_types::XZIP_FILE: {
		return !m_xzip_path.empty() && !m_xunzip_path.empty();
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return false;
}

const std::string& zsetup::zip_path(zip_types zip_type)
{
	init(zip_type);
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return m_gzip_path;
	}
	case zip_types::BZIP_FILE: {
		return m_bzip_path;
	}
	case zip_types::XZIP_FILE: {
		return m_xzip_path;
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return m_gzip_path;
}

const std::string& zsetup::unzip_path(zip_types zip_type)
{
	init(zip_type);
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return m_gunzip_path;
	}
	case zip_types::BZIP_FILE: {
		return m_bunzip_path;
	}
	case zip_types::XZIP_FILE: {
		return m_xunzip_path;
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return m_gunzip_path;
}

bool zsetup::set_zip_path(const std::string& path, zip_types zip_type)
{
	init(zip_type);
	if (::access(path.c_str(), X_OK) != 0) {
		return false;
	}
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		m_gzip_path = path;
		return true;
	}
	case zip_types::BZIP_FILE: {
		m_bzip_path = path;
		return true;
	}
	case zip_types::XZIP_FILE: {
		m_xzip_path = path;
		return true;
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return false;
}

bool zsetup::set_unzip_path(const std::string& path, zip_types zip_type)
{
	init(zip_type);
	if (::access(path.c_str(), X_OK) != 0) {
		return false;
	}
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		m_gunzip_path = path;
		return true;
	}
	case zip_types::BZIP_FILE: {
		m_bunzip_path = path;
		return true;
	}
	case zip_types::XZIP_FILE: {
		m_xunzip_path = path;
		return true;
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return false;
}

std::string zsetup::zip_file(const std::string& file_name, zip_types zip_type)
{
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return m_gzip_path + std::string(" > ") + "\"" + std::string(file_name) + "\"";
	}
	case zip_types::BZIP_FILE: {
		return m_bzip_path + std::string(" > ") + "\"" + std::string(file_name) + "\"";
	}
	case zip_types::XZIP_FILE: {
		return m_xzip_path + std::string(" > ") + "\"" + std::string(file_name) + "\"";
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return std::string{};
}

std::string zsetup::unzip_file(const std::string& file_name, zip_types zip_type)
{
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return m_gunzip_path + std::string(" -dcq ") + file_name;
	}
	case zip_types::BZIP_FILE: {
		return m_bunzip_path + std::string(" < \"") + file_name + std::string("\"");
	}
	case zip_types::XZIP_FILE: {
		return m_xunzip_path + std::string(" < \"") + file_name + std::string("\"");
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return std::string{};
}

std::string zsetup::missing_zip_error(zip_types zip_type)
{
	switch (zip_type) {
	case zip_types::GZIP_FILE: {
		return "please specify a full pathname for gzip with 'config_gzip' command";
	}
	case zip_types::BZIP_FILE: {
		return "please specify a full pathname for bzip with 'config_bzip' command";
	}
	case zip_types::XZIP_FILE: {
	    return "please specify a full pathname for xzip with 'config_xzip' command";
	}
	default: {
		throw zip_excp("incorrect zip format");
	}
	}
	return std::string{};
}

zsetup::zip_types zsetup::check_zip_type(const std::string& file_name)
{
	if (str_ends_with(file_name, ".gz")) {
		return zip_types::GZIP_FILE;
	}
	if (str_ends_with(file_name, ".bz2")) {
		return zip_types::BZIP_FILE;
	}
	if (str_ends_with(file_name, ".xz")) {
		return zip_types::XZIP_FILE;
	}
	return zip_types::NON_ZIP;
}
