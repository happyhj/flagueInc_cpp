// SUD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CGameManager gameManeger;

	gameManeger.Init();
	gameManeger.Run();
	gameManeger.Release();

	std::string name;
	std::getline(std::cin, name);

	return 0;
}