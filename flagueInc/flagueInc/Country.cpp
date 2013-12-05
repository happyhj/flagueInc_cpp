#include "stdafx.h"
#include "Country.h"

// #define ZERO_MEMORY(mem, size) memset(mem, 0, size)


CCountry::CCountry(std::string name)
:m_name(name)
{
	// 지역을(예. 서울) 하나만 만들어서 초기화 
	printf("나라(%s)을 만듭니다.\n", m_name.c_str());
	m_areas[0] = new CArea("서울",20);
	// ZERO_MEMORY(m_areas, sizeof(m_areas));
}


CCountry::~CCountry()
{
	// 포인터를 여러개 가질 경우는 어떻게 메모리를 반환하지?
	// 아래는 하나만 가질 경우 메모리를 풀어주는 방식이다.
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
