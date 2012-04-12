// test_iconv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZLEncodingConverter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = fopen("test-gb2312_2.txt", "r");
	if (fp) {
		char temp[1024] = {0};
		int xxx;
// 		fread(&xxx, 1, 1, fp);
// 		fread(&xxx, 1, 1, fp);
		fread(temp, sizeof(temp) - 1, 1, fp);

		IconvEncodingConverter* converter = new IconvEncodingConverter("utf-8");//("UCS-2");
		if (converter) {
			std::string dest;
			converter->convert(dest, temp, temp + 1023);
			printf(dest.c_str());
		}
	}

	system("PAUSE");
	return 0;
}

