#include <spdlog/spdlog.h>

#include <string>
#include <vector>
#include <queue>

#include <thread>
#include <mutex>
#include <future>

#include <chrono>

#include "job.hpp"

using namespace std::chrono_literals;

int main()
{
  auto const core_count = std::thread::hardware_concurrency();

  spdlog::info("This machine has {} cores", core_count);

  auto threads = std::vector<std::thread>{};

  auto th = std::thread(tb::do_thing, "blah");
  threads.push_back(std::move(th)); // Threads are move-only, so have to cast to rvalue if we've already created one as an lvalue

  for (auto const &name : {"one", "two", "three", "four", "five"})
  {
    threads.push_back(std::thread(tb::do_thing, name));
  }

  // Must .join() all the threads otherwise std::terminate() will be called with error "terminate called without an active exception"
  for (auto &thread : threads)
  {
    if (thread.joinable())
    {
      thread.join();
    }
  }


  // Alternatively (and better), use std::async to get return values out of the functions more easily
  // Instead of a vector of threads, use a vector of futures
  auto fut = std::async(std::launch::async, tb::do_thing, "asdf");
  spdlog::info("fut: {}", fut.get());

  std::vector<std::future<bool>> results;

  auto j = tb::job{"runner1"};

  for (auto const &name : {"one", "two", "three", "four", "five"})
  {
    results.emplace_back(std::async(std::launch::async, &tb::job::run, j, name)); // Member functions
    results.emplace_back(std::async(std::launch::async, tb::do_thing, name));     // Regular functions
  }

  for (auto &result : results)
  {
    spdlog::info("result: {}", result.get());
  }

  return EXIT_SUCCESS;
}
