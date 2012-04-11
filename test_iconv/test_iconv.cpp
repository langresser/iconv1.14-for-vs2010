// test_iconv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZLEncodingConverter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = fopen("test-gb2312_2.txt", "r");
	if (fp) {
		char temp[1024] = {0};
		fgets(temp, sizeof(temp) - 1, fp);

		IconvEncodingConverter* converter = new IconvEncodingConverter("utf-8");
		if (converter) {
			std::string dest;
			converter->convert(dest, temp, temp + strlen(temp));
			printf(dest.c_str());
		}
	}

	system("PAUSE");
	return 0;
}

