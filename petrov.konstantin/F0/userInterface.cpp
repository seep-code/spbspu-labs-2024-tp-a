#include "userInterface.hpp"
#include <iostream>
#include <fstream>
#include <string>

std::ostream& petrov::UserInterface::readText(std::istream& in, std::ostream& out)
{
  std::string file, name;
  in >> file >> name;
  if (texts_.find(name) != texts_.cend())
  {
    out << "This name is taken. Read anyway y/n: ";
    char ans;
    in >> ans;
    if (ans != 'y')
    {
      return out;
    }
  }
  texts_[name] = file;
  return out;
}
std::ostream& petrov::UserInterface::writeText(std::istream& in, std::ostream& out)
{
  std::string name, file;
  in >> name >> file;
  try
  {
    std::ifstream inFile(texts_.at(name), std::ios::in);
    std::ofstream outFile(file, std::ios::out);
    using isIt = std::istream_iterator< char >;
    using osIt = std::ostream_iterator< char >;
    std::copy(isIt(inFile), isIt(), osIt(outFile));
    inFile.close();
    outFile.close();
  }
  catch (const std::out_of_range&)
  {
    return out << "<INVALID NAME>\n";
  }
}
std::ostream& petrov::UserInterface::deleteText(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;

  auto deletable = texts_.find(name);
  if (deletable == texts_.end())
  {
    return out << "<INVALID NAME>\n";
  }
  texts_.erase(deletable);
  return out;
}
std::ostream& petrov::UserInterface::decode(std::istream& in, std::ostream& out)
{
  std::string codeName, binName, textName;
  in >> codeName >> binName >> textName;

  if (codes_.find(codeName) == codes_.cend())
  {
    return out << "<INVALID CODES NAME>\n";
  }
  if (texts_.find(binName) == texts_.cend())
  {
    return out << "<INVALID READ NAME>\n";
  }

  std::ostream outFile(textName, std::ios::out);
}
