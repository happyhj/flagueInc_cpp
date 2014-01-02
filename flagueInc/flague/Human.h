#pragma once

enum Cleanliness  // 더러움. 면역력과 지니고있는 병원균의 전염활성도를 결정한다. 
// 전염시도당할 시 걸릴 확률을 담당. 
// 그리고 전염 시도 시에는 성공확률을 높여준다.
{
	LOW_CLEANLINESS,
	MEDIUM_CLEANLINESS,
	HIGH_CLEANLINESS
};
enum Sociability  // 사교성. 사람을 많이 만나는 정도. 높을수록 많은 사람들에게 감염을 시도한다.
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

	// 로그용 메소드
	std::string getCleanlinessString(Cleanliness cleanliness);
	std::string getSociabilityString(Sociability sociability);
	std::string getInfectionStateString(InfectionState infectionState);
};