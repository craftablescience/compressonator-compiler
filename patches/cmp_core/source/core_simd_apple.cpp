//
// literally just copied in the CPU algorithm. lmao
//

#include "core_simd.h"

#if defined(_M_X64) || defined(_M_IX86) || defined(x86_64) || defined(i386)
#include <xmmintrin.h>
#include <smmintrin.h>
#elif defined(arm) || defined(_M_ARM) || defined(aarch64)
#include <arm_neon.h>
#else
#include <math.h>
#endif

#include "common_def.h"

#ifndef MAX_ERROR
#define MAX_ERROR 128000.f
#endif

static float cmp_floor_apple(float value)
{
#if defined(_M_X64) || defined(_M_IX86) || defined(x86_64) || defined(i386)
	__m128 vectorValue = _mm_set_ss(value);
    return _mm_cvtss_f32(_mm_floor_ss(vectorValue, vectorValue));
#elif defined(arm) || defined(_M_ARM) || defined(aarch64)
	return vget_lane_f32(vrndm_f32(vdup_n_f32(value)), 0);
#else
	return floor(value);
#endif
}

static float cpu_RampSrchW_apple(float Prj[BLOCK_SIZE_4X4],
                    float PrjErr[BLOCK_SIZE_4X4],
                    float PreMRep[BLOCK_SIZE_4X4],
                    float StepErr,
                    float lowPosStep,
                    float highPosStep,
                    int       dwUniqueColors,
                    int       dwNumPoints)
{
    float error  = 0.0f;
    float step   = (highPosStep - lowPosStep) / (dwNumPoints - 1);
    float step_h = step * 0.5f;
    float rstep  = (float)1.0f / step;
    int   i;

    for (i = 0; i < dwUniqueColors; i++)
    {
        // Work out which value in the block this select
        float del = Prj[i] - lowPosStep;

        float v;

        if (del <= 0)
            v = lowPosStep;
        else if (Prj[i] - highPosStep >= 0)
            v = highPosStep;
        else
            v = cmp_floor_apple((del + step_h) * rstep) * step + lowPosStep;

        // And accumulate the error
        float d = (Prj[i] - v);
        d *= d;
        float err = PreMRep[i] * d + PrjErr[i];
        error += err;
        if (StepErr < error)
        {
            error = StepErr;
            break;
        }
    }
    return error;
}

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
			float error = cpu_RampSrchW_apple(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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
			float error = cpu_RampSrchW_apple(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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
			float error = cpu_RampSrchW_apple(prj, prjError, preMRep, minError, lowStep, highStep, numColours, numPoints);

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
