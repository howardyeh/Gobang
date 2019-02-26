#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include "calc.h"
#include <iomanip>


using namespace std;

#define computer_depth 4 // how deep the min max search should go
#define comlive5 200000
#define live5 100000
#define comlive4 50000
#define live4 20000
#define comdead4 10000 
#define comlive3 500
#define live3 300
#define comlive2 100
#define live2 80
#define dead4 50
#define comdead3 30
#define dead3 20
#define dead2 10



void measureScore(int count, short headis2orNot, short tailis2orNot, int *score, int whichSide)
{
	
	if (count >= 5)
	{
		//printf("detect 5\n");
		if (!whichSide){ *score += (comlive5/5.0); }
		else{ *score += (live5/5.0); }
	}
	if (count == 4)
	{
		if (headis2orNot == 0)
		{
			if (tailis2orNot == 0)
			{
				// printf("detect live 4\n");
				if (!whichSide)
				{ 
					*score += (comlive4/4.0);
				}
				else
				{
					*score += (live4/4.0);
				}
			}
			else
			{
				//printf("detect dead 4\n");
				if (!whichSide)
				{
					*score += (comdead4/4.0);
				}
				else
				{
					*score += (dead4/4.0);
				}
			}
		}
		else
		{
			if (tailis2orNot == 0)
			{
				//printf("detect dead 4\n");
				if (!whichSide)
				{
					*score += (comdead4/4.0);
				}
				else
				{
					*score += (dead4/4.0);
				}
			}
			else
			{
				//printf("Not important\n");
			}
		}
	}
	if (count == 3)
	{
		if (headis2orNot == 0)
		{
			if (tailis2orNot == 0)
			{
				//printf("detect live 3\n");
				if (!whichSide)
				{
					*score += (comlive3/3.0);
				}
				else
				{
					*score += (live3/3.0);
				}
			}

			else
			{
				//printf("detect dead 3\n");
				if (!whichSide)
				{
					*score += (comdead3/3.0);
				}
				else
				{
					*score += (dead3/3.0);
				}
			}
		}
		else
		{
			if (tailis2orNot == 0)
			{
				//printf("detect dead 3\n");
				if (!whichSide)
				{
					*score += (comdead3/3.0);
				}
				else
				{
					*score += (dead3/3.0);
				}
			}
			else
			{
				//printf("Not important\n");
			}
		}
	}
	if (count == 2)
	{
		if (headis2orNot == 0)
		{
			if (tailis2orNot == 0)
			{
				//printf("detect live 2\n");
				if (!whichSide)
				{
					*score += (comlive2/2.0);
				}
				else
				{
					*score += (live2/2.0);
				}
			}

			else
			{
				//printf("detect dead 2\n");
				*score += (dead2/2.0);
			}
		}
		else
		{
			if (tailis2orNot == 0)
			{
				//printf("detect dead 2\n");
				*score += (dead2/2.0);
			}
			else
			{
				//printf("Not important\n");
			}
		}
	}
}

