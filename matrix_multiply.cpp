#include<iostream>
#include<chrono>
#include<cstdlib>
#include<new>
#include<cmath>
constexpr int n{ 2000 };
constexpr int NUM_THREADS{ 3 };
int main(void)
{
	double sum, * u, * a, * b;
	u = new double[n * n];
	a = new double[n * n];
	b = new double[n * n];
	for (int j = 0;j < n;j++) {
		for (int i = 0;i < n;i++) {
			a[j * n + i] = 1.0;
			b[j * n + i] = 1.0;
			u[j * n + i] = 0.0;
		}
	}
	//
	auto start = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for shared(a,b,u) private(sum) num_threads(NUM_THREADS)
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			sum = 0.0;
			for (int k = 0;k <n;k++) {
				sum += a[j * n + k] * b[k * n + i];
			}
			u[j * n + i] = sum;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	//
	double parallel_time=std::chrono::duration<double>(end - start).count();
	//
	std::cout<<parallel_time<<'\n';
}
