#include <iostream>
#include <fstream>
#include <string>
#include <map>

const std::map<std::string, int> numberNameMap = {
   { "one", 1 },
   { "two", 2 },
   { "three", 3 },
   { "four", 4 },
   { "five", 5 },
   { "six", 6 },
   { "seven", 7 },
   { "eight", 8 },
   { "nine", 9 }
};

void replaceFirst(const std::string &line, int firstPos, int &firstDigit);
void replaceLast(const std::string &line, int lastPos, int &lastDigit);

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
          int firstDigit = -1, lastDigit = -1;
          size_t firstPos = line.size(), lastPos = 0;

          for(size_t i = 0; i < line.length(); ++i)
            {
              if(isdigit(line[i]))
                {
                  const int num = line[i] - '0';

                  lastDigit = num;
                  lastPos   = i;

                  if(firstDigit == -1)
                    {
                      firstDigit = num;
                      firstPos   = i;
                    }
                }
            }

          replaceFirst(line, firstPos, firstDigit);
          replaceLast(line, lastPos, lastDigit);

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

void replaceFirst(const std::string &line, int firstPos, int &firstDigit)
{
  for(auto const& [ name, value ] : numberNameMap)
    {
      size_t pos = line.find(name);

      if(pos != std::string::npos && pos <= firstPos)
        {
          firstPos   = pos;
          firstDigit = value;
        }
    }
}

void replaceLast(const std::string &line, int lastPos, int &lastDigit)
{
  for(auto const& [ name, value ] : numberNameMap)
    {
      size_t pos = line.rfind(name);

      if(pos != std::string::npos && pos >= lastPos)
        {
          lastPos   = pos;
          lastDigit = value;
        }
    }
}
