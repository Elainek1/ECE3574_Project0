#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
using namespace std;

int main(int argc, char*argv[])
{
	string filename;  //for storing the filename grabbed from commandline
	std::vector<std::string>  arguments;
    for(int i = 0; i < argc; ++i)
	{
		arguments.push_back(argv[i]);
	}
    // code can use arguments as a C++ vector of C++ strings 
	
	//if there are more than one arguments grab the last one and use that for the filename
	if(argc > 1)
	{
		filename = arguments[argc-1];
	}
	else
	{
		//otherwise no filename was specified so return with exit failure
		return EXIT_FAILURE;
	}
	//opens file
	ifstream ins(filename, std::ios::binary);
	if(!ins)
	{
		return EXIT_FAILURE; //if file doesnt open then return
	}
	uint8_t value;  //used to read in each character
	uint8_t lines[16];  //used to hold each line of characters to print out at the end
	ins.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value);  //gets character
	
	//used to count how many characters
	int count = 0;
	while(!ins.fail())  //keep looping till end of file
	{
		if((count % 16) == 0)  //print out the address at the beginning of each line
		{
			cout << hex << setw(7) << setfill('0') << count << ": ";
		}
		cout << hex << setw(2) << setfill('0') << (int)value;  //print out the hex value of the character read in
		if((value > 31) && (value < 127))  //if it has an ascii char associated then store as is in the array
		{
			lines[count%16] = value;
		}
		else  //otherwise replace character in array with .
		{
			lines[count%16] = 46;
		}
		
		if(count%2) //after every two character read in put a space
		{
			cout << " ";
		}
		count++; //incrememnt count
		if((count%16) == 0)  //if line is filled up then print the ascii line
		{
			cout << " ";
			for(int i = 0; i < 16; i++)
			{
				cout << lines[i];
			}
			cout << endl;
		}
		ins.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value);  //read in next character
	}
	if(count%16==0)  //if it ends on a full characters line then we finish
	{
		return EXIT_SUCCESS;
	}
	//otherwise we have to calculate the spaces and print out the last half characters line
	int numSpaces = 0;
	numSpaces = 2*(16-count%16)+(16-count%16)/2;  //calculate number of spaces needed to fill the not full line
	if(count%16%2)
	{
		numSpaces++;
	}
	for(int i = 0; i<numSpaces; i++)  //print the spaces
	{
		cout << " ";
	}
	if(count%16)  //then loop and print the last half character line
	{
		cout << " ";
		for(int i = 0; i < (count%16); i++)
			{
				cout << lines[i];
			}
			cout << endl;
	}
    return EXIT_SUCCESS;  //return success
}
