#include "iostream"
#include "string"
#include "vector"
#include "filesystem"
#include "conio.h"
#include "stdio.h"

#include "windows.h"


namespace fs = std::experimental::filesystem;

void SetConsoleColor(WORD COLOR)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, COLOR);
}

std::string getext(std::string fname)
{
	std::string ext = "";
	for (int i = fname.length()-1; i > -1; i--)
	{
		if (fname[i] != '.')
		{
			ext = fname[i] + ext;
		}
		else
		{
			break;
		}

	}
	return ext;
}

std::string getFileName(std::string fname)
{
	std::string ext = "";
	for (int i = fname.length(); i > -1; i--)
	{
		if (fname[i] != '\\' && fname[i] != '/')
		{
			ext = fname[i] + ext;
		}
		else
		{
			break;
		}

	}
	return ext;
}

void gethelp()
{
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "This is an Automation Tool Made to automatically run a large number of programs" << std::endl << std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Syntax :\t";
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout<< "complirun - p \"*Directory where all the source code are stored*\"" << std::endl;
	std::cout << "\t\tUse -o flag to store the output in a txt file [Feature Under Development]" << std::endl << std::endl;
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "This Tool has been Developed by Rohan Verma and will be continued to be developed as an open source tool" << std::endl;
	std::cout << "Developed using c++17 on Microsoft Visual Studio 2017" << std::endl;
	std::cout << "Compiled Using MSVC" << std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void runJava(std::string fPath, const bool flag_outputToFile)
{
	if (flag_outputToFile)
	{
		//Code to save the output to a File
	}
	else
	{
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::string cmd = "java \"" + fPath + "\"";
		system(cmd.c_str());
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
}

void runPy(std::string fPath, const bool flag_outputToFile)
{
	if (flag_outputToFile)
	{
		//Code to save the output to a File
	}
	else
	{
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::string cmd = "python3 \"" + fPath + "\"";
		system(cmd.c_str());
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
}

void runCpp(std::string fPath, const bool flag_outputToFile)
{
	if (flag_outputToFile)
	{
		//Code to save the output to a File
	}
	else
	{
		std::string cmd = "c++ -o cppprog \"" + fPath + "\"";
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		system(cmd.c_str());
		system("cppprog.exe");
		remove("cppprog.exe");
		std::cout << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
}

void unknownFile(std::string fname)
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Failed to Run " << fname << std::endl;
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Was Unable to identify the Programming language of the file"<<std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

int main(int argc, const char** argv)
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	bool flag_outputToFile = false;
	bool flag_filePathSet = false;
	std::vector<std::string> filesToRun;
	std::string path = "";


	//Retrive all the info from the Command Line
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[1]) == "help")
		{
			gethelp();
			return 0;
		}
		if (std::string(argv[i]) == "-p" || std::string(argv[i]) == "-P")
		{
			flag_filePathSet = true;
			path = argv[++i];
		}
		if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "-O")
		{
			flag_outputToFile = true;
		}
	}
	//Check if path is present : if absent exit the program
	if (flag_filePathSet==false || path=="")
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Error : ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "File Path Absent" << std::endl;
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "use -P flag followed by the File Path of ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return 0;
	}
	//get all the files in the supplied directory
	for (const auto & entry : fs::directory_iterator(path))
	{
		filesToRun.push_back(entry.path().u8string());
	}

	//start running all the files
	for (std::string s : filesToRun)
	{
		std::string fileName = getFileName(s);
		std::string fileExt = getext(s);

		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Trying to Run " << fileName << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (fileExt == "java")
			runJava(s, flag_outputToFile);
		else if (fileExt == "py")
			runPy(s, flag_outputToFile);
		else if (fileExt == "cpp" || fileExt == "CPP")
			runCpp(s, flag_outputToFile);
		else
			unknownFile(fileName);
	}
	return 0;
}