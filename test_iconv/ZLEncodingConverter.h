#pragma once
#include <string>
#include <vector>
#include <map>
#include <iconv.h>

class ZLEncodingConverter {
public:
	ZLEncodingConverter();
	virtual ~ZLEncodingConverter();
	virtual std::string name() const = 0;
	virtual void convert(std::string &dst, const char *srcStart, const char *srcEnd) = 0;
	void convert(std::string &dst, const std::string &src);
	virtual void reset() = 0;
	virtual bool fillTable(int *map) = 0;

private:
	ZLEncodingConverter(const ZLEncodingConverter&);
	ZLEncodingConverter &operator = (const ZLEncodingConverter&);
};

class IconvEncodingConverter : public ZLEncodingConverter {

private:
	std::string m_encoding;
	iconv_t m_converter;
public:
	IconvEncodingConverter(const std::string &encoding);
	~IconvEncodingConverter();
	std::string name() const;
	void convert(std::string &dst, const char *srcStart, const char *srcEnd);
	void reset();
	bool fillTable(int *map);

friend class IconvEncodingConverterProvider;
};