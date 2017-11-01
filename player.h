#pragma once

//MEMORY
int cKey;			//Last key pressed;

class player {
public:
	player(int L) {
		//Initialize Parameters
		phase1 = ph1L;
		phase2 = ph1L + ph2L;
		phase3 = ph1L + ph2L + 1;
		length = L;
		dir = 0;
		dirB = 0;
		deltaDir = 0;
		phase = 0;

		//Initialize Entity Position
		x = border/2;
		pos.assign(L,x);
	}

	void updatePos() {
		for (int i=length-1; i>0; i--)
			pos[i] = pos[i-1];
		x += calcMovement();
		pos[0] = x;
	}

	int pLength() {
		return length;
	}

	int pPos(int x) {
		return pos[x];
	}


	void showPos() {
		cout << "[";
		for (int i = 0; i < pos.size(); ++i)
		{
			cout << pos[i] << " ";
		}
		cout << "]" << endl;
	}

	void debug() {
		cout << "PH1 " << phase1 << endl;
		cout << "PH2 " << phase2 << endl;
		cout << "PH3 " << phase3 << endl;
		cout << "PHS " << phase << endl;
		cout << "DIR " << dir << endl;
		cout << "DRB " << dirB << endl;
		cout << "DDR " << deltaDir << endl;
		cout << "POS " << x << endl;
		showPos();
	}

private:
	vector <int> pos;			//CURRENT position of whole body
	int x;				//Head position (bottom part)
	int dir;			//Current movement direction
	int dirB;			//Last movement direction
	int deltaDir;		//Where to translate (left or right), to satisfy current movement
	int phase;			//Transition between moving left, down, right
	int velX;			//X velocity, the variable depended by X
	int phase1;
	int phase2;
	int phase3;
	int length;

	int calcMovement() {
		//Reset parameters
		velX = 0;

		//Check last movement
		dirB = dir;

		//Check key input
		dir = cKey;

		//Check if there any change in direction
		if (dir != dirB) {
			if (dir > dirB) {
				deltaDir = 1;
			} else if (dir < dirB) {
				deltaDir = -1;
			}
		}

		//*Changing direction
		if ((phase == phase3 || phase == -phase3) && deltaDir != 0) {
			phase += deltaDir;
		}

		//*Fixing direction
		else if (phase == 0 && dir == 0){
			deltaDir = 0;
		}

		//Check phase
		//POSITIVE PHASE
		else if (phase > 0){
			if (phase < phase3) {
				phase += deltaDir;
			}
			if (phase == phase1 || phase == phase2) {
				velX = 1;
			} else if (phase == phase3){
				deltaDir = 0;
				velX = 1;
			}
		}
		//NEGATIVE PHASE
		else if (phase < 0){
			if (phase > -phase3) {
				phase += deltaDir;
			}
			if (phase == -phase1 || phase == -phase2) {
				velX = -1;
			} else if (phase == -phase3){
				deltaDir = 0;
				velX = -1;
			}

		} else if (phase == 0 && deltaDir != 0) {
			phase += deltaDir;
			velX = deltaDir;

		}

		//IF PHASE ERROR
		//couldnt find out why sometimes phase passing the limit
		//this is used to correct the phase if that happens
		if (phase < -phase3) {
			phase = -phase3;
			//cout << "error detected";
		} else if (phase > phase3) {
			phase = phase3;
			//cout << "error detected";
		}

		//Check border collision
		if ((x==0 && velX==-1) || (x==border && velX==1)) {
			velX = 0;
			phase = 0;
			dir = 0;
		}

		//DEBUGGING
		//cout << phase << " | " << deltaDir << " | " << dir << endl;

		return velX;
	}
};

