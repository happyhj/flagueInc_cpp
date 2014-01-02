#include "stdafx.h"
#include "Disease.h"
#include "Country.h"

CDisease::CDisease(std::string name)
{
	this->m_Name = name;
	// 게임 시작 시에는 모든 능력치가 최저에서 시작된다.
	this->m_FrozenResistance = EXTRA_LOW_FROZEN_RESISTANCE;
	this->m_HeatResistance = EXTRA_LOW_HEAT_RESISTANCE;
	this->m_Cough = EXTRA_WEAK_COUGH;
	this->m_Laziness = EXTRA_LOW_LAZINESS;
}


CDisease::CDisease(std::string name,CCountry* country)
{
	this->m_Name = name;
	// 게임 시작 시에는 모든 능력치가 최저에서 시작된다.
	this->m_FrozenResistance = EXTRA_LOW_FROZEN_RESISTANCE;
	this->m_HeatResistance = EXTRA_LOW_HEAT_RESISTANCE;
	this->m_Cough = EXTRA_WEAK_COUGH;
	this->m_Laziness = EXTRA_LOW_LAZINESS;

	m_TargetCountry = country;
}


CDisease::~CDisease()
{
}

void CDisease::printInfo()
{
	std::cout << getDiseaseInfoString() << std::endl;
}


