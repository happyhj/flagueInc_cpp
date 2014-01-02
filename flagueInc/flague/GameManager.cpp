#include "stdafx.h"
#include "GameManager.h"

#define RESITANCE_UPGRADE_COST 15
#define TRANSFER_PERIOD 7
#define POPULATION 652

CGameManager::CGameManager()
{

}


CGameManager::~CGameManager()
{

}


void CGameManager::Init() // 초기화
{
	//printf("\n\n Game을 시작합니다.\n\n");
	// 멤버변수를 초기화합니다.
	m_GameInfo.state = INITIALISING;

	time_t timer;
	struct tm t;

	timer = time(NULL); // 현재 시각을 초 단위로 얻기
	localtime_s(&t, &timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	// 현재날짜로 둘 다 초기화
	Date StartDate;
	StartDate.year = t.tm_year + 1900;
	StartDate.month = t.tm_mon + 1;
	StartDate.date = t.tm_mday;

	m_GameInfo.StartDate = StartDate;
	m_GameInfo.CurrentDate = StartDate;

	// 여기서 인트로멘트로 떡밥을 날린 후에
	m_GameInfo.state = INTRO_SEQUENCE;
	// DNA POINT, DayPassed 를 0으로 초기화
	m_GameInfo.DNAPoint = 0;
	m_GameInfo.DayPassed = 0;

	m_ViewDrawer = new CViewDrawer(&m_GameInfo);
	m_ViewDrawer->DrawIntroSequence();
	// 질병의 이름을 입력받는다.
	std::string diseaseName;
	std::cin >> diseaseName;

	m_Disease = new CDisease(diseaseName);

	m_ViewDrawer = new CViewDrawer(&m_GameInfo, m_Disease);


	// m_GameInfo.state = INITIALISING;
	// 게임을 할 국가의 특성을 선택한다.
	m_ViewDrawer->DrawSelectCountrySequence(diseaseName);
	int countryIndex;
	bool condition = true;
	while (condition)
	{
		printf("\n국가 선택 > ");
		std::cin >> countryIndex;
		if (!((countryIndex == std::atoi("1")) || (countryIndex == std::atoi("2")) || (countryIndex == std::atoi("3"))))
			printf("\n1,2,3번만 선택가능하다구요.\n");
		else
			break;
	}

	m_Country = createCountryByIndex(countryIndex);
	m_Disease = new CDisease(diseaseName, m_Country);

	m_ViewDrawer = new CViewDrawer(&m_GameInfo, m_Disease, m_Country);

	m_ViewDrawer->Draw();
//	printGameInfo();
//	m_Country->printInfo();
}

void CGameManager::Run() // 실행
{
	m_GameInfo.state = PROGRESSING;


	bool condition = true;
	while (condition)
	{
		// todo : 1번의 감염주기를 시행
		for (int i = 0; i < TRANSFER_PERIOD; i++)
		{
			// 날짜 1 증가. = m_dayPassed 도 증가.
			m_GameInfo.DayPassed++;
			updateCurrentDate(m_GameInfo.DayPassed);
			if (m_GameInfo.DayPassed == 1) {
				// 100%확률로 1명의 첫 감염자를 발생시킨다.
				m_Disease->makeFirstInfactee();
			}
			else {
				// 전염을 시도한다.
			m_Disease->attemptTransfer();
			}
			// system("cls");
			m_GameInfo.DNAPoint++;
			m_ViewDrawer->Draw();
			Sleep(100);
			//printf("%4d일 차 - ", m_dayPassed);
		}
		/*
		// 건강한 사람의 수를 체크하고 하나도 없으면 게임 종료
		int numOfHealthy = GetNumberOfPersonInCertainState(HEALTHY);
		if (numOfHealthy == 0) {
			printf("\n***축하합니다! 모든 인류를 감염시키셨습니다.***\n");
			break;
		}
		//		CheckMap();
		*/
		//printGameInfo();

		// 만약에 걸린사람이 POPULATION과 같으면 게임종료...
		int numOfInfected = m_Country->getNumberOfPersonInCertainState(INFECTED);
		if (numOfInfected == POPULATION)
		{
			m_ViewDrawer->DrawGameover();
			condition = false;
		}
		else {
			condition = InputProc(); //  TRUE  면 다음주기진행. FALSE 면 게임 종료
		}

	}

}

void CGameManager::Release() // 종료처리
{

}

void CGameManager::printGameInfo() {
	std::string logString = "";
	std::string gameState = "";
	logString = logString + "STARTDATE : " + std::to_string(this->m_GameInfo.StartDate.year);
	logString = logString + "/" + std::to_string(this->m_GameInfo.StartDate.month);
	logString = logString + "/" + std::to_string(this->m_GameInfo.StartDate.date) + "\n";
	logString = logString + "CURRENTDATE : " + std::to_string(this->m_GameInfo.CurrentDate.year);
	logString = logString + "/" + std::to_string(this->m_GameInfo.CurrentDate.month);
	logString = logString + "/" + std::to_string(this->m_GameInfo.CurrentDate.date) + "\n";


	logString = logString + "GameState : " + getGameStateString(this->m_GameInfo.state) + "\n\n";
	std::cout << "Country Info" << std::endl;
	m_Country->printInfo();
	std::cout << logString << std::endl;
	//this->m_Country = "";
}


std::string CGameManager::getGameStateString(GameState state) {
	std::string gameState = "";
	switch (state) {
	case 0:
		gameState = "INITIALISING";
		break;
	case 1:
		gameState = "PROGRESSING";
		break;
	case 2:
		gameState = "PROGRESSING_PAUSED";
		break;
	default:
		gameState = "gameState??";
		break;
	}
	return gameState;
}

CCountry* CGameManager::createCountryByIndex(int countryIndex)
{
	std::string countryName = "아무나라";
	Climate climate = TEMPERATE;
	CountryLevel countryLevel = UNDEVELOPED;
	PopulationDensity populationDensity = LOW_DENSITY;

	switch (countryIndex) 
	{
		case 1: // 인도
			countryName = "인도";
			climate = TROPICAL;
			countryLevel = UNDEVELOPED;
			populationDensity = HIGH_DENSITY;
			break;
		case 2: // 한국
			countryName = "한국";
			climate = TEMPERATE;
			countryLevel = DEVELOPING;
			populationDensity = MEDIUM_DENSITY;
			break;
		case 3: // 노르웨이
			countryName = "노르웨이";
			climate = POLAR;
			countryLevel = DEVELOPED;
			populationDensity = LOW_DENSITY;
			break;
		default:
			break;
	}
	CCountry* country = new CCountry(countryName, climate, countryLevel, populationDensity);

	country->printInfo();
	return country;
}

void CGameManager::updateCurrentDate(int m_dayPassed)
{
	m_GameInfo.CurrentDate.date = (m_dayPassed % 30) + 1;
	m_GameInfo.CurrentDate.month = ((m_dayPassed / 30 ) % 12) + 1;
	m_GameInfo.CurrentDate.year = m_GameInfo.StartDate.year + (m_dayPassed / 360);
}

bool CGameManager::InputProc()
{
	bool condition = true;
	while (condition)
	{
		printf_s("\nDNA 포인트를 사용하여 병을 진화시키세요.\n(지금은 할게 없으니 Y 로 다음 일주일을 진행 하세요)\n");
		printf_s("정비> ");

		// 스트링으로 제대로 입력 받기
		std::string strInput;
		std::cin >> strInput;
//		std::getline(std::cin, strInput);

		if (strInput == "Y" || strInput == "y")
		{
			printf_s("\n다음 감염주기를 진행합니다.\n");
			return true;
		}
		else if (strInput == "UF" || strInput == "uf")
		{
			// 잔액을 확인후 충분하다면 업글시키고 잔액차감
			int frIndex = m_Disease->getFrozenResistance();
			if (frIndex < 4) {
				if (m_GameInfo.DNAPoint > RESITANCE_UPGRADE_COST)
				{
					m_GameInfo.DNAPoint = m_GameInfo.DNAPoint - RESITANCE_UPGRADE_COST;
					m_Disease->upgradeFrozenResistance();
					printf_s("\n냉기저항이 상승하였습니다.\n");
				}
				else {
					printf_s("\nDNA POINT가 부족합니다.\n");
				}
			}
			else { // 이미 풀 업그레이드됨
				printf_s("\n이미 최고로 업그레이드가 되어있습니다.\n");
			}
			continue;
		}
		else if (strInput == "UH" || strInput == "uh")
		{
			// 잔액을 확인후 충분하다면 업글시키고 잔액차감
			int hrIndex = m_Disease->getHeatResistance();
			if (hrIndex < 4) {
				if (m_GameInfo.DNAPoint > RESITANCE_UPGRADE_COST)
				{
					m_GameInfo.DNAPoint = m_GameInfo.DNAPoint - RESITANCE_UPGRADE_COST;
					m_Disease->upgradeHeatResistance();
					printf_s("\n열기저항이 상승하였습니다.\n");
				}
				else {
					printf_s("\nDNA POINT가 부족합니다.\n");
				}
			}
			else { // 이미 풀 업그레이드됨
				printf_s("\n이미 최고로 업그레이드가 되어있습니다.\n");
			}
			continue;
		}
		else if (strInput == "Q" || strInput == "q")
		{
			return false;
		}
	}
	return true;
}