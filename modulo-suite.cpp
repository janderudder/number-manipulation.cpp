#include <iostream>

int main(int const argc, char** argv)
{
	using N = unsigned;

	N m    = (argc > 1) ? atoi(argv[1]) : 10;
	N nmax = (argc > 2) ? atoi(argv[2]) : 10;

	std::cout << "m: " << m << "\n";
	std::cout << "nmax: " << nmax << "\n";

	for (N n=0; n <= nmax; ++n) {
		const N modulo = n % m;
		std::cout << modulo << "\n";
	}
}
