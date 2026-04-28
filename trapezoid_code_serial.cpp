#include<iostream>
#include<chrono>
#include<cmath>
#include<numbers>
constexpr int n = 1000;
constexpr double a = 0.0;
constexpr double b = std::numbers::pi;
constexpr double h = (b - a) / (double)n;
constexpr double correct = std::numbers::pi * std::numbers::pi - 4;//what is the result
inline double function_f(const double x)noexcept {
	return x * x * std::sin(x);
}
int main() {
	
	double area{};
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < n;i++) {
		double hprev = a + (double)i * h;
		double hcurr = a + (double)(i + 1) * h;
		area += 0.5 * (function_f(hprev) + function_f(hcurr)) * h;
	}//for
	auto end = std::chrono::high_resolution_clock::now();
	double serial_time=std::chrono::duration<double>(end - start).count();
	std::cout <<"Area: " << area << '\n';
	std::cout<<"Correct Area: "<<correct<<'\n';
  	std::cout<<"Serial: "<<serial_time<<'\n';

	//serial part
}
