#include "stdafx.h"
#include "Human.h"



CHuman::CHuman(std::string	name, Cleanliness cleanliness, Sociability sociability)
{
	m_Name = name;
	// 사람의 능력치는 본인이 결정하는것이 아니라 소속한 나라가 자신의 속성을 통해 확률적으로 결정한다.
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
	// 병원균을 잘 전달받았지만 내가 감염되는지 여부는 내 상태에 따라 다르다.
	// 여기서 그것을 컴트롤한다. 일단 지금은 100%감염.
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