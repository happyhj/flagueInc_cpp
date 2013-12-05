#pragma once

#include "Country.h"

#define MAX_COUNTRY_NUMBER 1

// ������ ����
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


// ������ ��� ����Ѵ�
class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	void Init();		// �ʱ�ȭ
	void Run();			// ����
	void Release();		// ����ó��

protected:
	bool InputProc();	// Ű���� �Է� ó��
//	void CreateMobs();	// ���� ��ġ�Ѵ�
//	void CheckMap();
//  BattleResult StartBattle(CMob* pMob);
	int GetNumberOfPersonInCertainState(HumanState state);
	void AttemptTranfer();

protected:
//	CGameMap	m_Map;
//	CPC*		m_PC;		// �÷��̾� ĳ����
	GameState	m_GameState;
	CCountry* m_Countries[MAX_COUNTRY_NUMBER];
	int m_dayPassed;
};

