#include "stdafx.h"
#include "GameManager.h"

#define POWER_OFFSET 3


CGameManager::CGameManager(void)
:m_GameState(NORMAL)
{
	m_dayPassed = 0;
	// �ϴ� �ϳ��� ���� ���� �ʱ�ȭ
	m_Countries[0] = new CCountry("���ѹα�");
}


CGameManager::~CGameManager(void)
{
//	delete m_PC;
}

void CGameManager::Init()
{
	printf("\n\n Game�� �����մϴ�.\n\n");

	srand((unsigned)time(NULL));
//	CreateMobs();

	// ��ġ ����
//	m_PC->SetPosition(5, 5);
//	m_PC->PrintPosition();

}

void CGameManager::Run()
{
	// INTRO

	Sleep(1000);
	printf("2030�� ����.\n");
	Sleep(1000);
	printf("�ʹ� ������ �ΰ��� ��ü �� ������\n");
	Sleep(1000);
	printf("���°� ������ �������� �ִ�.\n");
	Sleep(1000);
	printf("�ذ�å�� �� �ϳ�.\n");
	Sleep(1000);
	printf("�η��� ��ü���� �����ϴ� ��.\n");
	Sleep(1000);
	Sleep(1000);
	

	// INIT
	// ��Ʈ������ ����� �Է� �ޱ�
	printf("\n�������� ó������ ������ �ְڽ��ϱ�?.(����� 1���� ���ð���)\n");
	printf("1) ���ѹα� �뵵�� ���￡ ��� 30�� ȸ��� �ּ���.\n");
	printf("2) ���̴�ī��ȭ�� ����Ƽ�� ��� 20�� �л� �޵�.\n");
	printf("3) ĳ���� �뵵�� �����Ͽ� ��� 20�� �丮�� �丶��.\n");

	std::string strInput;
	while (true)
	{		
		printf("\nù ������ ���� > ");
		std::getline(std::cin, strInput);
		if (strInput != "1")
			printf("\n1���� ���ð����ϴٱ���.\n");
		else
			break;
	}
	printf("\n1���� �����ϼ̽��ϴ�.\n", strInput.c_str());

	// todo  :��� ���� -> ���� -> �ΰ��� �������·� ����� �Լ��� ����
	m_Countries[0]->MakeFirstInfactedPerson(0);



	while (InputProc())
	{
		// todo : 7���� �����ֱ⸦ ����
		for (int i = 0; i < 7; i++){
			// �����ֱ� //
			// ��� ������, ��� ������, ��� ��� �� "������" ����� ���� ���� ���� 
			// ������ ��� 1��(���Ĺٲ� ������) ���� �����õ��� �Ѵ�.
			m_dayPassed++;
			printf("%4d�� �� - ", m_dayPassed);
			Sleep(500);
			AttemptTranfer();
		}

		// �ǰ��� ����� ���� üũ�ϰ� �ϳ��� ������ ���� ����
		int numOfHealthy = GetNumberOfPersonInCertainState(HEALTHY);
		if (numOfHealthy == 0) {
			printf("\n***�����մϴ�! ��� �η��� ������Ű�̽��ϴ�.***\n");
			break;
		}
//		CheckMap();
	}
}

void CGameManager::Release()
{
	printf("[Game Over!!]\n");
}

bool CGameManager::InputProc()
{
	while (true)
	{
		printf_s("\nDNA ����Ʈ�� ����Ͽ� ���� ��ȭ��Ű����.\n(������ �Ұ� ������ Y �� ���� �������� ���� �ϼ���)\n");
		printf_s("����> ");

		// ��Ʈ������ ����� �Է� �ޱ�
		std::string strInput;
		std::getline(std::cin, strInput);

		if (strInput == "Y" || strInput == "y")
		{
			printf_s("\n���� �����ֱ⸦ �����մϴ�.\n");
			return true;
		}
		else if (strInput == "Q" || strInput == "q")
		{
			return false;
		}
	}
	return true;
}

void CGameManager::AttemptTranfer()
{
	int numOfCountries = sizeof(m_Countries) / sizeof(m_Countries[0]);
	for (int i = 0; i < numOfCountries; i++){
		m_Countries[i]->AttemptTransfer();
	}
}
int CGameManager::GetNumberOfPersonInCertainState(HumanState state) {
	int counter = 0;
	int numOfCountries = sizeof(m_Countries) / sizeof(m_Countries[0]);
	for (int i = 0; i < numOfCountries; i++){
		counter = +m_Countries[i]->GetNumberOfPersonInCertainState(state);
	}
	return counter;
}
