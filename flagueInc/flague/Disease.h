#pragma once
class CHuman;
class CCountry;

// 기후내성에대한 속성
// 국가의 기후에 따라 전염시도 시 성공율이 바뀐다.
enum FrozenResistance {
	EXTRA_LOW_FROZEN_RESISTANCE,
	LOW_FROZEN_RESISTANCE,
	MEDIUM_FROZEN_RESISTANCE,
	HIGH_FROZEN_RESISTANCE,
	EXTRA_HIGH_FROZEN_RESISTANCE
};
enum HeatResistance {
	EXTRA_LOW_HEAT_RESISTANCE,
	LOW_HEAT_RESISTANCE,
	MEDIUM_HEAT_RESISTANCE,
	HIGH_HEAT_RESISTANCE,
	EXTRA_HIGH_HEAT_RESISTANCE
};

// 증상에대한 속성
// 기침 : 인구밀도가 높을 경우에 더 전염시도 대상 수를 높여준다.
enum Cough   {
	EXTRA_WEAK_COUGH,
	WEAK_COUGH,
	MEDIUM_COUGH,
	STRONG_COUGH,
	EXTRA_STRONG_COUGH
};
// 무기력 : 사람들이 게을러지게해서 위생도를 낮춘다.
enum Laziness {
	EXTRA_LOW_LAZINESS,
	LOW_LAZINESS,
	MEDIUM_LAZINESS,
	HIGH_LAZINESS,
	EXTRA_HIGH_LAZINESS
};

class CDisease
{
public:
	CDisease(std::string name);
	CDisease(std::string name, CCountry* country);
	~CDisease();
	void printInfo();
	int attemptTransfer(); // 새로운 감염자 수를 반환
	void makeFirstInfactee(); // 첫 감염자를 발생시킨다.
	void upgradeFrozenResistance(); // 
	void upgradeHeatResistance(); //
	int getFrozenResistance(){ return (int)m_FrozenResistance; };
	int getHeatResistance(){ return (int)m_HeatResistance; };
	std::string getName(){ return m_Name; };

protected:
	std::string	m_Name;
	FrozenResistance m_FrozenResistance;
	HeatResistance m_HeatResistance;
	Cough m_Cough;
	Laziness m_Laziness;
	CCountry* m_TargetCountry;

// 로그용 함수

	std::string getDiseaseInfoString();
	std::string getFrozenResistanceString(FrozenResistance frozenResistance);
	std::string getHeatResistanceString(HeatResistance heatResistance);
	std::string getCoughString(Cough cough);
	std::string getLazinessString(Laziness laziness);
	int getTransmitResult();
};

