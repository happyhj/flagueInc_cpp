#include "stdafx.h"
#include "Country.h"

// #define ZERO_MEMORY(mem, size) memset(mem, 0, size)


CCountry::CCountry(std::string name)
:m_name(name)
{
	// ������(��. ����) �ϳ��� ���� �ʱ�ȭ 
	printf("����(%s)�� ����ϴ�.\n", m_name.c_str());
	m_areas[0] = new CArea("����",20);
	// ZERO_MEMORY(m_areas, sizeof(m_areas));
}


CCountry::~CCountry()
{
	// �����͸� ������ ���� ���� ��� �޸𸮸� ��ȯ����?
	// �Ʒ��� �ϳ��� ���� ��� �޸𸮸� Ǯ���ִ� ����̴�.
	/*
	for (int i = 0; i < MAX_CAPACITY; ++i) {
		delete m_areas[i].pMob;
		m_areas[i].pMob = nullptr;
	}
	*/
}
void CCountry::MakeFirstInfactedPerson(int areaIndex){
	m_areas[areaIndex]->MakeFirstInfactedPerson();
}

void CCountry::AttemptTransfer()
{
	int numOfAreas = sizeof(m_areas) / sizeof(m_areas[0]);
	for (int i = 0; i < numOfAreas; i++){
		m_areas[i]->AttemptTransfer();
	}
}
int CCountry::GetNumberOfPersonInCertainState(HumanState state) {
	int counter = 0;
	int numOfArea = sizeof(m_areas) / sizeof(m_areas[0]);
	for (int i = 0; i < numOfArea; i++){
		counter =+ m_areas[i]->GetNumberOfPersonInCertainState(state);
	}
	return counter;
}
