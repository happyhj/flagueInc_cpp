#pragma once

#include "Country.h"

#define MAX_COUNTRY_NUMBER 1

// 게임의 상태
enum GameState
{
	NORMAL,
	BATTLE,
};

enum BattleResult
{
	BATTLE_WIN,
	BATTLE_LOSE,
	BATTLE_NONE,
};


// 게임의 제어를 담당한다
class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	void Init();		// 초기화
	void Run();			// 실행
	void Release();		// 종료처리

protected:
	bool InputProc();	// 키보드 입력 처리
//	void CreateMobs();	// 몹을 배치한다
//	void CheckMap();
//  BattleResult StartBattle(CMob* pMob);
	int GetNumberOfPersonInCertainState(HumanState state);
	void AttemptTranfer();

protected:
//	CGameMap	m_Map;
//	CPC*		m_PC;		// 플레이어 캐릭터
	GameState	m_GameState;
	CCountry* m_Countries[MAX_COUNTRY_NUMBER];
	int m_dayPassed;
};

