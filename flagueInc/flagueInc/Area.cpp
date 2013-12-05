#include "stdafx.h"
#include "Area.h"


CArea::CArea(std::string name, int initialPopulation)
:m_name(name)
{
	// printf("����(%s)�� ����ϴ�. �ʱ��α� %d.\n", m_name.c_str(), initialPopulation);
	
	// �ϴ� �ִ� �α��� �� ä���� �ʱ�ȭ �ϴ°ɷ� �Ѵ�.
	printf("����(%s)�� ����ϴ�. �ʱ��α� %d.\n", m_name.c_str(), MAX_POPULATION);

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

	// �����ڰ� �����Ѵٸ�
	if (numOfInfectee > 0)
	{
		// ���� �����ڵ��� �ε����� �̷���� �迭�� �����Ѵ�.
		int* InfectedIndex = new int[numOfInfectee];
		int infectedCounter = 0;
		for (int i = 0; i < numOfHuman; i++){
			if (m_humans[i]->GetInfectionState() == INFECTED) {
				InfectedIndex[infectedCounter] = i;
				infectedCounter++;
			}
		}

		for (int i = 0; i < numOfInfectee ; i++){
			// �ϴ� 8% �����ϴ� �ɷ�..
			TransmitResult result = TRANSMIT_FAIL;
			if (rand()%13==0)
				result = TRANSMIT_SUCCESS;

			// �ڽ��� ������ �ƹ����׳� ����
			int targetIndex = rand() % (numOfHuman-1);
			if (targetIndex >= InfectedIndex[i])
			{
				targetIndex++;
			}

			// ���� ��Ų��..
			m_humans[targetIndex]->InfectionCheck(result);
		}
		delete[] InfectedIndex;
	}
	PrintPopulation();


	int numOfInfecteeAfterTransfer = GetNumberOfPersonInCertainState(INFECTED);

	int numOfNewInfectee = numOfInfecteeAfterTransfer - numOfInfectee;
	if (numOfNewInfectee > 0)
		printf_s(" �� ������ %2d��\n", numOfNewInfectee);
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
