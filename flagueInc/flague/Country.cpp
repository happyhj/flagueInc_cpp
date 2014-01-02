#include "stdafx.h"
#include "Country.h"



CCountry::CCountry(std::string name, Climate climate, CountryLevel countryLevel, PopulationDensity populationDensity)
{
	m_Name = name;
	m_Climate = climate;
	m_CountryLevel = countryLevel;
	m_PopulationDensity = populationDensity;

	// 기준에 맞게 인구를 생성한다.
	for (int i = 0; i < POPULATION; i++) {
		HumanParam newHumanParam = getRandomNewHumanParam(m_CountryLevel, m_PopulationDensity);
		m_Population[i] = new CHuman(newHumanParam.name, newHumanParam.cleanliness, newHumanParam.sociability);
		//m_Population[i]->printInfo();
	}
}

CCountry::~CCountry()
{

}
HumanParam CCountry::getRandomNewHumanParam(CountryLevel m_CountryLevel, PopulationDensity m_PopulationDensity)
{
	HumanParam humanParam;

	humanParam.cleanliness = LOW_CLEANLINESS;
	humanParam.name = "김희재";
	humanParam.sociability = LOW_SOCIABILITY;

	return humanParam;
}

void CCountry::printInfo()
{
	std::string logString = getCountryInfoString();

	std::cout << logString << std::endl;
}

std::string CCountry::getCountryInfoString()
{
	std::string logString = "";
	logString = "Name : " + m_Name + "\n";
	logString = logString + "Climate : " + getClimateString(m_Climate) + "\n";
	logString = logString + "CountryLevel : " + getCountryLevelString(m_CountryLevel) + "\n";
	logString = logString + "HealtyPopulation : " + std::to_string(getNumberOfPersonInCertainState(NOT_INFECTED_YET)) + "\n";
	logString = logString + "InfactesPopulation : " + std::to_string(getNumberOfPersonInCertainState(INFECTED)) + "\n";

	return logString;
}


std::string CCountry::getClimateString(Climate climate) {
	std::string result = "";
	switch (climate) {
	case 0:
		result = "TROPICAL";
		break;
	case 1:
		result = "TEMPERATE";
		break;
	case 2:
		result = "POLAR";
		break;
	default:
		result = "Climate??";
		break;
	}
	return result;
}
std::string CCountry::getCountryLevelString(CountryLevel countryLevel)
{
	std::string result = "";
	switch (countryLevel) {
	case 0:
		result = "UNDEVELOPED";
		break;
	case 1:
		result = "DEVELOPING";
		break;
	case 2:
		result = "DEVELOPED";
		break;
	default:
		result = "CountryLevel??";
		break;
	}
	return result;
}
std::string CCountry::getPopulationDensityString(PopulationDensity populationDensity)
{
	std::string result = "";
	switch (populationDensity) {
	case 0:
		result = "LOW_DENSITY";
		break;
	case 1:
		result = "MEDIUM_DENSITY";
		break;
	case 2:
		result = "HIGH_DENSITY";
		break;
	default:
		result = "PopulationDensity??";
		break;
	}
	return result;
}

int CCountry::getNumberOfPersonInCertainState(InfectionState infectionState)
{
	int counter = 0;

//	CHuman** m_humans = m_TargetCountry->getPopulation();
//	CHuman* targetHuman = *(m_humans + targetIndex);
	InfectionState targetInfectionState;
//	std::cout << sizeof(m_Population) / sizeof(m_Population[0]) << std::endl;
//	targetInfectionState = m_Population[900]->getInfectionStatus();

	for (int i = 0; i < POPULATION; i++)
	{
		targetInfectionState = m_Population[i]->getInfectionStatus();
		if (targetInfectionState == infectionState) {
			counter++;
		}
	}
	return counter;
}

int* CCountry::getInfectedHumanIndex()
{
	int numOfInfectee = getNumberOfPersonInCertainState(INFECTED);
	// 기존 감염자들의 인덱스로 이루어진 배열을 생성한다.
	int* InfectedIndex = new int[numOfInfectee];
	int infectedCounter = 0;
	for (int i = 0; i < POPULATION; i++){
		if (m_Population[i]->getInfectionStatus() == INFECTED) {
			InfectedIndex[infectedCounter] = i;
			infectedCounter++;
		}
	}
	return InfectedIndex;
}
