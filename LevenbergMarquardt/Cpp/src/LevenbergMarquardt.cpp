#include <LevenbergMarquardt.h>

#include <cmath>

#include <Eigen/Dense>

using namespace Eigen;

void Jacobian(MatrixXf& J, const VectorXf& poly, const VectorXf& xobs)
{
	lmu32 N = xobs.rows();
	lmu32 D = poly.rows();

	J.resize(N, D);

	for (size_t i = 0; i < N; i++)
		for (size_t k = 0; k < D; k++)
			J(i, k) = static_cast<lmf32>( std::pow(xobs(i), k) );

}

void Jacobian(MatrixXd& J, const VectorXd& poly, const VectorXd& xobs)
{
	lmu32 N = xobs.rows();
	lmu32 D = poly.rows();

	J.resize(N, D);

	for (size_t i = 0; i < N; i++)
		for (size_t k = 0; k < D; k++)
			J(i, k) = static_cast<lmf64>(std::pow(xobs(i), k));

}

VectorXf Horner(const VectorXf& poly, const VectorXf& xobs)
{
	size_t xobsLength = xobs.rows();
	size_t numCoeffs = poly.rows();

	VectorXf y = VectorXf::Zero(xobsLength);
	auto yarr = y.array();
	auto xarr = xobs.array();

	for (ptrdiff_t i = numCoeffs-1; i >= 0; i--)
		yarr = (yarr * xarr) + poly(i);

	return yarr.matrix();
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

lmf32 Mu(const MatrixXf& A, lmf32 tau)
{
	lmu32 N = A.rows();

	lmf32 mu = 0.f;

	for (size_t i = 0; i < N; i++)
	{
		lmf32 a = A(i, i);
		if (mu < a)
			mu = a;
	}

	return mu * tau;
}

lmu32 LM_API levenberg_marquardt(
	lmf32* yobs,
	lmu32 yobsLength,
	lmf32* xobs,
	lmu32 xobsLength,
	lmf32* polyptr,
	lmu32 numCoeffs,
	lmf32* e)
{
	lmf32 e1 = 10e-15f;
	lmf32 e2 = 10e-15f;
	lmf32 e3 = 10e-15f;
	lmf32 tau = 10e-3f;
	lmu32 kmax = 100;

	if (yobsLength != xobsLength)
		return LM_ARRAY_SIZES_DIFFERENT;

	// initialisation
	VectorXf P = VectorXf::Zero(numCoeffs);

	VectorXf Xobs(xobsLength);
	for (size_t i = 0; i < xobsLength; i++)
		Xobs(i) = xobs[i];

	VectorXf Yobs(yobsLength);
	for (size_t i = 0; i < yobsLength; i++)
		Yobs(i) = yobs[i];

	MatrixXf J;
	Jacobian(J, P, Xobs);

	MatrixXf Jt = J.transpose();
	MatrixXf A = Jt * J;
	MatrixXf Id = MatrixXf::Identity( A.rows(), A.cols() );

	// computations
	VectorXf E(yobsLength);
	E = Yobs - Horner(P, Xobs);

	VectorXf G = Jt * E;

	lmu32 k = 0;
	lmf32 nu = 2.f;
	lmf32 mu = Mu(A, tau);

	bool stop = G.cwiseAbs().maxCoeff() < e1;

	while ((stop != true) && (k < kmax))
	{
		k++;
		lmf32 rho = 1;

		do
		{
			VectorXf dp = (A + mu * Id).inverse() * G;

			if (dp.dot(dp) < e2*e2*P.dot(P))
				stop = true;
			else
			{
				VectorXf Pnew = P + dp;
				VectorXf Enew = Yobs - Horner(Pnew, Xobs);

				rho = (E.dot(E) - Enew.dot(Enew)) / (dp.dot(mu * dp + G) );

					if (rho > 0)
					{
						P = Pnew;
						//A doesn't change
						E = Enew;
						G = Jt * E;

						stop = (G.cwiseAbs().maxCoeff() < e1) || (E.dot(E) < e3);
						mu = mu * std::max((1.f / 3.f), 1.f - std::pow((2.f * rho - 1.f), 3));
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

lmu32 LM_API direct_resolution(
	lmf32* yobs,
	lmu32 yobsLength,
	lmf32* xobs,
	lmu32 xobsLength,
	lmf32* polyptr,
	lmu32 numCoeffs,
	lmf32* e)
{
	lmf32 e1 = 10e-15f;
	lmf32 e2 = 10e-15f;
	lmf32 e3 = 10e-15f;
	lmf32 tau = 10e-3f;
	lmu32 kmax = 100;

	if (yobsLength != xobsLength)
		return LM_ARRAY_SIZES_DIFFERENT;

	// initialisation
	VectorXd P = VectorXd::Zero(numCoeffs);

	VectorXd Xobs(xobsLength);
	for (size_t i = 0; i < xobsLength; i++)
		Xobs(i) = static_cast<lmf64>( xobs[i] );

	VectorXd Yobs(yobsLength);
	for (size_t i = 0; i < yobsLength; i++)
		Yobs(i) = static_cast<lmf64>( yobs[i] );

	MatrixXd J;
	Jacobian(J, P, Xobs);

	MatrixXd Jt = J.transpose();
	MatrixXd A = Jt * J;

	// computations
	P = A.inverse() * (Jt * Yobs);

	// copy back results
	for (size_t i = 0; i < numCoeffs; i++)
		polyptr[i] = static_cast<lmf32>( P(i) );

	VectorXd E(yobsLength);
	E = Yobs - Horner(P, Xobs);
	*e = static_cast<lmf32>( E.squaredNorm() );

	return LM_SUCCESS;
}