std::string CDisease::getDiseaseInfoString()
{
	std::string logString = "";
	logString = "Name : " + m_Name + "\n";
	logString = logString + "FrozenResistance : " + getFrozenResistanceString(m_FrozenResistance) + "\n";
	logString = logString + "HeatResistance : " + getHeatResistanceString(m_HeatResistance) + "\n";
	logString = logString + "Cough : " + getCoughString(m_Cough) + "\n";
	logString = logString + "Laziness : " + getLazinessString(m_Laziness) + "\n";

	return logString;
}
std::string CDisease::getFrozenResistanceString(FrozenResistance frozenResistance)
{
	std::string result = "";
	switch (frozenResistance) {
	case 0:
		result = "EXTRA_LOW_FROZEN_RESISTANCE";
		break;
	case 1:
		result = "LOW_FROZEN_RESISTANCE";
		break;
	case 2:
		result = "MEDIUM_FROZEN_RESISTANCE";
		break;
	case 3:
		result = "HIGH_FROZEN_RESISTANCE";
		break;
	case 4:
		result = "EXTRA_HIGH_FROZEN_RESISTANCE";
		break;
	default:
		result = "FrozenResistance??";
		break;
	}
	return result;
}
std::string CDisease::getHeatResistanceString(HeatResistance heatResistance)
{
	std::string result = "";
	switch (heatResistance) {
	case 0:
		result = "EXTRA_LOW_HEAT_RESISTANCE";
		break;
	case 1:
		result = "LOW_HEAT_RESISTANCE";
		break;
	case 2:
		result = "MEDIUM_HEAT_RESISTANCE";
		break;
	case 3:
		result = "HIGH_HEAT_RESISTANCE";
		break;
	case 4:
		result = "EXTRA_HIGH_HEAT_RESISTANCE";
		break;
	default:
		result = "HeatResistance??";
		break;
	}
	return result;
}
std::string CDisease::getCoughString(Cough cough)
{
	std::string result = "";
	switch (cough) {
	case 0:
		result = "EXTRA_WEAK_COUGH";
		break;
	case 1:
		result = "WEAK_COUGH";
		break;
	case 2:
		result = "MEDIUM_COUGH";
		break;
	case 3:
		result = "STRONG_COUGH";
		break;
	case 4:
		result = "EXTRA_STRONG_COUGH";
		break;
	default:
		result = "Cough??";
		break;
	}
	return result;
}
std::string CDisease::getLazinessString(Laziness laziness)
{
	std::string result = "";
	switch (laziness) {
	case 0:
		result = "EXTRA_LOW_LAZINESS";
		break;
	case 1:
		result = "LOW_LAZINESS";
		break;
	case 2:
		result = "MEDIUM_LAZINESS";
		break;
	case 3:
		result = "HIGH_LAZINESS";
		break;
	case 4:
		result = "EXTRA_HIGH_LAZINESS";
		break;
	default:
		result = "Laziness??";
		break;
	}
	return result;
}
int CDisease::getTransmitResult()
{
	// 나라의 기후와 병원균의 능력치에 의해 결정된다.
	Climate climate = m_TargetCountry->getClimate();
	int FRIdx = (int) m_FrozenResistance + 1; // 1~5
	int HRIdx = (int) m_HeatResistance + 1; // 1~5

	// 가중치를 달리 주어 최종 확률을 구한다.
	// 최종확률은 0에서 10까지의 정수값을 가진다. 100 이 100% 를 의미
	int totalProbability;

	// 추운 곳일 경우 냉기저항에 따라 평균조절
	switch (climate) 
	{ 
	case(TROPICAL) :
		totalProbability = ((FRIdx + 3*HRIdx) / 2) * 5;
		break;
	case(TEMPERATE) :
		totalProbability = (FRIdx + HRIdx) * 5;
		if (totalProbability < 10) 
		{
			// 기본 난이도를 낮추기위한 확률 높이기
			totalProbability = totalProbability + 2;
		}
		break;
	case(POLAR) :
		totalProbability = ((3*FRIdx + HRIdx) / 2) * 5;
		break;
	default:
		break;
	}

//	totalProbability = 30; 최고확률은 30%

//	srand((unsigned)time(NULL)); // 난수 발생초기화
	int randomInteger = rand() % 100;
	//std::cout << "totalProbability:" << totalProbability << " randomInteger:" << randomInteger << std::endl;
	//Sleep(1000);
	if (randomInteger <= totalProbability) {
		return (int) TRANSMIT_SUCCESS;
	}
	else {
		return (int) TRANSMIT_FAIL;
	}
	
}
int CDisease::attemptTransfer()
{
	int numOfInfectee = m_TargetCountry->getNumberOfPersonInCertainState(INFECTED);
	int numOfHuman = POPULATION;
	
	
	// 감염자가 존재한다면
	if (numOfInfectee > 0)
	{
		// 기존 감염자들의 인덱스로 이루어진 배열을 생성한다.
		int* InfectedIndex = m_TargetCountry->getInfectedHumanIndex();

		for (int i = 0; i < numOfInfectee; i++){

			//// 한번 전염시키는 루틴, 한명이 한번에 여러명에게 전염시도 시 반복문 처리함.
			//병원균 전달 성공율을 결정.. 
			TransmitResult result = TRANSMIT_FAIL;
			result = (TransmitResult)getTransmitResult();

			int targetIndex = rand() % (numOfHuman - 1);
			if (targetIndex >= InfectedIndex[i])
			{
				targetIndex++;
			}

			CHuman** m_humans = m_TargetCountry->getPopulation();
			// m_TargetCountry = new CCountry("미쿸", (Climate)0, (CountryLevel)0, (PopulationDensity)0);

			// 전염 시킨다..
			//)->InfectionCheck((TransmitResult)result));
			CHuman* targetHuman = *(m_humans + targetIndex);
			bool isNewInfactee = targetHuman->InfectionCheck((TransmitResult)result);
		}
		delete[] InfectedIndex;
	}
	int numOfInfecteeAfterTransfer = m_TargetCountry->getNumberOfPersonInCertainState(INFECTED);

	int numOfNewInfectee = numOfInfecteeAfterTransfer - numOfInfectee;
	return numOfNewInfectee;
}

void CDisease::makeFirstInfactee() // 아무감염자가 없는 나라에 첫 감염자를 발생시킨다.
{
	srand((unsigned)time(NULL)); // 난수 발생초기화

	int targetIndex = rand() % POPULATION;
	std::cout << targetIndex;
	CHuman** m_humans = m_TargetCountry->getPopulation();
	CHuman* targetHuman = *(m_humans + targetIndex);
	targetHuman->InfectionCheck(TRANSMIT_SUCCESS);
	
	//std::string humanInfo = targetHuman->getHumanInfoString();
	//bool isNewInfactee = ((CHuman*)(m_humans + targetIndex))->InfectionCheck((TransmitResult)TRANSMIT_SUCCESS);
	//std::cout << "targetIndex:" << targetIndex << humanInfo << std::endl;

}
void  CDisease::upgradeFrozenResistance()
{
	m_FrozenResistance = (FrozenResistance) ((int)m_FrozenResistance + 1);
}// 
void  CDisease::upgradeHeatResistance()
{
	m_HeatResistance = (HeatResistance)((int)m_HeatResistance + 1);
}//
