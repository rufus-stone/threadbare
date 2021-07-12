#pragma once

#include <mutex>
#include <string>

namespace tb
{

struct pod
{
  std::mutex mtx;

  std::string s1 = "asdf";
  std::string s2;

  void write_s1(std::string const &s)
  {
    std::lock_guard<std::mutex> lg{mtx};
    s1 = s;
  }

  std::string read_s1()
  {
    std::lock_guard<std::mutex> lg{mtx};
    return s1;
  }
};

} // namespace tb