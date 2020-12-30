#include "job.hpp"

#include <thread>
#include <chrono>

#include <sstream>

#include "prng.hpp"

namespace tb
{

using namespace std::chrono_literals;

job::job(std::string const &id) : m_id(id)
{
  spdlog::info("Created new job runner with id: {}", this->m_id);
}

auto job::run(std::string const &name) const -> bool
{
  bool const result = static_cast<bool>(tb::prng::number_between(0, 1));

  auto const some_ms = std::chrono::milliseconds{tb::prng::number_between(0, 500)};

  auto const start = std::chrono::high_resolution_clock::now();

  std::this_thread::sleep_for(some_ms);

  auto const finish = std::chrono::high_resolution_clock::now();

  auto const nanoseconds_taken = (finish - start); //.count();
  auto const milliseconds_taken = std::chrono::duration<double, std::milli>(nanoseconds_taken).count();

  auto ss = std::stringstream{};
  ss << std::this_thread::get_id();

  spdlog::info("Job '{}' on obj '{}' with thread ID {} returned '{}' after {}ms", name, this->m_id, ss.str(), result, milliseconds_taken);

  return result;
}


auto do_thing(std::string const &name) -> bool
{
  bool const result = static_cast<bool>(tb::prng::number_between(0, 1));

  auto const some_ms = std::chrono::milliseconds{tb::prng::number_between(0, 500)};

  auto const start = std::chrono::high_resolution_clock::now();

  std::this_thread::sleep_for(some_ms);

  auto const finish = std::chrono::high_resolution_clock::now();

  auto const nanoseconds_taken = (finish - start); //.count();
  auto const milliseconds_taken = std::chrono::duration<double, std::milli>(nanoseconds_taken).count();

  auto ss = std::stringstream{};
  ss << std::this_thread::get_id();

  spdlog::info("Job '{}' with thread ID {} returned '{}' after {}ms", name, ss.str(), result, milliseconds_taken);

  return result;
}

} // namespace tb
