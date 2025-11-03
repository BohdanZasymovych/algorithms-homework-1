#include <chrono>

template <typename T>
void measureOperations(T& obj, int seconds = 10) {
    using namespace std::chrono;
    auto start = steady_clock::now();
    auto end_time = start + seconds(seconds);
    long long ops = 0;

    while (steady_clock::now() < end_time) {
        obj.runOperation();
        ++ops;
    }

    auto elapsed = duration<double>(steady_clock::now() - start).count();
    std::cout << "Ops/sec: " << ops / elapsed << " (" << ops << " total)\n";
}