int inLine(int x, int y, int whichSide, node *fake) 
{
	int positionX, positionY, count, score;
	short headis2orNot = 0;
	short tailis2orNot = 0;
	
	score = 0;

	// count up down
	positionX = x; positionY = y; count = 0;
	while (1)
	{
		positionX--;
		if (fake->Board[positionX][positionY] != whichSide || positionX < 0)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				headis2orNot = 1; // one side is block by other team
				break;
			}
			else if (positionX < 0)
			{
				headis2orNot = 2; // one side is block by wall
				break;
			}
			headis2orNot = 0; // one side is empty
			break;
		}
	}
	while (1)
	{
		positionX++;
		if (fake->Board[positionX][positionY] != whichSide || positionX > 14)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				tailis2orNot = 1;
				break;
			}
			else if (positionX > 14)
			{
				tailis2orNot = 2;
				break;
			}
			tailis2orNot = 0;
			break;
		}
		count++;
		
		
	}
	measureScore(count,headis2orNot,tailis2orNot,&score,whichSide);
	
	// count left right
	positionX = x; positionY = y; count = 0; headis2orNot = 0; tailis2orNot = 0;
	while (1)
	{
		positionY--;
		if (fake->Board[positionX][positionY] != whichSide || positionY < 0)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				headis2orNot = 1;
				break;
			}
			else if (positionY < 0)
			{
				headis2orNot = 2;
				break;
			}
			headis2orNot = 0;
			break;
		}
	}
	while (1)
	{
		positionY++;
		if (fake->Board[positionX][positionY] != whichSide || positionY > 14)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				tailis2orNot = 1;
				break;
			}
			else if (positionY > 14)
			{
				tailis2orNot = 2;
				break;
			}
			tailis2orNot = 0;
			break;
		}
		count++;
		

	}
	measureScore(count, headis2orNot, tailis2orNot, &score, whichSide);
	
	// count left tilt
	positionX = x; positionY = y; count = 0; headis2orNot = 0; tailis2orNot = 0;
	while (1)
	{
		positionX--; positionY--;
		if (fake->Board[positionX][positionY] != whichSide || positionY < 0 || positionX < 0)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				headis2orNot = 1;
				break;
			}
			else if (positionY < 0|| positionX < 0)
			{
				headis2orNot = 2;
				break;
			}
			headis2orNot = 0;
			break;
		}
	}
	while (1)
	{
		positionX++; positionY++;
		if (fake->Board[positionX][positionY] != whichSide || positionY > 14 || positionX >14)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				tailis2orNot = 1;
				break;
			}
			else if (positionY > 14 || positionX >14)
			{
				tailis2orNot = 2;
				break;
			}
			tailis2orNot = 0;
			break;
		}
		count++;
		

	}
	measureScore(count, headis2orNot, tailis2orNot, &score, whichSide);
	
	// count right tilt
	positionX = x; positionY = y; count = 0; headis2orNot = 0; tailis2orNot = 0;
	while (1)
	{
		positionX--; positionY++;
		if (fake->Board[positionX][positionY] != whichSide || positionY >14 || positionX < 0)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				headis2orNot = 1;
				break;
			}
			else if (positionY >14 || positionX < 0)
			{
				headis2orNot = 2;
				break;
			}
			headis2orNot = 0;
			break;
		}
	}
	while (1)
	{
		positionX++; positionY--;
		if (fake->Board[positionX][positionY] != whichSide || positionY <0 || positionX >14)
		{
			if (fake->Board[positionX][positionY] == -whichSide)
			{
				tailis2orNot = 1;
				break;
			}
			else if (positionY <0 || positionX >14)
			{
				tailis2orNot = 2;
				break;
			}
			tailis2orNot = 0;
			break;
		}
		count++;
		

	}
	measureScore(count, headis2orNot, tailis2orNot, &score, whichSide);
	return score;
}

