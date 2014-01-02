#pragma once
#include "Country.h"
#include "Disease.h"
#include "ViewDrawer.h"

enum GameState
{
	INITIALISING,
	INTRO_SEQUENCE,
	PROGRESSING,
	PROGRESSING_PAUSED,
};

struct Date {
	int year;
	int month;
	int date;
};

// �� ������ ����
struct GameInfo {
	GameState state;
	Date StartDate;
	Date CurrentDate;
	int DayPassed;
	int DNAPoint;
};

class CGameManager
{
public:
	//	static const char* PROGRESSING = "PROGRESSING";
	CGameManager();
	~CGameManager();

	void Init();		// �ʱ�ȭ
	void Run();			// ����
	void Release();		// ����ó��

protected:
	GameInfo m_GameInfo;

	// viewController �� �ؾ��� �� 
	bool InputProc();	// Ű���� �Է� ó��

	//// Model Manipulation 
	//	void CreateMobs();	// ���� ��ġ�Ѵ�
	//	void CheckMap();
	//  BattleResult StartBattle(CMob* pMob);
	//int GetNumberOfPersonInCertainState(HumanState state);
	// void AttemptTranfer();

	//	CGameMap	m_Map;
	//	CPC*		m_PC;		// �÷��̾� ĳ����

	CCountry* m_Country;
	CDisease* m_Disease;


	void updateCurrentDate(int dayPassed);
	// log �� �Լ���.
	void printGameInfo();
	CViewDrawer* m_ViewDrawer;

	std::string getGameStateString(GameState state);
	CCountry* createCountryByIndex(int countryIndex);

};

