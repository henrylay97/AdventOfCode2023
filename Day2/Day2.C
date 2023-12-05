#include<fstream>
#include<iostream>
#include <string>
#include <vector>

class round
{
  int nred;
  int ngreen;
  int nblue;

public:

  round(int red, int green, int blue)
  {
    nred   = red;
    ngreen = green;
    nblue  = blue;
  }

  bool possible(int red, int green, int blue) const
  {
    return nred <= red && ngreen <= green && nblue <= blue;
  }

  void updateMinimum(int &red, int &green, int &blue) const
  {
    if(nred > red)
      red = nred;

    if(ngreen > green)
      green = ngreen;

    if(nblue > blue)
      blue = nblue;
  }
};

typedef std::vector<round> rounds;

int HowManyColour(const std::string &line, const std::string &name, const size_t end);

int main(int argc, char *argv[])
{
  if(argc != 2)
    {
      std::cout << "Wrong number of inputs... should be 1..." << std::endl;
      return 1;
    }

  const std::string fileName = argv[1];
  std::fstream inputFile(fileName, std::ios::in);

  if(inputFile.is_open())
    {
      std::string line;
      int total = 0;
      
      while(getline(inputFile, line))
        {
          rounds lineRounds;

          size_t colonPos = line.find(':');
          line.erase(0, colonPos + 2);

          size_t semiColonPos = line.find(';');
          do
            {
              semiColonPos = line.find(';');

              const int red   = HowManyColour(line, "red", semiColonPos);
              const int green = HowManyColour(line, "green", semiColonPos);
              const int blue  = HowManyColour(line, "blue", semiColonPos);
    
              lineRounds.emplace_back(red, green, blue);
              line.erase(0, semiColonPos+1);
            }
          while(semiColonPos != std::string::npos);

          int minRed = -1, minGreen = -1, minBlue = -1;

          for(auto const& round : lineRounds)
            round.updateMinimum(minRed, minGreen, minBlue);

          total += minRed * minGreen * minBlue;
        }

      std::cout << "Total: " << total << std::endl;
    }
}

int HowManyColour(const std::string &line, const std::string &name, const size_t end)
{
  const size_t pos = line.find(name);

  if(pos != std::string::npos && pos < end)
    {
      size_t commaPos = line.rfind(',', pos);
      if(commaPos == std::string::npos)
        commaPos = 0;
      else
        commaPos += 1;

      return std::stoi(line.substr(commaPos, pos-1));
    }

  return 0;
}