point calculateScore(node fake1, int depth, int whichSide, point this_depth_point, bool alpha_beta)
{
	// whichSide>0 user
	// whichSide<0 Comp


	// first decide the consider range on the board (ie. we don't need to see through all the board.)
	int beginI = 14;
	int beginJ = 14;
	int endI = 0;
	int endJ = 0;
	bool have_started_or_not = false;

	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(fake1.Board[i][j] != 0){
				// cout<<"found a point at "<<i+1<<" , "<<j+1<<endl;
				if(!have_started_or_not) have_started_or_not = true;
				if(i<beginI) beginI = i;
				if(i>endI) endI = i;
				if(j<beginJ) beginJ = j;
				if(j>endJ) endJ = j;
			}
		}
	}
	if(!have_started_or_not){
		beginI = 0;
		beginJ = 0;
		endI = 14;
		endJ = 14;
	}
	else{
		if (beginI != 0){ beginI -= 1; }
		if (beginJ != 0){ beginJ -= 1; }
		if (endI != 14){ endI += 1; }
		if (endJ != 14){ endJ += 1; }
	}
	// cout<<"we only consider board ("<<beginI<<","<<beginJ<<") to ("<<endI<<","<<endJ<<")"<<endl;
	

	// start to play a move
	int countScore = 0;
	point next_depth_point;

	for(int i=beginI; i<endI+1; i++){
		for(int j=beginJ; j<endJ+1; j++){
			if (fake1.Board[i][j] == 0)
			{
				// ===========================================================================================
				// cout<<"position "<<i<<" "<<j<<" is empty"<<endl;

				// user step --> user want to minimize the score
				if (whichSide > 0)
				{
					fake1.Board[i][j] = whichSide;

					// end depth
					if(depth == computer_depth)
					{
						for(int p = beginI; p<endI+1; p++)
						{
							for(int q = beginJ; q<endJ+1; q++)
							{
								if(fake1.Board[p][q] == 1)
								{
									countScore-=inLine(p,q,1,&fake1);
								}
								else if(fake1.Board[p][q] == -1)
								{
									countScore+=inLine(p,q,-1,&fake1);
								}
							}
						}
						// cout << "countScore = " << countScore << "\n";
						
						if (this_depth_point.Min > countScore)
						{
							this_depth_point.Min = countScore;
							this_depth_point.x = i;
							this_depth_point.y = j;
						}

						if (this_depth_point.Max > this_depth_point.Min)
						{
							// cout<<"cut"<<endl;
							return this_depth_point;
						}
						countScore = 0;
					}

					// usual depth
					else
					{
						if(OverorNot(fake1, 1, i+1, j+1))
						{
							// cout<<"detect possible die in depth "<<depth<<endl;
							this_depth_point.Min = -live5;
							return this_depth_point;
						}
						next_depth_point = calculateScore(fake1, depth+1, -1*whichSide, this_depth_point, alpha_beta);
						if (this_depth_point.Min > next_depth_point.Max)
						{ 
							this_depth_point.Min = next_depth_point.Max;
							this_depth_point.x = i;
							this_depth_point.y = j;	
						}

						if (this_depth_point.Max >= this_depth_point.Min)
						{
							// cout<<"cut"<<endl;
							return this_depth_point;
						}
					}
					fake1.Board[i][j] = 0;
				}

				// computer step
				else if (whichSide < 0)
				{
					fake1.Board[i][j] = whichSide;

					// end depth
					if(depth == computer_depth)
					{
						for(int p = beginI; p<endI+1; p++)
						{
							for(int q = beginJ; q<endJ+1; q++)
							{
								if(fake1.Board[p][q] == 1)
								{
									countScore-=inLine(p,q,1,&fake1);
								}
								else if(fake1.Board[p][q] == -1)
								{
									countScore+=inLine(p,q,-1,&fake1);
								}
							}
						}
						if (this_depth_point.Max < countScore)
						{
							this_depth_point.Max = countScore;
							this_depth_point.x = i;
							this_depth_point.y = j;
						}
						if (this_depth_point.Max > this_depth_point.Min)
						{
							// cout<<"cut"<<endl;
							return this_depth_point;
						}
						countScore = 0;
					}

					// usual depth
					else
					{
						if(OverorNot(fake1, -1, i+1, j+1))
						{
							// cout<<"detect possible win in depth "<<depth<<endl;
							this_depth_point.Max = comlive5;
							this_depth_point.x = i;
							this_depth_point.y = j;
							return this_depth_point;
						}
						next_depth_point = calculateScore(fake1, depth+1, -1*whichSide, this_depth_point, alpha_beta);
						if (this_depth_point.Max < next_depth_point.Min)
						{
							this_depth_point.Max = next_depth_point.Min;
							this_depth_point.x = i;
							this_depth_point.y = j;
						}

						if (this_depth_point.Max >= this_depth_point.Min)
						{
							// cout<<"cut"<<endl;
							return this_depth_point;
						}
					}

					fake1.Board[i][j] = 0;
				}
				// ===========================================================================================
			}
		}
	}
	return this_depth_point;
}

