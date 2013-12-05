#pragma once

#include "Human.h"

#define MAX_POPULATION 50

class CArea
{
public:
	CArea(std::string name, int initialPopulation );
	~CArea();
	void MakeFirstInfactedPerson();
	void AttemptTransfer();
	int GetNumberOfPersonInCertainState(HumanState state);
	int GetNumberOfPersonInCertainPreviousState(HumanState state);
	void PrintPopulation();
private:
	CHuman* m_humans[MAX_POPULATION];
	std::string m_name;
};

