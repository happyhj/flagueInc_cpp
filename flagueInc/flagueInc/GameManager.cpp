#include "stdafx.h"
#include "GameManager.h"

#define POWER_OFFSET 3


CGameManager::CGameManager(void)
:m_GameState(NORMAL)
{
	m_dayPassed = 0;
	// 일단 하나의 나라를 만들어서 초기화
	m_Countries[0] = new CCountry("대한민국");
}


CGameManager::~CGameManager(void)
{
//	delete m_PC;
}

void CGameManager::Init()
{
	printf("\n\n Game을 시작합니다.\n\n");

	srand((unsigned)time(NULL));
//	CreateMobs();

	// 위치 세팅
//	m_PC->SetPosition(5, 5);
//	m_PC->PrintPosition();

}

void CGameManager::Run()
{
	// INTRO

	Sleep(1000);
	printf("2030년 지구.\n");
	Sleep(1000);
	printf("너무 많아진 인간의 개체 수 때문에\n");
	Sleep(1000);
	printf("생태계 균형은 무너지고 있다.\n");
	Sleep(1000);
	printf("해결책은 단 하나.\n");
	Sleep(1000);
	printf("인류의 개체수를 조절하는 것.\n");
	Sleep(1000);
	Sleep(1000);
	

	// INIT
	// 스트링으로 제대로 입력 받기
	printf("\n누구에게 처음으로 질병을 주겠습니까?.(현재는 1번만 선택가능)\n");
	printf("1) 대한민국 대도시 서울에 사는 30대 회사원 최세훈.\n");
	printf("2) 도미니카공화국 아이티에 사는 20대 학생 메디나.\n");
	printf("3) 캐나다 대도시 보스턴에 사는 20대 요리사 토마스.\n");

	std::string strInput;
	while (true)
	{		
		printf("\n첫 감염자 선택 > ");
		std::getline(std::cin, strInput);
		if (strInput != "1")
			printf("\n1번만 선택가능하다구요.\n");
		else
			break;
	}
	printf("\n1번을 선택하셨습니다.\n", strInput.c_str());

	// todo  :대상 국가 -> 영역 -> 인간을 감염상태로 만드는 함수를 실행
	m_Countries[0]->MakeFirstInfactedPerson(0);



	while (InputProc())
	{
		// todo : 7번의 감염주기를 시행
		for (int i = 0; i < 7; i++){
			// 감염주기 //
			// 모든 국가의, 모든 영역의, 모든 사람 중 "감염된" 사람이 같은 구역 내의 
			// 무작위 사람 1명(추후바뀔 수있음) 에게 감염시도를 한다.
			m_dayPassed++;
			printf("%4d일 차 - ", m_dayPassed);
			Sleep(500);
			AttemptTranfer();
		}

		// 건강한 사람의 수를 체크하고 하나도 없으면 게임 종료
		int numOfHealthy = GetNumberOfPersonInCertainState(HEALTHY);
		if (numOfHealthy == 0) {
			printf("\n***축하합니다! 모든 인류를 감염시키셨습니다.***\n");
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
		printf_s("\nDNA 포인트를 사용하여 병을 진화시키세요.\n(지금은 할게 없으니 Y 로 다음 일주일을 진행 하세요)\n");
		printf_s("정비> ");

		// 스트링으로 제대로 입력 받기
		std::string strInput;
		std::getline(std::cin, strInput);

		if (strInput == "Y" || strInput == "y")
		{
			printf_s("\n다음 감염주기를 진행합니다.\n");
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
