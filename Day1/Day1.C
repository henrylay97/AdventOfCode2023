#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::fstream inputFile("input.txt", std::ios::in);

  if(inputFile.is_open())
    {
      std::string line;

      while(getline(inputFile, line))
	{
	  std::cout << line << std::endl;
	}
    }
}