bool OverorNot(node &temp, int whichSide, int x, int y)
{
	// whichSide > 0 --> user ;  whichSide < 0 --> computer
	int count;
	
	// Calculate up-down
	count = Count_line(temp, x, y, whichSide, 'v');
	if (count == 5)
	{
		return true;
	}
	
	// Calculate left-right
	count = Count_line(temp, x, y, whichSide, 'h');
	if (count == 5)
	{
		return true;
	}

	// Calculate laft tilt
	count = Count_line(temp, x, y, whichSide, 'l');
	if (count == 5)
	{
		return true;
	}

	// Calculate right tilt
	count = Count_line(temp, x, y, whichSide, 'r');
	if (count == 5)
	{
		return true;
	}

	return false;
}

bool CanPutOrNot(node &temp, int x, int y)
{
	if (x>=16 || y>=16 || x<1 || y<1) { cout<<"Wrong position! x, y can only be 1 - 15\n"; return 0; }
	if (temp.Board[x - 1][y - 1] != 0)
	{
		cout<<"you can't put here!\n"; return 0;
	}
	cout<<"input allowed!\n"; return 1;
}

int Count_line(node &temp, int x, int y, int whichSide, char dir)
{
	int positionX, positionY, positionXX, positionYY, count;
	bool flip1, flip2;
	switch(dir)
	{
		case 'v':
			positionX = x - 1; positionY = y - 1; positionXX = x; positionYY = y-1; count = 0; flip1 = false; flip2 = false;
			while(!flip1 || !flip2)
			{
				if (temp.Board[positionX][positionY] != whichSide || positionY < 0)
				{
					flip1 = true;
				}
				else
				{
					count++;
					positionX--;
				}
				if (temp.Board[positionXX][positionYY] != whichSide || positionY > 15)
				{
					flip2 = true;
				}
				else
				{
					count++;
					positionXX++;
				}
			}
			break;

		case 'h':
			positionX = x - 1; positionY = y - 1; positionXX = x-1; positionYY = y; count = 0; flip1 = false; flip2 = false;
			while(!flip1 || !flip2)
			{
				if (temp.Board[positionX][positionY] != whichSide || positionX < 0)
				{
					flip1 = true;
				}
				else
				{
					count++;
					positionY--;
				}
				if (temp.Board[positionXX][positionYY] != whichSide || positionX > 15)
				{
					flip2 = true;
				}
				else
				{
					count++;
					positionYY++;
				}
			}
			break;

		case 'l':
			positionX = x - 1; positionY = y - 1; positionXX = x; positionYY = y; count = 0; flip1 = false; flip2 = false;
			while(!flip1 || !flip2)
			{
				if (temp.Board[positionX][positionY] != whichSide || positionY < 0 || positionX < 0)
				{
					flip1 = true;
				}
				else
				{
					count++;
					positionX--;
					positionY--;
				}
				if (temp.Board[positionXX][positionYY] != whichSide || positionY > 15 || positionX>15)
				{
					flip2 = true;
				}
				else
				{
					count++;
					positionXX++;
					positionYY++;
				}
			}
			break;

		case 'r':
			positionX = x - 1; positionY = y - 1; positionXX = x-2; positionYY = y; count = 0; flip1 = false; flip2 = false;
			while(!flip1 || !flip2)
			{
				if (temp.Board[positionX][positionY] != whichSide || positionY < 0 || positionX>15)
				{
					flip1 = true;
				}
				else
				{
					count++;
					positionX++;
					positionY--;
				}
				if (temp.Board[positionXX][positionYY] != whichSide || positionY > 15 || positionX<0)
				{
					flip2 = true;
				}
				else
				{
					count++;
					positionXX--;
					positionYY++;
				}
			}
			break;
	}
	return count;
}

void showBoard(node &temp)
{
	printf("        1     2     3     4     5     6     7     8     9    10    11    12    13    14    15\n");
	for (int i = 0; i<15; i++)
	{
		for (int j = 0; j<16; j++)
		{
			if (j == 0){ printf("%5d", i + 1); }
			else if (temp.Board[i][j-1] == 0)
			{
				printf("     ");
			}
			else if (temp.Board[i][j-1] == 1)
			{
				printf("  ●  ");
			}
			else
			{
				printf("  ○  ");
			}
			if (j<16) printf("|");
		}
		printf("\n------------------------------------------------------------------------------------------------\n");
	}
}