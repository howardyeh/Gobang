#include <iostream>
#include <cmath>
#include "calc.h"


using namespace std;

int main()
{
	int x, y, who;
	node temp, BoardScore;
	point ComputerPutAt;
	
	
	cout<<"please decide who go first?( 1 = you ; 0 = com )\n";
	cin >> who;
	showBoard(temp);
	if (who)
	{
		while (1)
		{
			cout<<"please enter your position!\n";
			cin >> x;
			cin >> y;
			if (CanPutOrNot(temp, x, y))
			{
				temp.Board[x - 1][y - 1] = 1;
				showBoard(temp);
				if(OverorNot(temp, 1, x, y)){
					cout<<"You win!!\n";
					exit(0);
				}
				else{
					cout<<"it's not over!\n";
				}
				ComputerPutAt.Max = -2147483647;
				ComputerPutAt.Min = 2147483647;
				ComputerPutAt = calculateScore(temp, 1, -1, ComputerPutAt, true);
				temp.Board[ComputerPutAt.x][ComputerPutAt.y] = -1;
				showBoard(temp);
				if(OverorNot(temp, -1, ComputerPutAt.x+1, ComputerPutAt.y+1)){
					cout<<"You loss!!\n";
					exit(0);
				}
				else{
					cout<<"it's not over!\n";
				}
				cout <<"computer put at ( "<<ComputerPutAt.x + 1 << " , " << ComputerPutAt.y + 1 << " )\n";
			}
		}
	}
	else
	{
		temp.Board[7][7] = -1;
		showBoard(temp);
		while(1)
		{
			cout<<"please enter your position!\n";
			cin>>x;
			cin>>y;
			if(CanPutOrNot(temp,x,y))
			{
				temp.Board[x-1][y-1] = 1;
				showBoard(temp);
				if(OverorNot(temp, 1, x, y)){
					cout<<"You win!!\n";
					exit(0);
				}
				else{
					cout<<"it's not over!\n";
				}
				ComputerPutAt.Max = -2147483647;
				ComputerPutAt.Min = 2147483647;
				ComputerPutAt = calculateScore(temp, 1, -1, ComputerPutAt);
				temp.Board[ComputerPutAt.x][ComputerPutAt.y] = -1;
				showBoard(temp);
				if(OverorNot(temp, -1, ComputerPutAt.x+1, ComputerPutAt.y+1)){
					cout<<"You loss!!\n";
					exit(0);
				}
				else{
					cout<<"it's not over!\n";
				}
				cout << "computer put at ( " << ComputerPutAt.x + 1 << " , " << ComputerPutAt.y + 1 << " )\n";
			}
		}
	}

	return 0;
}











