#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GridEntry
{
  bool star;
  std::vector<int> adjacentCodes;

public:
  GridEntry()
  {
    star = false;
    adjacentCodes = std::vector<int>();
  }

  void SetStar()
  {
    star = true;
  }

  void AddCode(int code)
  {
    adjacentCodes.push_back(code);
  }

  bool IsStar() const
  {
    return star;
  }

  size_t CodesSize() const
  {
    return adjacentCodes.size();
  }

  int CodesProduct() const
  {
    int product = 1;

    for(auto const& code : adjacentCodes)
      product *= code;

    return product;
  }
};

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

      std::vector<std::vector<GridEntry>> gridEntries;

      while(std::getline(inputFile, line))
        {
          grid.push_back(line);
          gridEntries.push_back(std::vector<GridEntry>(line.size(), GridEntry()));
        }

      for(int i = 0; i < grid.size(); ++i)
        {
          const std::string row = grid[i];

          for(int j = 0; j < row.size();)
            {
              if(row[j] == '*')
                gridEntries[i][j].SetStar();

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

                          if(grid[ii][jj] == '*')
                            gridEntries[ii][jj].AddCode(number);
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

      int total2 = 0;

      for(auto const& gridRows : gridEntries)
        {
          for(auto const& entry : gridRows)
            {
              if(entry.IsStar() && entry.CodesSize() == 2)
                total2 += entry.CodesProduct();
            }
        }

      std::cout << "Total2: " << total2 << std::endl;
    }
}

bool IsPart(const char c)
{
  return !std::isdigit(c) && c != '.';
}
