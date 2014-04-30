#include <LevenbergMarquardt.h>

#include <cmath>

#include <Eigen/Dense>

using namespace Eigen;

void Jacobian(MatrixXd& J, const VectorXd& poly, const VectorXd& xobs)
{
	lmu32 N = xobs.rows();
	lmu32 D = poly.rows();

	J.resize(N, D);

	for (size_t i = 0; i < N; i++)
		for (size_t k = 0; k < D; k++)
			J(i, k) = static_cast<lmf64>(std::pow(xobs(i), k));

}

VectorXd Horner(const VectorXd& poly, const VectorXd& xobs)
{
	size_t xobsLength = xobs.rows();
	size_t numCoeffs = poly.rows();

	VectorXd y = VectorXd::Zero(xobsLength);
	auto yarr = y.array();
	auto xarr = xobs.array();

	for (ptrdiff_t i = numCoeffs - 1; i >= 0; i--)
		yarr = (yarr * xarr) + poly(i);

	return yarr.matrix();
}

lmf64 Mu(const MatrixXd& A, lmf64 tau)
{
	lmu32 N = A.rows();

	lmf64 mu = 0.f;

	for (size_t i = 0; i < N; i++)
	{
		lmf64 a = A(i, i);
		if (mu < a)
			mu = a;
	}

	return mu * tau;
}

extern "C"
{
	lmu32 LM_API levenberg_marquardt(
		lmf64* yobs,
		lmu32 yobsLength,
		lmf64* xobs,
		lmu32 xobsLength,
		lmf64* polyptr,
		lmu32 numCoeffs,
		lmf64* e)
	{
		lmf64 e1 = 10e-15f;
		lmf64 e2 = 10e-15f;
		lmf64 e3 = 10e-15f;
		lmf64 tau = 10e-3f;
		lmu32 kmax = 1000;

		if (yobsLength != xobsLength)
			return LM_ARRAY_SIZES_DIFFERENT;

		// initialisation
		VectorXd P = VectorXd::Zero(numCoeffs);

		VectorXd Xobs(xobsLength);
		for (size_t i = 0; i < xobsLength; i++)
			Xobs(i) = xobs[i];

		VectorXd Yobs(yobsLength);
		for (size_t i = 0; i < yobsLength; i++)
			Yobs(i) = yobs[i];

		MatrixXd J;
		Jacobian(J, P, Xobs);

		MatrixXd Jt = J.transpose();
		MatrixXd A = Jt * J;
		MatrixXd Id = MatrixXd::Identity(A.rows(), A.cols());

		// computations
		VectorXd E(yobsLength);
		E = Yobs - Horner(P, Xobs);

		VectorXd G = Jt * E;

		lmu32 k = 0;
		lmf64 nu = 2.f;
		lmf64 mu = Mu(A, tau);

		bool stop = G.cwiseAbs().maxCoeff() < e1;

		while ((stop != true) && (k < kmax))
		{
			k++;
			lmf64 rho = 1.0;

			do
			{
				VectorXd dp = (A + mu * Id).inverse() * G;

				if (dp.dot(dp) < e2*e2*P.dot(P))
					stop = true;
				else
				{
					VectorXd Pnew = P + dp;
					VectorXd Enew = Yobs - Horner(Pnew, Xobs);

					rho = (E.dot(E) - Enew.dot(Enew)) / (dp.dot(mu * dp + G));

					if (rho > 0)
					{
						P = Pnew;
						//A doesn't change
						E = Enew;
						G = Jt * E;

						stop = (G.cwiseAbs().maxCoeff() < e1) || (E.dot(E) < e3);
						mu = mu * std::max((1.0 / 3.0), 1.f - std::pow((2.0 * rho - 1.0), 3));
						nu = 2;
					}
					else
					{
						mu = mu * nu;
						nu = nu * 2;
					}
				}
			} while ((rho <= 0) && (stop == false));
		}

		// copy back results
		for (size_t i = 0; i < numCoeffs; i++)
			polyptr[i] = P(i);

		*e = E.squaredNorm();

		return LM_SUCCESS;
	}
}