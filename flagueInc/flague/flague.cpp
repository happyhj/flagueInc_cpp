// flague.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	argc;
	argv;

	CGameManager gameManeger;

	gameManeger.Init();
	gameManeger.Run();
	gameManeger.Release();

	system("pause");

	return 0;
}
