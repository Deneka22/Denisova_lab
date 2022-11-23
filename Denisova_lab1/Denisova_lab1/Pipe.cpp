#include "Pipe.h"

int pipe::pipeMaxId = 0;

int pipe::getId() 
{
	return pipeMaxId;
}

void pipe::changePipeMaxId(int Id)
{
	pipe::pipeMaxId = Id;
}

string pipe::getName() const
{
	return name;
}

bool pipe::getInRepair() const
{
	return inRepair;
}