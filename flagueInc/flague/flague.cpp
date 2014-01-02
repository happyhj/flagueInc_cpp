// flague.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
