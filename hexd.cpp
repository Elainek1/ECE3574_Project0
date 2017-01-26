/*#include <fstream>

int main()
{

	std::ofstream outs("temp.txt");
	outs << "This is a line of text.\nThis is another.\n";
	outs.close();
	   
	return 0;
}*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
using namespace std;

int main(int argc, char*argv[])
{
	string filename;
	std::vector<std::string>  arguments;
    for(int i = 0; i < argc; ++i)
	{
		arguments.push_back(argv[i]);
		//cout << argv[i] << endl;
		//count++;
	}
    // code can use arguments as a C++ vector of C++ strings 
	if(argc > 1)
	{
		//ofstream outs(arguments[count-1]);
		filename = arguments[argc-1];
	}
	else
	{
		filename = "temp.txt";
		//return EXIT_FAILURE;
	}
	
	ifstream ins(filename, std::ios::binary);
	if(!ins)
	{
		return EXIT_FAILURE;
	}
	uint8_t value;
	uint8_t lines[16];
	ins.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value);
	
	int count = 0;
	
	while(!ins.fail())
	{
		
		if((count % 16) == 0)
		{
			cout << hex << setw(7) << setfill('0') << count << ": ";
		}
		//cout << value << endl;
		cout << hex << setw(2) << setfill('0') << (int)value;
		if((value > 31) && (value < 127))
		{
			lines[count%16] = value;
			//cout << lines[count%16] << endl;
		}
		else
		{
			lines[count%16] = 46;
			//cout << lines[count%16] << endl;
		}
		
		if(count%2)
		{
			cout << " ";
		}

		count++;
		if((count%16) == 0)
		{
			for(int i = 0; i < 16; i++)
			{
				cout << lines[i];
			}
			cout << endl;
		}
		//cout << inputChar << endl;

		//ins >> inputChar;
		ins.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value);

	}
	if(count%16==0)
	{
		return EXIT_SUCCESS;
	}
	int numSpaces = 0;
	numSpaces = 2*(16-count%16)+(16-count%16)/2;
	if(count%16%2)
	{
		numSpaces++;
	}
	for(int i = 0; i<numSpaces; i++)
	{
		cout << " ";
	}
	if(count%16)
	{
		for(int i = 0; i < (count%16); i++)
			{
				cout << lines[i];
			}
			cout << endl;
	}

    return EXIT_SUCCESS;
}
