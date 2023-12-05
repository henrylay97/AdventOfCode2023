#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  if(argc == 1)
    {
      std::cout << "Please input file name..." << std::endl;
      return 1;
    }

  std::string fileName = argv[1];
  std::fstream inputFile(fileName, std::ios::in);

  if(inputFile.is_open())
    {
      std::string line;

      int totalValue = 0;

      while(getline(inputFile, line))
        {
          int firstDigit = -1;
          int lastDigit = -1;

          for(int i = 0; i < line.length(); ++i)
            {
              if(isdigit(line[i]))
                {
                  const int num = line[i] - '0';
                  lastDigit = num;

                  if(firstDigit == -1)
                    firstDigit = num;
                }
            }

          const int value = 10 * firstDigit + lastDigit;
          totalValue += value;
        }

      std::cout << "Total: " << totalValue << std::endl;
    }
  else
    {
      std::cout << "Failed to open file" << std::endl;
      return 1;
    }
}
