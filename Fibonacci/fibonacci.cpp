#include <chrono>

namespace zx {

class Timer {
  using system_clock = std::chrono::system_clock;
  using resolution = std::chrono::milliseconds;
  std::chrono::time_point<system_clock> m_start, m_end;
  bool m_isRunning;

 public:
  void start() noexcept {
    m_start = system_clock::now();
    m_isRunning = true;
  }
  void stop() noexcept {
    if (!m_isRunning) return;
    m_end = system_clock::now();
    m_isRunning = false;
  }
  uint32_t elapsedTime() noexcept {
    auto elapsed = m_end - m_start;
    return std::chrono::duration_cast<resolution>(elapsed).count();
  }
};

}  // namespace zx

#include <iostream>
#include <string>

#ifdef V1

uint32_t fib(uint32_t n) {
  if (n <= 2) return 1;
  return fib(n - 1) + fib(n - 2);
}

#elif defined V2

uint32_t fib(uint32_t n) noexcept {
  if (n <= 2) return 1;
  return fib(n - 1) + fib(n - 2);
}

#elif defined V3

#include <unordered_map>

std::unordered_map<uint32_t, uint64_t> memo;

uint64_t fib(uint32_t n) noexcept {
  if (n <= 2) return 1;
  if (memo[n]) return memo[n];
  memo[n] = fib(n - 1) + fib(n - 2);
  return memo[n];
}

#endif

uint32_t parseInt(const std::string& s) {
  uint32_t result = 0u;
  for (int i = 0; i < s.size(); ++i) {
    if (i) result *= 10;
    result += s[i] - '0';
  }
  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "invalid argument" << std::endl;
  }

  uint32_t n = parseInt(argv[1]);

  zx::Timer timer;
  timer.start();
  uint32_t result = fib(n);
  timer.stop();
  std::cout << "fib(" << n << ")= " << result
            << ", elapsedTime= " << timer.elapsedTime() << " [ms]" << std::endl;
}
