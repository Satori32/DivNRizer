#include <iostream>
#include <cstdint>
#include <vector>
#include <random>

typedef std::vector<std::uint8_t> DType;

DType MakeVector0001(std::size_t N, unsigned int S = 0) {
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui(0, 255);
	
	DType R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mt));
	}

	return R;
}

DType NRizer_enc(const DType& In, std::uint8_t S) {
	DType R;

	for (auto& o : In) {
		R.push_back(o / S);
		R.push_back(o % S);
	}

	return R;
}

DType NRizer_dec(const DType& In, std::uint8_t S) {
	DType R;
	bool F = true;
	for (auto& o : In) {
		if (F) {
			R.push_back(o * S);
		}
		else {
			R.back() += o;
		}
		F = !F;
	}

	return R;
}

bool Show0001(const DType& In) {
	for (auto& o : In) {
		std::cout <<(int) o << ",";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	return true;
}

int main() {
	DType D = MakeVector0001(16);
	std::uint8_t N = 16;

	Show0001(D);

	DType E = NRizer_enc(D, N);
	Show0001(E);
	DType X = NRizer_dec(E, N);
	Show0001(X);
	if (D == X) {
		std::cout << "good" << std::endl;
	}
	else {
		std::cout << "Bad" << std::endl;
	}

	return 0;
}