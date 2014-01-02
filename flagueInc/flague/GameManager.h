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

// 내 게임의 상태
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

	void Init();		// 초기화
	void Run();			// 실행
	void Release();		// 종료처리

protected:
	GameInfo m_GameInfo;

	// viewController 가 해야할 일 
	bool InputProc();	// 키보드 입력 처리

	//// Model Manipulation 
	//	void CreateMobs();	// 몹을 배치한다
	//	void CheckMap();
	//  BattleResult StartBattle(CMob* pMob);
	//int GetNumberOfPersonInCertainState(HumanState state);
	// void AttemptTranfer();

	//	CGameMap	m_Map;
	//	CPC*		m_PC;		// 플레이어 캐릭터

	CCountry* m_Country;
	CDisease* m_Disease;


	void updateCurrentDate(int dayPassed);
	// log 용 함수들.
	void printGameInfo();
	CViewDrawer* m_ViewDrawer;

	std::string getGameStateString(GameState state);
	CCountry* createCountryByIndex(int countryIndex);

};

