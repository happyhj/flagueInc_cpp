#pragma once
class CHuman;
class CCountry;

// ���ĳ��������� �Ӽ�
// ������ ���Ŀ� ���� �����õ� �� �������� �ٲ��.
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

// ���󿡴��� �Ӽ�
// ��ħ : �α��е��� ���� ��쿡 �� �����õ� ��� ���� �����ش�.
enum Cough   {
	EXTRA_WEAK_COUGH,
	WEAK_COUGH,
	MEDIUM_COUGH,
	STRONG_COUGH,
	EXTRA_STRONG_COUGH
};
// ����� : ������� �����������ؼ� �������� �����.
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
	int attemptTransfer(); // ���ο� ������ ���� ��ȯ
	void makeFirstInfactee(); // ù �����ڸ� �߻���Ų��.
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

// �α׿� �Լ�

	std::string getDiseaseInfoString();
	std::string getFrozenResistanceString(FrozenResistance frozenResistance);
	std::string getHeatResistanceString(HeatResistance heatResistance);
	std::string getCoughString(Cough cough);
	std::string getLazinessString(Laziness laziness);
	int getTransmitResult();
};

