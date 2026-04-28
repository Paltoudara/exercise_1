#include<iostream>
#include<chrono>
#include<cmath>
#include<numbers>
#define NUM_THREADS 1
constexpr int n = 1000;
constexpr double a = 0.0;
constexpr double b = std::numbers::pi;
constexpr double h = (b - a) / (double)n;
constexpr double correct = std::numbers::pi * std::numbers::pi - 4;//what is the result
inline double function_f(const double x)noexcept {
	return x * x * std::sin(x);
}
int main() {
	//parallel part
	double area{};
	auto start_1 = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for  reduction(+:area) num_threads(NUM_THREADS)
	for (int i = 0;i < n;i++) {
		double hprev = a + (double)i * h;
		double hcurr = a + (double)(i + 1) * h;
		area += 0.5 * (function_f(hprev) + function_f(hcurr)) * h;
	}//for
	auto end_1 = std::chrono::high_resolution_clock::now();
	double parallel_time=std::chrono::duration<double>(end_1 - start_1).count();
	std::cout <<"Area :" << area << '\n';
	//serial part


	area = 0.0;
	auto start_2 = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < n;i++) {
		double hprev = a + (double)i * h;
		double hcurr = a + (double)(i + 1) * h;
		area += 0.5 * (function_f(hprev) + function_f(hcurr)) * h;
	}//for
	auto end_2 = std::chrono::high_resolution_clock::now();
	double serial_time=std::chrono::duration<double>(end_2 - start_2).count();
	std::cout << "Area :" << area << "\n\n\n";
	//

	double speedup = serial_time / parallel_time;
	std::cout <<"Serial: " << serial_time << '\n';
	std::cout <<"Parallel: " << parallel_time << '\n';
	std::cout << "Speedup: " << speedup << '\n';
	std::cout << "Efficiency: " << (speedup / NUM_THREADS) * 100 << '\n';
}
