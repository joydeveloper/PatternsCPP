#include "stdafx.h"
#include "MyPatterns.h"
using namespace MyPatterns;
using namespace Grower;
bool GrowCondition::GrowUp(int condition)
{
	if (pseed->condition == condition)
	{
		pseed->NextGrow();
		pseed->conditioned = true;
		return true;
	}
	else
		return false;
}
Radiator::Material::Material(float t, float d)
{

	temperature = t;
	durability = d;


}

