#include "iostream"
#include "string"
#include "vector"
#include "filesystem"
#include "conio.h"
#include "stdio.h"
#include <chrono>
#include "fstream"
#include "sstream"

#include "windows.h"

#include <direct.h>
#define GetCurrentDir _getcwd


namespace fs = std::experimental::filesystem;

std::vector<std::string> fileWriteBuffer;

std::string exec(std::string cmd)
{
	std::string rt="";
	std::string textFromFile;
	cmd = cmd + " > this_is_an_outputfile.txt";
	system(cmd.c_str());
	std::ifstream file("this_is_an_outputfile.txt");
	while (getline(file, textFromFile))
	{
		rt = rt + textFromFile;
	}
	file.close();
	remove("this_is_an_outputfile.txt");
	return rt;
}

void SetConsoleColor(WORD COLOR)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, COLOR);
}

std::string get_current_dir()
{
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
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

std::string readInputFile()
{
	std::string rt="", txt;
	std::ifstream MyReadFile("this_is_an_inputfile.txt");
	while (getline(MyReadFile, txt))
	{
		rt = rt + txt + "\n";
	}
	MyReadFile.close();
	return rt;
}

void gethelp()
{
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "This is an Automation Tool Made to automatically run a large number of programs" << std::endl << std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Syntax :\t";
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout<< "complirun -p \"*Directory where all the source code are stored*\"" << std::endl;
	std::cout << "\t\tUse -o flag followed path to a txt file to store the output in a txt file" << std::endl;
	std::cout << "\t\tUse -i flag to provide inputs for the files to be run" << std::endl << std::endl;
	std::cout << "\t\tIf you wish to run a single file use complirun - f \"*Path to the source code*\"" << std::endl << std::endl;
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "This Tool has been Developed by Rohan Verma and will be continued to be developed as an open source tool" << std::endl;
	std::cout << "Developed using c++17 on Microsoft Visual Studio 2017" << std::endl;
	std::cout << "Compiled Using MSVC" << std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void runJava(std::string fPath, const bool flag_outputToFile, const bool flag_input)
{
	if (flag_input)
	{
		std::cout << "Enter the inputs for the file" << std::endl << "The program will keep on accepting inputs till it Encounters a line without any text" << std::endl;
		std::vector<std::string> fileinputlines;
		std::ofstream file("this_is_an_inputfile.txt");
		std::string inpt = "";
		do
		{
			getline(std::cin, inpt);
			fileinputlines.push_back(inpt);
		} while (inpt != "");
		for (int i = 0; i < fileinputlines.size() - 1; i++)
		{
			file << fileinputlines[i];
			if (i < fileinputlines.size() - 2)
				file << std::endl;
		}
		file.close();
	}
	else
	{
		std::ofstream file("this_is_an_inputfile.txt");
		file << "";
		file.close();
	}
	if (flag_outputToFile)
	{
		std::string cmd = "java \"" + fPath + "\" < this_is_an_inputfile.txt";

		auto start = std::chrono::high_resolution_clock::now();
		std::string lines[4];
		lines[0]="File Name : "+getFileName(fPath);
		
		if(flag_input)
			lines[1] = "Input File Contains : \n" + readInputFile();
		else
			lines[1] = "Input File Contains : \nThere was No Input";

		lines[2]=exec(cmd);

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::ostringstream out;
		out << duration.count();
		lines[3]="Time Taken : "+out.str()+"ms";
		
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[2] << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[3] << std::endl << std::endl;
		fileWriteBuffer.push_back(lines[0]);
		fileWriteBuffer.push_back(lines[1]);
		fileWriteBuffer.push_back("Output : "+lines[2]);
		fileWriteBuffer.push_back(lines[3]);
		//Adds an Empty line to provide a break line at the end of each program
		fileWriteBuffer.push_back("");
	}
	else
	{
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::string cmd = "java \"" + fPath + "\" < this_is_an_inputfile.txt";

		auto start = std::chrono::high_resolution_clock::now();

		system(cmd.c_str());
		
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Time Taken : " << duration.count() << "ms" << std::endl << std::endl;
	}
	remove("this_is_an_inputfile.txt");
}

void runPy(std::string fPath, const bool flag_outputToFile, const bool flag_input)
{
	if (flag_input)
	{
		std::cout << "Enter the inputs for the file" << std::endl << "The program will keep on accepting inputs till it Encounters a line without any text" << std::endl;
		std::vector<std::string> fileinputlines;
		std::ofstream file("this_is_an_inputfile.txt");
		std::string inpt = "";
		do
		{
			getline(std::cin, inpt);
			fileinputlines.push_back(inpt);
		} while (inpt != "");
		for (int i = 0; i < fileinputlines.size() - 1; i++)
		{
			file << fileinputlines[i];
			if (i < fileinputlines.size() - 2)
				file << std::endl;
		}
		file.close();
	}
	else
	{
		std::ofstream file("this_is_an_inputfile.txt");
		file << "";
		file.close();
	}
	if (flag_outputToFile)
	{
		std::string cmd = "python3 \"" + fPath + "\" < this_is_an_inputfile.txt";
		std::string lines[4];
		
		auto start = std::chrono::high_resolution_clock::now();
		lines[0]="File Name : " + getFileName(fPath);

		if (flag_input)
			lines[1] = "Input File Contains : \n" + readInputFile();
		else
			lines[1] = "Input File Contains : \nThere was No Input";

		lines[2]=exec(cmd);

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::ostringstream out;
		out << duration.count();
		lines[3]="Time Taken : " + out.str() + "ms";

		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[2] << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[3] << std::endl << std::endl;
		fileWriteBuffer.push_back(lines[0]);
		fileWriteBuffer.push_back(lines[1]);
		fileWriteBuffer.push_back("Output : " + lines[2]);
		fileWriteBuffer.push_back(lines[3]);
		fileWriteBuffer.push_back("");
	}
	else
	{
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::string cmd = "python3 \"" + fPath + "\" < this_is_an_inputfile.txt";

		auto start = std::chrono::high_resolution_clock::now();

		system(cmd.c_str());

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Time Taken : " << duration.count() << "ms" << std::endl << std::endl;
	}
	remove("this_is_an_inputfile.txt");
}

void runCpp(std::string fPath, const bool flag_outputToFile, const bool flag_input)
{
	if (flag_input)
	{
		std::cout << "Enter the inputs for the file" << std::endl << "The program will keep on accepting inputs till it Encounters a line without any text" << std::endl;
		std::vector<std::string> fileinputlines;
		std::ofstream file("this_is_an_inputfile.txt");
		std::string inpt = "";
		do
		{
			getline(std::cin, inpt);
			fileinputlines.push_back(inpt);
		} while (inpt != "");
		for (int i = 0; i < fileinputlines.size() - 1; i++)
		{
			file << fileinputlines[i];
			if (i < fileinputlines.size() - 2)
				file << std::endl;
		}
		file.close();
	}
	else
	{
		std::ofstream file("this_is_an_inputfile.txt");
		file << "";
		file.close();
	}
	if (flag_outputToFile)
	{
		std::string cmd = "c++ -o cppprog \"" + fPath + "\"";
		std::string lines[4];

		lines[0]="File Name : " + getFileName(fPath);
		system(cmd.c_str()); 
		
		if (flag_input)
			lines[1] = "Input File Contains : \n" + readInputFile();
		else
			lines[1] = "Input File Contains : \nThere was No Input";

		auto start = std::chrono::high_resolution_clock::now();
		lines[2]=exec("cppprog < this_is_an_inputfile.txt");

		auto stop = std::chrono::high_resolution_clock::now();
		
		remove("cppprog.exe");

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::ostringstream out;
		out << duration.count();
		lines[3]="Time Taken : " + out.str() + "ms";

		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[2] << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << lines[3] << std::endl << std::endl;

		fileWriteBuffer.push_back(lines[0]);
		fileWriteBuffer.push_back(lines[1]);
		fileWriteBuffer.push_back("Output : " + lines[2]);
		fileWriteBuffer.push_back(lines[3]);
		fileWriteBuffer.push_back("");
	}
	else
	{
		std::string cmd = "c++ -o cppprog \"" + fPath + "\"";
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "Output : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		system(cmd.c_str());

		auto start = std::chrono::high_resolution_clock::now();

		system("cppprog.exe < this_is_an_inputfile.txt");

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Time Taken : " << duration.count() << "ms" << std::endl;

		remove("cppprog.exe");
		std::cout << std::endl;
	}
	remove("this_is_an_inputfile.txt");
}

void unknownFile(std::string fname)
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Failed to Run " << fname << std::endl;
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Was Unable to identify the Programming language of the file" << std::endl << std::endl;
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

int main(int argc, const char** argv)
{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	bool flag_outputToFile = false;
	bool flag_filePathSet = false;
	bool flag_singleFileRun = false;
	bool flag_input = false;
	std::vector<std::string> filesToRun;
	std::string path = "";
	std::string outputFilePath = "output.txt";


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
			if (path == "this")
			{
				path = get_current_dir();
			}
		}
		if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "-F")
		{
			flag_singleFileRun = true;
			path = argv[++i];
		}
		if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "-O")
		{
			flag_outputToFile = true;
			outputFilePath = argv[++i]; 
			if (outputFilePath == "this")
			{
				outputFilePath = get_current_dir();
				outputFilePath += "\\output.txt";
			}
		}
		if (std::string(argv[i]) == "-i" || std::string(argv[i]) == "-I")
		{
			flag_input = true;
		}
	}
	//Check if path is present : if absent exit the program
	if ((flag_filePathSet==false || path=="") && flag_singleFileRun==false)
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Error : ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "File Path Absent" << std::endl;
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "To get Help type complirun help" << std::endl;
		std::cout << "use -P flag followed by the Path of Directory containing the files" << std::endl;
		std::cout << "Or use -F flag followed by path of specific path you want to run";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return 0;
	}

	if (flag_filePathSet && flag_singleFileRun)
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Error : ";
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "You Cannot use -f and -p at the same time" << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return 0;
	}

	if (flag_filePathSet)
	{
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
				runJava(s, flag_outputToFile, flag_input);
			else if (fileExt == "py")
				runPy(s, flag_outputToFile, flag_input);
			else if (fileExt == "cpp" || fileExt == "CPP")
				runCpp(s, flag_outputToFile, flag_input);
			else
				unknownFile(fileName);
		}
	}
	else if (flag_singleFileRun)
	{
		std::string fileName = getFileName(path);
		std::string fileExt = getext(path);

		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Trying to Run " << fileName << std::endl;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (fileExt == "java")
			runJava(path, flag_outputToFile, flag_input);
		else if (fileExt == "py")
			runPy(path, flag_outputToFile, flag_input);
		else if (fileExt == "cpp" || fileExt == "CPP")
			runCpp(path, flag_outputToFile, flag_input);
		else
			unknownFile(fileName);
	}
	if (flag_outputToFile)
	{
		std::ofstream outputFile(outputFilePath);
		for (std::string s : fileWriteBuffer)
		{
			outputFile << s << std::endl;
		}
		outputFile.close();
	}
	return 0;
}