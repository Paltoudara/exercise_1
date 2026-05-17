#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<random>
double find_how_close(const std::vector<double>& A, const std::vector <double>& x,const std::vector<double>&b, const long long n) {//done
	//
	double error_squared = 0.0;
	//
	#pragma omp parallel for reduction(+:error_squared)
	for (long long i = 0;i < n;i++) {
		double sum = 0.0;
		for (long long j = 0;j < n;j++) {
			sum += A[i * n + j] * x[j];//b_start[i]
		}
		error_squared=error_squared+(sum - b[i])*(sum - b[i]);
	}
	return std::sqrt(error_squared);
}

std::vector<double> jacobi_solver_openmp(const long long n,const std::vector<double>& A,const std::vector<double>& b,
	std::vector<double> x_old,const long long max_iter, const double tol = 1.0e-8) {//done
	//
	std::vector<double> x_new(n,0.0);
	double error = tol + 1.0;
	long long k = 0;
	//
	//
	while (error>tol &&k < max_iter) {
		double sum_sq = 0.0;
		#pragma omp parallel for reduction(+:sum_sq)
		for (long long i = 0; i < n; i++) {
			double sigma = 0.0;
			for (long long j = 0; j < n; j++) {
				if (i != j) {
					sigma += A[i * n + j] * x_old[j];
				}
			}
			x_new[i] = (b[i] - sigma) / A[i * n + i];
			double diff = x_new[i] - x_old[i];
			sum_sq += diff * diff;
		}
		std::swap(x_old, x_new);
		error = std::sqrt(sum_sq);
		k++;
	}
	return x_old;
}

void initialize_matrix_and_vector(std::vector<double>& A,std::vector<double>&b,const long long n) {//done
	std::mt19937_64 gen(std::random_device{}());
	std::uniform_real_distribution<double> ds(1.0, 1000.0);

	for (long long i = 0;i < n;i++) {
		for (long long j = 0;j < n;j++) {
			if (i != j) {
				A[i * n + j] = ds(gen);
			}
			else {
				A[i * n + j] = 0.0;
			}
		}
		b[i] = ds(gen);
	}
	for (long long i = 0;i < n;i++) {
		double sum = 0.0;
		for (long long j = 0;j < n;j++)sum += A[i * n + j];
		A[i * n + i] = sum+ds(gen);
	}

}


int main() {
	
	long long n= 25;
	//
	std::vector<double>A(n*n);
	std::vector<double>b(n);
	std::vector<double>x_first(n,0.0);
	//
	initialize_matrix_and_vector(A,b,n);
	x_first=jacobi_solver_openmp(n, A, b,x_first, 10000);
	//x_first contains the solution
	//
	std::cout << find_how_close(A, x_first, b, n)<<'\n';
	
}
//poly barh do you want me to use it ?
/*if (error(A, x_old, b, n) < tol) {
	std::cout << "found approximate solution" << '\n';
	return;
}*/
