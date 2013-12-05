#include "stdafx.h"
#include "Area.h"


CArea::CArea(std::string name, int initialPopulation)
:m_name(name)
{
	// printf("지역(%s)을 만듭니다. 초기인구 %d.\n", m_name.c_str(), initialPopulation);
	
	// 일단 최대 인구를 다 채워서 초기화 하는걸로 한다.
	printf("지역(%s)을 만듭니다. 초기인구 %d.\n", m_name.c_str(), MAX_POPULATION);

	for (int i = 0; i < MAX_POPULATION; i++)
	{
		m_humans[i] = new CHuman();
	}

	m_humans[0]->GetInfectionState();
}


CArea::~CArea()
{
}

void CArea::MakeFirstInfactedPerson()
{
	m_humans[0]->InfectionCheck(TRANSMIT_SUCCESS);
}

void CArea::AttemptTransfer()
{
	int numOfInfectee = GetNumberOfPersonInCertainState(INFECTED);
	int numOfHuman = sizeof(m_humans) / sizeof(m_humans[0]);

	// 감염자가 존재한다면
	if (numOfInfectee > 0)
	{
		// 기존 감염자들의 인덱스로 이루어진 배열을 생성한다.
		int* InfectedIndex = new int[numOfInfectee];
		int infectedCounter = 0;
		for (int i = 0; i < numOfHuman; i++){
			if (m_humans[i]->GetInfectionState() == INFECTED) {
				InfectedIndex[infectedCounter] = i;
				infectedCounter++;
			}
		}

		for (int i = 0; i < numOfInfectee ; i++){
			// 일단 8% 성공하는 걸로..
			TransmitResult result = TRANSMIT_FAIL;
			if (rand()%13==0)
				result = TRANSMIT_SUCCESS;

			// 자신을 제외한 아무한테나 전염
			int targetIndex = rand() % (numOfHuman-1);
			if (targetIndex >= InfectedIndex[i])
			{
				targetIndex++;
			}

			// 전염 시킨다..
			m_humans[targetIndex]->InfectionCheck(result);
		}
		delete[] InfectedIndex;
	}
	PrintPopulation();


	int numOfInfecteeAfterTransfer = GetNumberOfPersonInCertainState(INFECTED);

	int numOfNewInfectee = numOfInfecteeAfterTransfer - numOfInfectee;
	if (numOfNewInfectee > 0)
		printf_s(" 새 감염자 %2d명\n", numOfNewInfectee);
	else 
		printf_s("\n");

}

int CArea::GetNumberOfPersonInCertainState(HumanState state) {
	int infectedCounter = 0;
	int numOfHuman = sizeof(m_humans) / sizeof(m_humans[0]);
	for (int i = 0; i < numOfHuman; i++){
		if (m_humans[i]->GetInfectionState() == state) {
			infectedCounter++;
		}
	}
	return infectedCounter;
}
int CArea::GetNumberOfPersonInCertainPreviousState(HumanState state) {
	int infectedCounter = 0;
	int numOfHuman = sizeof(m_humans) / sizeof(m_humans[0]);
	for (int i = 0; i < numOfHuman; i++){
		if (m_humans[i]->GetPreviousInfectionState() == state) {
			infectedCounter++;
		}
	}
	return infectedCounter;
}

void CArea::PrintPopulation()
{
	int numOfInfectee = GetNumberOfPersonInCertainState(INFECTED);
	int numOfHealthy = GetNumberOfPersonInCertainState(HEALTHY);
	int numOfDead = GetNumberOfPersonInCertainState(DEAD);
	for (int i = 0; i < numOfDead; i++)
	{
		printf_s("X");
		Sleep(20);

	}	
	for (int i = 0; i < numOfInfectee; i++)
	{
		printf_s("!");
		Sleep(20);
	}
		
	for (int i = 0; i < numOfHealthy; i++)
	{
		printf_s("O");
		Sleep(20);
	}	
}
