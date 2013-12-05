#pragma once

#include "Area.h"

#define MAX_AREA_NUMBER 1

class CCountry
{
public:
	CCountry(std::string name);
	~CCountry();
	void MakeFirstInfactedPerson(int areaIndex);
	void AttemptTransfer();
	int GetNumberOfPersonInCertainState(HumanState state);

protected:
	std::string m_name;
	CArea* m_areas[MAX_AREA_NUMBER];
};
