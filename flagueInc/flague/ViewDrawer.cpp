#include "stdafx.h"
#include "ViewDrawer.h"
#include "GameManager.h"

CViewDrawer::CViewDrawer(GameInfo* gameInfo)
{

}
CViewDrawer::CViewDrawer(GameInfo* gameInfo, CDisease* disease)
{
	m_GameInfo = gameInfo;
	m_Disease = disease;
}
CViewDrawer::CViewDrawer(GameInfo* gameInfo, CDisease* disease ,CCountry* country )
//CViewDrawer::CViewDrawer()
{
	m_GameInfo = gameInfo;
	m_Country = country;
	m_Disease = disease;
}

CViewDrawer::~CViewDrawer()
{
}
// 감염인이 눈에 보이게 원을 구성하는 내부영역의 한 줄을 그린다.
int CViewDrawer::DrawPopulations(int numberOfSpace,int startHumanIndex)
{
	CHuman** m_humans = m_Country->getPopulation();
	CHuman* targetHuman = *(m_humans);
	InfectionState targetHumanInfectionState = targetHuman->getInfectionStatus();
	// 공백 17개 출력
	for (int i = 0; i < numberOfSpace; i++)
	{
		targetHuman = *(m_humans + startHumanIndex);
		targetHumanInfectionState = targetHuman->getInfectionStatus();
		if (targetHumanInfectionState == INFECTED)
		{
			std::cout << "*";
		}
		else
		{
			std::cout << " ";
		}
		startHumanIndex++;
	}
	return startHumanIndex;
}
void CViewDrawer::Draw()
{
	int humanIndex = 0;
	system("cls"); 
	std::cout << m_Country->getNumberOfPersonInCertainState(INFECTED);

	std::cout << "\n";
	std::cout << "                      *** ### ### ***" << "\n";
	std::cout.width(9);
	std::cout << m_Country->getName();
	std::cout << "         *##";humanIndex = DrawPopulations(17, humanIndex);std::cout <<"##*";std::cout.width(33);std::cout << this->getDateString() << "\n";
	std::cout << "              *##";humanIndex = DrawPopulations(25, humanIndex); std::cout<<"##*" << "\n";
	std::cout << "           *##"; humanIndex = DrawPopulations(32, humanIndex); std::cout << "##*"; std::cout.width(12); std::cout << this->m_GameInfo->DayPassed << "일 째" << "\n";
	std::cout << "         *##"; humanIndex = DrawPopulations(36, humanIndex); std::cout << "##*" << "\n";
	std::cout << "       *##"; humanIndex = DrawPopulations(40, humanIndex); std::cout << "##*" << "\n";
	std::cout << "     *##"; humanIndex = DrawPopulations(43, humanIndex); std::cout << "##*" << "\n";
	std::cout << "     *##"; humanIndex = DrawPopulations(43, humanIndex); std::cout << "##*" << "\n";
	std::cout << "    *##"; humanIndex = DrawPopulations(45, humanIndex); std::cout << "##*" << "\n";
	std::cout << "    *##"; humanIndex = DrawPopulations(45, humanIndex); std::cout << "##*" << "\n";
	std::cout << "    *##"; humanIndex = DrawPopulations(45, humanIndex); std::cout << "##*" << "\n"; // 45
	std::cout << "    *##"; humanIndex = DrawPopulations(45, humanIndex); std::cout << "##*" << "\n"; // 45
	std::cout << "     *##"; humanIndex = DrawPopulations(43, humanIndex); std::cout << "##*" << "\n"; // 43
	std::cout << "     *##"; humanIndex = DrawPopulations(43, humanIndex); std::cout << "##*" << "\n"; // 43
	std::cout << "       *##"; humanIndex = DrawPopulations(40, humanIndex); std::cout << "##*" << "\n"; // 40
	std::cout << "         *##"; humanIndex = DrawPopulations(36, humanIndex); std::cout << "##*"; std::cout.width(20); std::cout <<"DNA POINT:"<< m_GameInfo->DNAPoint << "\n";// 36
	std::cout << "           *##"; humanIndex = DrawPopulations(32, humanIndex); std::cout << "##*" << "\n"; // 32
	std::cout << "              *##"; humanIndex = DrawPopulations(25, humanIndex); std::cout << "##*" << "\n"; // 25
	std::cout << "                  *##"; humanIndex = DrawPopulations(17, humanIndex); std::cout << "##*" << "\n"; // 17 
	std::cout << "                      *** ### ### ***" << "\n";

	//m_Disease->printInfo();
	//m_Country->printInfo();
}
void CViewDrawer::DrawIntroSequence()
{
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년                                                         ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################";
	Sleep(100);
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년    당신은                                               ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################";
	Sleep(100);
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년    당신은     전세계를                                  ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################";
	Sleep(100);
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년    당신은     전세계를                                  ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                           무엇에                                           ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################";
	Sleep(100);
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년    당신은     전세계를                                  ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                           무엇에       감염시키고 싶습니까?                ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################" << std::endl;
	Sleep(100);
	std::cout << "                         질병의   이름을   지어주세요.                          " << std::endl;
	std::cout << "                                  ";

}
void CViewDrawer::DrawSelectCountrySequence(std::string diseaseName)
{
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "##            2014 년    당신은     전세계를                                  ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                           무엇에       감염시키고 싶습니까?                ##";
	std::cout << "##                                                                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################" << std::endl;
	Sleep(100);
	std::cout << "                 " << diseaseName;
	for (int i = 0;i<3; i++) {
		Sleep(100);
		std::cout << ".";
	}
	Sleep(100);
	std::cout << "    흥미로운    이름이군요?" << std::endl << std::endl;
	Sleep(100);
	std::cout << "                       이제   감염시킬   국가를  고르세요." << std::endl << std::endl;
	std::cout << "                      1.인도       2.한국      3.노르웨이                    " << std::endl << std::endl;
	std::cout << "                                    ";

}
std::string CViewDrawer::getDateString()
{
	Date date = m_GameInfo->CurrentDate;
	std::string dateString = "";
	dateString = std::to_string(date.year) + "년";
	dateString = dateString + " " + std::to_string(date.month) + "월 ";
	dateString = dateString + std::to_string(date.date) + "일";
	return dateString;
}

void CViewDrawer::DrawGameover()
{
	system("cls");
	std::cout << "################################################################################";
	std::cout << "##                                                                            ##";
	std::cout << "##                         축 하 합 니 다,                                    ##";
	std::cout << "          "<< m_Country->getName() << "의 모든 국인이 " << m_Disease->getName() <<"에 걸렸습니다.\n";
	std::cout << "##                                                                            ##";
	std::cout << "##                              즐 거 우 십 니 까?                            ##";
	std::cout << "##                                                                            ##";
	std::cout << "################################################################################" << std::endl;
}
