#include <iostream>
#include "FlatMap.h"

typedef FlatMap<int, int> FM;

bool Test01(const FM& F) {
	auto X = F[1];
	return true;
}

int main() {
	FM F;

	for (int i = 0; i < 16; i++) {
		F[i] = i;
	}
	F.sort();
	Test01(F);
	//FM.sort([](auto& A, auto& B) {return A < B; });
	return 0;
}