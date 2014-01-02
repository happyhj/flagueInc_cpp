#pragma once

class CGameManager;
struct GameInfo;

#include "Country.h"
#include "Disease.h"

class CViewDrawer
{
public:
//	CViewDrawer(GameInfo* gameInfo, CCountry** country, CDisease** disease);
	CViewDrawer(GameInfo* gameInfo);
	CViewDrawer(GameInfo* gameInfo, CDisease* disease);
	CViewDrawer(GameInfo* gameInfo, CDisease* disease, CCountry* country);
	~CViewDrawer();

	void Draw();
	void DrawIntroSequence();
	void DrawSelectCountrySequence(std::string diseaseName);
	void DrawGameover();

protected:
	GameInfo* m_GameInfo;
	CCountry* m_Country;
	CDisease* m_Disease;
	std::string getDateString();
	int DrawPopulations(int numberOfSpace, int startHumanIndex);
};

