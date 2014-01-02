#pragma once

enum Cleanliness  // ������. �鿪�°� ���ϰ��ִ� �������� ����Ȱ������ �����Ѵ�. 
// �����õ����� �� �ɸ� Ȯ���� ���. 
// �׸��� ���� �õ� �ÿ��� ����Ȯ���� �����ش�.
{
	LOW_CLEANLINESS,
	MEDIUM_CLEANLINESS,
	HIGH_CLEANLINESS
};
enum Sociability  // �米��. ����� ���� ������ ����. �������� ���� ����鿡�� ������ �õ��Ѵ�.
{
	LOW_SOCIABILITY,
	MEDIUM_SOCIABILITY,
	HIGH_SOCIABILITY
};

enum InfectionState
{
	NOT_INFECTED_YET,
	INFECTED
};

enum TransmitResult
{
	TRANSMIT_FAIL,
	TRANSMIT_SUCCESS
};


class CHuman
{
public:
	CHuman(std::string	name, Cleanliness cleanliness, Sociability sociability);
	~CHuman();
	void printInfo();
	InfectionState getInfectionStatus(){ return m_InfectionState; };
	bool CHuman::InfectionCheck(TransmitResult result);
	std::string getHumanInfoString();

protected:
	std::string	m_Name;
	Cleanliness m_Cleanliness;
	Sociability m_Sociability;
	InfectionState m_InfectionState;
	InfectionState m_PreviousInfectionState;

	bool m_Immuned;

	// �α׿� �޼ҵ�
	std::string getCleanlinessString(Cleanliness cleanliness);
	std::string getSociabilityString(Sociability sociability);
	std::string getInfectionStateString(InfectionState infectionState);
};