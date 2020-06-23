#include "Utils.h"

#include <cstdlib>


namespace Utils
{
	float GetRandFloat(const float lower, const float upper)
	{
		return lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upper - lower)));
	}
}