//
// literally just copied in the CPU algorithm. lmao
//

#include "core_simd.h"

CGU_FLOAT sse_bc1ComputeBestEndpoints(CGU_FLOAT endpointsOut[2],
                                      CGU_FLOAT endpointsIn[2],
                                      CGU_FLOAT prj[16],
                                      CGU_FLOAT prjError[16],
                                      CGU_FLOAT preMRep[16],
                                      int       numColours,
                                      int       numPoints)
{
	CGU_FLOAT minError = MAX_ERROR;

	static const CGU_FLOAT searchStep = 0.025f;

	const CGU_FLOAT lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const CGU_FLOAT highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	CGU_FLOAT lowStep  = lowStart;
	CGU_FLOAT highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			CGU_FLOAT error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

			if (error < minError)
			{
				// save better result
				minError        = error;
				endpointsOut[0] = lowStep;
				endpointsOut[1] = highStep;
			}

			highStep -= searchStep;
		}

		lowStep += searchStep;
	}

	return minError;
}

CGU_FLOAT avx_bc1ComputeBestEndpoints(CGU_FLOAT endpointsOut[2],
                                      CGU_FLOAT endpointsIn[2],
                                      CGU_FLOAT prj[16],
                                      CGU_FLOAT prjError[16],
                                      CGU_FLOAT preMRep[16],
                                      int       numColours,
                                      int       numPoints)
{
	CGU_FLOAT minError = MAX_ERROR;

	static const CGU_FLOAT searchStep = 0.025f;

	const CGU_FLOAT lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const CGU_FLOAT highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	CGU_FLOAT lowStep  = lowStart;
	CGU_FLOAT highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			CGU_FLOAT error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

			if (error < minError)
			{
				// save better result
				minError        = error;
				endpointsOut[0] = lowStep;
				endpointsOut[1] = highStep;
			}

			highStep -= searchStep;
		}

		lowStep += searchStep;
	}

	return minError;
}

CGU_FLOAT avx512_bc1ComputeBestEndpoints(CGU_FLOAT endpointsOut[2],
                                      CGU_FLOAT endpointsIn[2],
                                      CGU_FLOAT prj[16],
                                      CGU_FLOAT prjError[16],
                                      CGU_FLOAT preMRep[16],
                                      int       numColours,
                                      int       numPoints)
{
	CGU_FLOAT minError = MAX_ERROR;

	static const CGU_FLOAT searchStep = 0.025f;

	const CGU_FLOAT lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const CGU_FLOAT highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	CGU_FLOAT lowStep  = lowStart;
	CGU_FLOAT highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			CGU_FLOAT error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

			if (error < minError)
			{
				// save better result
				minError        = error;
				endpointsOut[0] = lowStep;
				endpointsOut[1] = highStep;
			}

			highStep -= searchStep;
		}

		lowStep += searchStep;
	}

	return minError;
}
