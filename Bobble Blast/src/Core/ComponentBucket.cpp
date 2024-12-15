#include "../../include/Core/ComponentBucket.h"


size_t ComponentBucket::GetComponentID()
{
	static size_t lastID = 0;

	return lastID++;
}