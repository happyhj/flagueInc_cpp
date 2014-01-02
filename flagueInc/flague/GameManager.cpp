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


void CGameManager::Init() // �ʱ�ȭ
{
	//printf("\n\n Game�� �����մϴ�.\n\n");
	// ��������� �ʱ�ȭ�մϴ�.
	m_GameInfo.state = INITIALISING;

	time_t timer;
	struct tm t;

	timer = time(NULL); // ���� �ð��� �� ������ ���
	localtime_s(&t, &timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	// ���糯¥�� �� �� �ʱ�ȭ
	Date StartDate;
	StartDate.year = t.tm_year + 1900;
	StartDate.month = t.tm_mon + 1;
	StartDate.date = t.tm_mday;

	m_GameInfo.StartDate = StartDate;
	m_GameInfo.CurrentDate = StartDate;

	// ���⼭ ��Ʈ�θ�Ʈ�� ������ ���� �Ŀ�
	m_GameInfo.state = INTRO_SEQUENCE;
	// DNA POINT, DayPassed �� 0���� �ʱ�ȭ
	m_GameInfo.DNAPoint = 0;
	m_GameInfo.DayPassed = 0;

	m_ViewDrawer = new CViewDrawer(&m_GameInfo);
	m_ViewDrawer->DrawIntroSequence();
	// ������ �̸��� �Է¹޴´�.
	std::string diseaseName;
	std::cin >> diseaseName;

	m_Disease = new CDisease(diseaseName);

	m_ViewDrawer = new CViewDrawer(&m_GameInfo, m_Disease);


	// m_GameInfo.state = INITIALISING;
	// ������ �� ������ Ư���� �����Ѵ�.
	m_ViewDrawer->DrawSelectCountrySequence(diseaseName);
	int countryIndex;
	bool condition = true;
	while (condition)
	{
		printf("\n���� ���� > ");
		std::cin >> countryIndex;
		if (!((countryIndex == std::atoi("1")) || (countryIndex == std::atoi("2")) || (countryIndex == std::atoi("3"))))
			printf("\n1,2,3���� ���ð����ϴٱ���.\n");
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

void CGameManager::Run() // ����
{
	m_GameInfo.state = PROGRESSING;


	bool condition = true;
	while (condition)
	{
		// todo : 1���� �����ֱ⸦ ����
		for (int i = 0; i < TRANSFER_PERIOD; i++)
		{
			// ��¥ 1 ����. = m_dayPassed �� ����.
			m_GameInfo.DayPassed++;
			updateCurrentDate(m_GameInfo.DayPassed);
			if (m_GameInfo.DayPassed == 1) {
				// 100%Ȯ���� 1���� ù �����ڸ� �߻���Ų��.
				m_Disease->makeFirstInfactee();
			}
			else {
				// ������ �õ��Ѵ�.
			m_Disease->attemptTransfer();
			}
			// system("cls");
			m_GameInfo.DNAPoint++;
			m_ViewDrawer->Draw();
			Sleep(100);
			//printf("%4d�� �� - ", m_dayPassed);
		}
		/*
		// �ǰ��� ����� ���� üũ�ϰ� �ϳ��� ������ ���� ����
		int numOfHealthy = GetNumberOfPersonInCertainState(HEALTHY);
		if (numOfHealthy == 0) {
			printf("\n***�����մϴ�! ��� �η��� ������Ű�̽��ϴ�.***\n");
			break;
		}
		//		CheckMap();
		*/
		//printGameInfo();

		// ���࿡ �ɸ������ POPULATION�� ������ ��������...
		int numOfInfected = m_Country->getNumberOfPersonInCertainState(INFECTED);
		if (numOfInfected == POPULATION)
		{
			m_ViewDrawer->DrawGameover();
			condition = false;
		}
		else {
			condition = InputProc(); //  TRUE  �� �����ֱ�����. FALSE �� ���� ����
		}

	}

}

void CGameManager::Release() // ����ó��
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
	std::string countryName = "�ƹ�����";
	Climate climate = TEMPERATE;
	CountryLevel countryLevel = UNDEVELOPED;
	PopulationDensity populationDensity = LOW_DENSITY;

	switch (countryIndex) 
	{
		case 1: // �ε�
			countryName = "�ε�";
			climate = TROPICAL;
			countryLevel = UNDEVELOPED;
			populationDensity = HIGH_DENSITY;
			break;
		case 2: // �ѱ�
			countryName = "�ѱ�";
			climate = TEMPERATE;
			countryLevel = DEVELOPING;
			populationDensity = MEDIUM_DENSITY;
			break;
		case 3: // �븣����
			countryName = "�븣����";
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
		printf_s("\nDNA ����Ʈ�� ����Ͽ� ���� ��ȭ��Ű����.\n(������ �Ұ� ������ Y �� ���� �������� ���� �ϼ���)\n");
		printf_s("����> ");

		// ��Ʈ������ ����� �Է� �ޱ�
		std::string strInput;
		std::cin >> strInput;
//		std::getline(std::cin, strInput);

		if (strInput == "Y" || strInput == "y")
		{
			printf_s("\n���� �����ֱ⸦ �����մϴ�.\n");
			return true;
		}
		else if (strInput == "UF" || strInput == "uf")
		{
			// �ܾ��� Ȯ���� ����ϴٸ� ���۽�Ű�� �ܾ�����
			int frIndex = m_Disease->getFrozenResistance();
			if (frIndex < 4) {
				if (m_GameInfo.DNAPoint > RESITANCE_UPGRADE_COST)
				{
					m_GameInfo.DNAPoint = m_GameInfo.DNAPoint - RESITANCE_UPGRADE_COST;
					m_Disease->upgradeFrozenResistance();
					printf_s("\n�ñ������� ����Ͽ����ϴ�.\n");
				}
				else {
					printf_s("\nDNA POINT�� �����մϴ�.\n");
				}
			}
			else { // �̹� Ǯ ���׷��̵��
				printf_s("\n�̹� �ְ�� ���׷��̵尡 �Ǿ��ֽ��ϴ�.\n");
			}
			continue;
		}
		else if (strInput == "UH" || strInput == "uh")
		{
			// �ܾ��� Ȯ���� ����ϴٸ� ���۽�Ű�� �ܾ�����
			int hrIndex = m_Disease->getHeatResistance();
			if (hrIndex < 4) {
				if (m_GameInfo.DNAPoint > RESITANCE_UPGRADE_COST)
				{
					m_GameInfo.DNAPoint = m_GameInfo.DNAPoint - RESITANCE_UPGRADE_COST;
					m_Disease->upgradeHeatResistance();
					printf_s("\n���������� ����Ͽ����ϴ�.\n");
				}
				else {
					printf_s("\nDNA POINT�� �����մϴ�.\n");
				}
			}
			else { // �̹� Ǯ ���׷��̵��
				printf_s("\n�̹� �ְ�� ���׷��̵尡 �Ǿ��ֽ��ϴ�.\n");
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