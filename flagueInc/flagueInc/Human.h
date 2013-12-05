#pragma once

enum HumanState
{
	HEALTHY,
	INFECTED,
	DEAD
};
enum TransmitResult
{
	TRANSMIT_SUCCESS,
	TRANSMIT_FAIL
};

class CHuman
{
public:
	CHuman();
	~CHuman();
	HumanState GetInfectionState();
	HumanState GetPreviousInfectionState();
	void InfectionCheck(TransmitResult result);

private:
	HumanState	m_HumanState;
	HumanState	m_PreHumanState;

	int m_sociability;
	int m_neatness;

};

