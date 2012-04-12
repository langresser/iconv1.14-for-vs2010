/*
 * Copyright (C) 2004-2012 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "ZLEncodingConverter.h"

ZLEncodingConverter::ZLEncodingConverter() {
}

ZLEncodingConverter::~ZLEncodingConverter() {
}

void ZLEncodingConverter::convert(std::string &dst, const std::string &src) {
	convert(dst, src.data(), src.data() + src.length());
}


IconvEncodingConverter::IconvEncodingConverter(const std::string &encoding) {
	m_encoding = encoding;
//	m_converter = iconv_open("utf-8//TRANSLIT", encoding.c_str());
//	m_converter = iconv_open("utf-8//IGNORE", encoding.c_str());
	m_converter = iconv_open("gb18030//IGNORE", encoding.c_str());
}

IconvEncodingConverter::~IconvEncodingConverter() {
	iconv_close(m_converter);
	m_converter = 0;
}

std::string IconvEncodingConverter::name() const {
	return m_encoding;
}

void IconvEncodingConverter::convert(std::string &dst, const char *srcStart, const char *srcEnd) {
	if (m_converter == 0) {
		return;
	}

	int srcLen = srcEnd - srcStart;
	int outLen = srcLen * 2;

// 	if (m_encoding == "utf-8") {
// 		char* outBuffer = new char[srcLen + 1];
// 		memcpy(outBuffer, srcStart, srcLen);
// 		outBuffer[srcLen] = 0;
// 		dst = outBuffer;
// 		return;
// 	}

	if (outLen < 1024) {
		outLen = 1024;
		static char s_outBuffer[1024] = {0};
		memset(s_outBuffer, 0, outLen);

		// iconv会写tempOutBuffer指针，最终其会指向转换未完成的部分
		char* tempOutBuffer = s_outBuffer;
		size_t ret = iconv(m_converter, (const char**)&srcStart, (size_t *)&srcLen, &tempOutBuffer, (size_t *)&outLen);
		dst = s_outBuffer;
//		LOGD(dst.c_str());
	} else {
		char* outBuffer = new char[outLen];
		memset(outBuffer, 0, outLen);

		// iconv会写tempOutBuffer指针，最终其会指向转换未完成的部分
		char* tempOutBuffer = outBuffer;
		size_t ret = iconv(m_converter, (const char**)&srcStart, (size_t *)&srcLen, &tempOutBuffer, (size_t *)&outLen);
		dst = outBuffer;

	//	LOGD(dst.c_str());
		delete[] outBuffer;
	}
}

void IconvEncodingConverter::reset() {
}

bool IconvEncodingConverter::fillTable(int *map) {
	return true;
}
