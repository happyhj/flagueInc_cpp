#include "stdafx.h"
#include "Human.h"



CHuman::CHuman(std::string	name, Cleanliness cleanliness, Sociability sociability)
{
	m_Name = name;
	// ����� �ɷ�ġ�� ������ �����ϴ°��� �ƴ϶� �Ҽ��� ���� �ڽ��� �Ӽ��� ���� Ȯ�������� �����Ѵ�.
	m_Cleanliness = cleanliness;
	m_Sociability = sociability;
	m_Immuned = false;
	m_InfectionState = NOT_INFECTED_YET;
	m_PreviousInfectionState = NOT_INFECTED_YET;
	//printInfo(); 
}


CHuman::~CHuman()
{
}

void CHuman::printInfo()
{
	std::string logString = getHumanInfoString();

	std::cout << logString << std::endl;
}

std::string CHuman::getHumanInfoString()
{
	std::string logString = "";
	std::string humanInfo = "";
	logString = "Name : " + this->m_Name + "\n";
	logString = logString + "Cleanliness : " + getCleanlinessString(this->m_Cleanliness) + "\n";
	logString = logString + "Sociability : " + getSociabilityString(this->m_Sociability) + "\n";
	logString = logString + "InfectionState : " + getInfectionStateString(this->m_InfectionState) + "\n";

	return logString;
}

std::string CHuman::getCleanlinessString(Cleanliness cleanliness) {
	std::string result = "";
	switch (cleanliness) {
	case 0:
		result = "LOW_CLEANLINESS";
		break;
	case 1:
		result = "MEDIUM_CLEANLINESS";
		break;
	case 2:
		result = "HIGH_CLEANLINESS";
		break;
	default:
		result = "Cleanliness??";
		break;
	}
	return result;
}

std::string CHuman::getSociabilityString(Sociability sociability) {
	std::string result = "";
	switch (sociability) {
	case 0:
		result = "LOW_SOCIABILITY";
		break;
	case 1:
		result = "MEDIUM_SOCIABILITY";
		break;
	case 2:
		result = "HIGH_SOCIABILITY";
		break;
	default:
		result = "sociability??";
		break;
	}
	return result;
}

std::string CHuman::getInfectionStateString(InfectionState infectionState) {
	std::string result = "";
	switch (infectionState) {
	case 0:
		result = "NOT_INFECTED_YET";
		break;
	case 1:
		result = "INFECTED";
		break;
	default:
		result = "infectionState??";
		break;
	}
	return result;
}

bool CHuman::InfectionCheck(TransmitResult result)
{
	// �������� �� ���޹޾����� ���� �����Ǵ��� ���δ� �� ���¿� ���� �ٸ���.
	// ���⼭ �װ��� ��Ʈ���Ѵ�. �ϴ� ������ 100%����.
	switch (result)
	{
	case TRANSMIT_SUCCESS:
		m_PreviousInfectionState = m_InfectionState;
		m_InfectionState = INFECTED;
		
		if (m_PreviousInfectionState == NOT_INFECTED_YET)
			return true;
		else if (m_PreviousInfectionState == INFECTED)
			return false;
		
		break;
	case TRANSMIT_FAIL:
		break;
	default:
		break;
	}
}