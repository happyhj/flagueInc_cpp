#include "stdafx.h"
#include "Human.h"


CHuman::CHuman()
{
	m_HumanState = HEALTHY;
	m_PreHumanState = HEALTHY;

	printf("+사람");
}


CHuman::~CHuman()
{
}

void CHuman::InfectionCheck(TransmitResult result)
{
	switch (result)
	{
	case TRANSMIT_SUCCESS:
		m_PreHumanState = m_HumanState;
		m_HumanState = INFECTED;
		/*
		if (m_PreHumanState == HEALTHY)
			printf_s(" 1명의 새로운 감염자가 발생했습니다.\n");
		else if (m_PreHumanState == INFECTED)
			printf_s(" 1명의 중복 감염자가 발생했습니다.\n");
			*/
		break;
	case TRANSMIT_FAIL:	
		break;
	default:
		break;
	}
}

HumanState CHuman::GetInfectionState()
{
	return m_HumanState;
}
HumanState CHuman::GetPreviousInfectionState()
{
	return m_HumanState;
}
