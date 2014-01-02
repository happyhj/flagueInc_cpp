#include "stdafx.h"
#include "Disease.h"
#include "Country.h"

CDisease::CDisease(std::string name)
{
	this->m_Name = name;
	// ���� ���� �ÿ��� ��� �ɷ�ġ�� �������� ���۵ȴ�.
	this->m_FrozenResistance = EXTRA_LOW_FROZEN_RESISTANCE;
	this->m_HeatResistance = EXTRA_LOW_HEAT_RESISTANCE;
	this->m_Cough = EXTRA_WEAK_COUGH;
	this->m_Laziness = EXTRA_LOW_LAZINESS;
}


CDisease::CDisease(std::string name,CCountry* country)
{
	this->m_Name = name;
	// ���� ���� �ÿ��� ��� �ɷ�ġ�� �������� ���۵ȴ�.
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
	// ������ ���Ŀ� �������� �ɷ�ġ�� ���� �����ȴ�.
	Climate climate = m_TargetCountry->getClimate();
	int FRIdx = (int) m_FrozenResistance + 1; // 1~5
	int HRIdx = (int) m_HeatResistance + 1; // 1~5

	// ����ġ�� �޸� �־� ���� Ȯ���� ���Ѵ�.
	// ����Ȯ���� 0���� 10������ �������� ������. 100 �� 100% �� �ǹ�
	int totalProbability;

	// �߿� ���� ��� �ñ����׿� ���� �������
	switch (climate) 
	{ 
	case(TROPICAL) :
		totalProbability = ((FRIdx + 3*HRIdx) / 2) * 5;
		break;
	case(TEMPERATE) :
		totalProbability = (FRIdx + HRIdx) * 5;
		if (totalProbability < 10) 
		{
			// �⺻ ���̵��� ���߱����� Ȯ�� ���̱�
			totalProbability = totalProbability + 2;
		}
		break;
	case(POLAR) :
		totalProbability = ((3*FRIdx + HRIdx) / 2) * 5;
		break;
	default:
		break;
	}

//	totalProbability = 30; �ְ�Ȯ���� 30%

//	srand((unsigned)time(NULL)); // ���� �߻��ʱ�ȭ
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
	
	
	// �����ڰ� �����Ѵٸ�
	if (numOfInfectee > 0)
	{
		// ���� �����ڵ��� �ε����� �̷���� �迭�� �����Ѵ�.
		int* InfectedIndex = m_TargetCountry->getInfectedHumanIndex();

		for (int i = 0; i < numOfInfectee; i++){

			//// �ѹ� ������Ű�� ��ƾ, �Ѹ��� �ѹ��� �������� �����õ� �� �ݺ��� ó����.
			//������ ���� �������� ����.. 
			TransmitResult result = TRANSMIT_FAIL;
			result = (TransmitResult)getTransmitResult();

			int targetIndex = rand() % (numOfHuman - 1);
			if (targetIndex >= InfectedIndex[i])
			{
				targetIndex++;
			}

			CHuman** m_humans = m_TargetCountry->getPopulation();
			// m_TargetCountry = new CCountry("�̳k", (Climate)0, (CountryLevel)0, (PopulationDensity)0);

			// ���� ��Ų��..
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

void CDisease::makeFirstInfactee() // �ƹ������ڰ� ���� ���� ù �����ڸ� �߻���Ų��.
{
	srand((unsigned)time(NULL)); // ���� �߻��ʱ�ȭ

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
