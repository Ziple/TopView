#include <LevenbergMarquardt.h>

#include <iostream>

int main(int argc, char** argv)
{
	lmf32 p[] = {1.25f, 2.23f, 3.16f, 2.68f };
	lmu32 numCoeffs = 4;

	lmf32 pg[4];
	lmf32 e = 0.f;

	lmf32 pgd[4];
	lmf32 ed = 0.f;

	lmu32 numSamples = 100;
	lmf32 *xobs = new lmf32[numSamples];
	lmf32 *yobs = new lmf32[numSamples];

	for (size_t i = 0; i < numSamples; i++)
	{
		xobs[i] = lmf32(i) / (numSamples - 1);

		yobs[i] = 0.f;
		for (ptrdiff_t j = numCoeffs - 1;j >= 0; j--)
			yobs[i] = yobs[i] * xobs[i] + p[j];
	}

	levenberg_marquardt(yobs, numSamples, xobs, numSamples, pg, numCoeffs, &e);

	std::cout << "Guessed polynom (LM): " << pg[3] << "*x^3 + " << pg[2] << "*x^2 + " << pg[1] << "*x + " << pg[0] << std::endl;

	direct_resolution(yobs, numSamples, xobs, numSamples, pgd, numCoeffs, &ed);

	std::cout << "Guessed polynom (D): " << pgd[3] << "*x^3 + " << pgd[2] << "*x^2 + " << pgd[1] << "*x + " << pgd[0] << std::endl;

	delete[] yobs;
	delete[] xobs;

	return 0;
}