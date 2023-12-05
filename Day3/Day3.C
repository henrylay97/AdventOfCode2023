#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool IsPart(const char c);

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
      std::vector<std::string> grid;
      int total = 0;

      while(std::getline(inputFile, line))
        grid.push_back(line);

      for(int i = 0; i < grid.size(); ++i)
        {
          const std::string row = grid[i];

          for(int j = 0; j < row.size();)
            {
              if(std::isdigit(row[j]))
                {
                  size_t pos = row.find('.', j);
                  if(pos == std::string::npos)
                    pos = row.size() - 1;

                  std::string numberString = row.substr(j, pos);

                  for(int k = 0; k < numberString.size(); ++k)
                    {
                      if(!std::isdigit(numberString[k]))
                        {
                          numberString.erase(k, numberString.size());
                          break;
                        }
                    }

                  const int number = std::stoi(numberString);

                  bool isPart = false;

                  for(int ii = i - 1; ii < i + 2; ++ii)
                    {
                      if(ii < 0 || ii >= grid.size())
                        continue;

                      for(int jj = j - 1; jj < j + (int)numberString.size() + 1; ++jj)
                        {
                          if(jj < 0 || jj >= row.size())
                            continue;

                          isPart |= IsPart(grid[ii][jj]);
                        }
                    }

                  if(isPart)
                    total += number;

                  j += numberString.size();
                }
              else
                ++j;
            }
        }

      std::cout << "Total: " << total << std::endl;
    }
}

bool IsPart(const char c)
{
  return !std::isdigit(c) && c != '.';
}
