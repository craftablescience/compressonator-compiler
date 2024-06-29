//
// literally just copied in the CPU algorithm. lmao
//

#include "core_simd.h"

float sse_bc1ComputeBestEndpoints(float endpointsOut[2],
                                  float endpointsIn[2],
                                  float prj[16],
                                  float prjError[16],
                                  float preMRep[16],
                                  int       numColours,
                                  int       numPoints)
{
	float minError = MAX_ERROR;

	static const float searchStep = 0.025f;

	const float lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const float highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	float lowStep  = lowStart;
	float highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			float error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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

float avx_bc1ComputeBestEndpoints(float endpointsOut[2],
                                  float endpointsIn[2],
                                  float prj[16],
                                  float prjError[16],
                                  float preMRep[16],
                                  int       numColours,
                                  int       numPoints)
{
	float minError = MAX_ERROR;

	static const float searchStep = 0.025f;

	const float lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const float highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	float lowStep  = lowStart;
	float highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			float error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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

float avx512_bc1ComputeBestEndpoints(float endpointsOut[2],
                                     float endpointsIn[2],
                                     float prj[16],
                                     float prjError[16],
                                     float preMRep[16],
                                     int       numColours,
                                     int       numPoints)
{
	float minError = MAX_ERROR;

	static const float searchStep = 0.025f;

	const float lowStart  = (endpointsIn[0] - 2.0f * searchStep > 0.0f) ? endpointsIn[0] - 2.0f * searchStep : 0.0f;
	const float highStart = (endpointsIn[1] + 2.0f * searchStep < 1.0f) ? endpointsIn[1] + 2.0f * searchStep : 1.0f;

	float lowStep  = lowStart;
	float highStep = highStart;

	for (int low = 0; low < 8; ++low)
	{
		for (int high = 0; high < 8; ++high)
		{
			// compute an error for the current pair of end points.
			float error = cpu_RampSrchW(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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
