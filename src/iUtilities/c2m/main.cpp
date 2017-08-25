#include <iostream>
#include <string>
using namespace std;

#ifdef MSVC
#include <conio.h>
#endif

using namespace System;

static std::string toStandardString(System::String^ string)
{
	using System::Runtime::InteropServices::Marshal;
	System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string returnString(charPointer, string->Length);
	Marshal::FreeHGlobal(pointer);
	return returnString;
}

int c2m(
	const char* library,
	const char* prefix,
	const string& path,
	const string& chfile, 
	const string& mhfile, 
	const string& mcfile,
	int wp = 0);

int main(int argc, char **argv)
{
	int status;
	string path;

	string SIRF_path;
	try {
		SIRF_path = toStandardString(Environment::GetEnvironmentVariable("SIRF_PATH"));
	}
	catch (...) {
		cout << "variable not defined" << endl;
		getc(stdin);
		return 1;
	}

	if (argc < 2 || argv[1][0] == 'u') {
		//path = "../";
		path = SIRF_path + "/src/iUtilities/";
		status = c2m\
			("IUTILITIES", "---", path, "iutilities.h", "mutilities.h", "mutilities.c");
		if (status)
			cout << "wrong input file format" << endl;
	}

	if (argc < 2 || argv[1][0] == 'g') {
		path = SIRF_path + "/src/xGadgetron/cGadgetron/";
		//path = "../../xGadgetron/cGadgetron/";
		status = c2m\
			("CGADGETRON", "cGT", path, "cgadgetron.h", "mgadgetron.h", "mgadgetron.c");
		if (status)
			cout << "wrong input file format" << endl;
	}

	if (argc < 2 || argv[1][0] == 's') {
		path = SIRF_path + "/src/xSTIR/cSTIR/";
		//path = "../../xSTIR/cSTIR/";
		status = c2m("CSTIR", "cSTIR", path, "cstir.h", "mstir.h", "mstir.c", 1);
		if (status)
			cout << "wrong input file format" << endl;
	}

#ifdef MSVC
	cout << "Press any key to continue ";
	_getch();
#endif
	return 0;
}

