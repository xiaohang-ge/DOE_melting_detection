#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include<opencv2/opencv.hpp>
#include <io.h>
#include <direct.h>
#include<fstream>
using namespace std;
using namespace cv;
int window = 4;
int interval = 100;
int light_mean(Mat &src1, string &newPath)
{
	const char *p = "./1.txt";
	ofstream fout(p);
	Mat ref_win(window, window, CV_8UC1, Scalar(0));
	Mat target_win(window, window, CV_8UC1, Scalar(0));
	for (int i = interval; i < src1.cols - window; i++)
	{
		for (int j = interval; j < src1.rows - window; j++)
		{
			ref_win = src1(Rect(i, j, window, window));
			target_win = src1(Rect(i - interval, j - interval, window, window));
			Scalar value;
			value = sum(ref_win);
			Scalar value_;
			value_ = sum(target_win);

			if (value_[0] != 0)
			{
				fout << value[0] / value_[0] << endl;
				if (value[0] / value_[0] > 30)
				{
					return -1;
				}
			}
		}
	}
	return 0;
}
bool TraverseDirectory(std::string path)
{
	__int64  Handle;
	struct __finddata64_t  FileInfo;
	string strFind = path + "\\*";

	if ((Handle = _findfirst64(strFind.c_str(), &FileInfo)) == -1L)
	{
		printf("没有找到匹配的项目\n");
		return false;
	}
	do
	{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//判断是子文件夹
			//下面的判断条件很重要，过滤 . 和 ..
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				string newPath = path + "\\" + FileInfo.name;
				TraverseDirectory(newPath);
			}
		}
		else
		{
			string newPath = path + "\\" + FileInfo.name;
			char *st1 = const_cast<char *>(newPath.c_str());
			Mat src = imread(st1);
			if (light_mean(src, newPath) == -1)
			{
				string::size_type iPos = newPath.find_last_of('\\') + 1;
				string newPath2 = newPath.substr(iPos, newPath.length() - iPos);
				string newPath3 = newPath2.substr(0, newPath2.rfind("."));
				char ad[128000] = { 0 };
				char buf[128] = { 0 };
				newPath3.copy(buf, 100);
				sprintf_s(ad, "./zt/%s.bmp", buf);
				imwrite(ad, src);
			}
		}
	} while (_findnext64(Handle, &FileInfo) == 0);

	_findclose(Handle);
	return true;
}
int main(int argc, char *argv[])
{
	const char *st = argv[1];
	string input_path = st;
	TraverseDirectory(input_path);
	return 0;
}