#pragma once
#include "Human.h"

//class CHuman;
#define POPULATION 652

struct HumanParam {
	std::string name;
	Cleanliness cleanliness;
	Sociability sociability;
};

enum Climate {
	TROPICAL,
	TEMPERATE,
	POLAR
};
//// ����������� �Ӽ��� �����ϴ� �Ӽ�
// �������� ���� ���������� ���� ����� ���� ����.
enum CountryLevel {
	UNDEVELOPED,
	DEVELOPING,
	DEVELOPED
};
// �α��е��� ���� ���� ������� �δ볥Ȯ���� ��������. ������ �Ҽź���Ƽ ���
enum PopulationDensity {
	LOW_DENSITY,
	MEDIUM_DENSITY,
	HIGH_DENSITY
};
class CCountry
{
public:
	CCountry(std::string name, Climate climate, CountryLevel countryLevel, PopulationDensity populationDensity);
	~CCountry();
	void printInfo();
	std::string getName(){ return m_Name; };
	int getNumberOfPersonInCertainState(InfectionState infectionState);
	CHuman** getPopulation(){ return m_Population; };
	int* getInfectedHumanIndex();
	Climate getClimate(){ return m_Climate; };

protected:
	std::string	m_Name;
	Climate m_Climate;
	CountryLevel m_CountryLevel;
	PopulationDensity m_PopulationDensity;

	CHuman* m_Population[POPULATION];

	std::string getCountryInfoString();
	std::string getClimateString(Climate climate);
	std::string getCountryLevelString(CountryLevel countryLevel);
	std::string getPopulationDensityString(PopulationDensity populationDensity);

	HumanParam getRandomNewHumanParam(CountryLevel m_CountryLevel, PopulationDensity m_PopulationDensity);
};

