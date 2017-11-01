#pragma once

class level {
public:
	level() {
		dropRange = dropdown;
		playerPos = dropdown*35/60;
	}

	void progress() {
		updateFrame();
		pRef->updatePos();
	}

	void updateFrame() {
		for (int i = 0; i < playerLength; ++i) {
			if (playerPosB[i] == pRef->pPos(i)) {
				playerPosB[i] = pRef->pPos(i);
			} else {
				consClear(playerPosB[i], (playerSpacing+playerLength-i), 1);
				playerPosB[i] = pRef->pPos(i);
				consPrint(pRef->pPos(i), (playerSpacing+playerLength-i), "X" );
			}

		}
	}

	void setPlayer(player* ref) {
		pRef = ref;
		playerLength = pRef->pLength();
		playerSpacing = playerPos - playerLength;
		playerPosB.assign(playerLength, -1);
	}

private:
	vector<int> playerPosB;
	int playerLength;
	int playerSpacing;
	int playerPos; 
	int dropRange;
	player* pRef;

	void consGoto(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void consClear(int x, int y, int length) {
		consGoto(x,y);
		cout << string(length, ' ');
	}

	void consPrint(int x, int y, string str) {
		consGoto(x,y);
		cout << str;
	}
};

