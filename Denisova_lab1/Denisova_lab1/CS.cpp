#include "CS.h"

int compressorStation::csMaxId = 0;

int compressorStation::getId()
{
	return csMaxId;
}

void compressorStation::changeCsMaxId(int Id)
{
	compressorStation::csMaxId = Id;
}

int compressorStation::getAllShop() const
{
	return allShop;
}
int compressorStation::getWorkShop() const
{
	return workShop;
}


string compressorStation::getName() const
{
	return name;
}