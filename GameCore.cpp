#define MAP_SIZE 4
#define MAX_TIMES 2000000000
#include<string.h>
#include<stdlib.h>
#include<iostream>


void Move(int(&MAP)[MAP_SIZE][MAP_SIZE], int direction, int position, int &score) {
	/*竖直移动合并*/
	//函数声明
	void DeleteZero(int(&MAP)[MAP_SIZE][MAP_SIZE], int position);
	void Transpose(int(&MAP)[MAP_SIZE][MAP_SIZE]);

	//如果是水平方向上的话, 先转置
	if (direction == 1) {
		Transpose(MAP);
	}

	//首先移动所有格子,让其靠在一起
	DeleteZero(MAP, position);

	for (int j = 0; j < MAP_SIZE; j++) {
		int start = abs(MAP_SIZE - 1 - position);
		int curPos = -start;
		//合并
		while (curPos-start < MAP_SIZE-1) {
			int cur = MAP[abs(curPos)][j];
			int next = abs(curPos + 1);
			if ((cur != 0) && (cur == MAP[next][j])) {
				MAP[next][j] = 0;
				MAP[abs(curPos)][j] *= 2;
				curPos += 2;
				score++;
			}
			else {
				curPos++;
			}
		}
	}

	//补充因合并产生的空位
	DeleteZero(MAP, position);

	//如果是水平方向上的话, 最后再转置一下
	if (direction == 1) {
		Transpose(MAP);
	}
}

void DeleteZero(int(&MAP)[MAP_SIZE][MAP_SIZE], int position) {
	/*移动地图(竖直移动)而进行的靠拢, 即删除0*/
	for (int j = 0; j < MAP_SIZE; j++) {
		for (int i = 0 - position; i < MAP_SIZE - 1 - position; i++) {
			if (MAP[abs(i)][j] == 0) {
				//找到从i往后第一个不为0的坐标，然后把其填到当前位置
				for (int zeroPos = i + 1; zeroPos < MAP_SIZE - position; zeroPos++) {
					if (MAP[abs(zeroPos)][j] != 0) {
						MAP[abs(i)][j] = MAP[abs(zeroPos)][j];
						MAP[abs(zeroPos)][j] = 0;
						break;
					}
				}
			}
		}
	}
}

void Transpose(int(&MAP)[MAP_SIZE][MAP_SIZE]) {
	/*对地图进行转置
	行的0转为列的0, 列的0转为行的0*/
	void SwapElement(int &A, int &B);

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < i; j++) {
			SwapElement(MAP[i][j], MAP[j][i]);
		}
	}
}

void SwapElement(int &A, int &B) {
	/*交换两个元素*/
	int temp = A;
	A = B;
	B = temp;
}

using namespace std;
class Gamemap
{
public:
    Gamemap();
    int map[MAP_SIZE][MAP_SIZE];
    void MoveMap(char command);
    bool SetBlock(int x,int y,int n);
    int score;
};

Gamemap::Gamemap(/* args */)
{
    memset(map,0,sizeof(map));
    score=0;
}

bool Gamemap::SetBlock(int x,int y,int n){
    if(map[x][y]==0){
        map[x][y]==n;
        return true;
    }
    return false;
}

void ShowMap(Gamemap input) {
	/*输出地图*/
	cout << "Now Your Game Map is: " << endl;
	cout << "---------------------------------" << endl;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (input.map[i][j] == 0) cout << "	" << "-";
			else cout << "	" << input.map[i][j];
		}
		cout << endl;
	}
	cout << "---------------------------------" << endl;
	cout << "Now Your Score is: " << input.score << endl;
	cout << "Plase Move Map(up:w down:s left:a right:d): ";
}

void Gamemap::MoveMap(char command) {
	/*根据指令移动地图*/
	switch (command) {
	case 'w':
		Move(map, 0, 0, score);
		break;
	case 's':
		Move(map, 0, MAP_SIZE - 1, score);
		break;
	case 'a':
		Move(map, 1, 0, score);
		break;
	default:
		Move(map, 1, MAP_SIZE - 1, score);
	}
}





