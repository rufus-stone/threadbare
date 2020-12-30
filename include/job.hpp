#pragma once

#include <string>
#include <future>

#include <spdlog/spdlog.h>

namespace tb
{

class job
{
private:
  std::string const m_id;

public:
  job() = delete;
  job(std::string const &id);
  ~job() = default;

  auto run(std::string const &name) const -> bool;
};


auto do_thing(std::string const &name) -> bool;


} // namespace tb
