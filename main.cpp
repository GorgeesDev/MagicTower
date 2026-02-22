#include <iostream>
#include <iomanip>

using namespace std;

class game {
private:
	char symbol;

public:
	void fillSpaceGrid(int row, int col) {
		for (short r = row; r <= row; r++) {     ////this fills the grid with a character
			cout << setfill(symbol);
			for (short c = col; c <= col; c++) {
				cout << setfill(symbol);
			}
			cout << endl;
			return;
		}
	}
	void blankSpaceGrid(int row, int col) {
		for (short r = row; r <= row; r++) {     ////this creates a empty grid
			cout << " ";
			for (short c = col; c <= col; c++) {
				cout << " ";
			}
			cout << endl;
		}
		return;
	}



	void tutorialMap() {
		cout << "*************";
		cout << "*   !  +-; @*";
		cout << "*    ********";
		cout << "*    ^      *";
		cout << "**********[**";
		cout << "*G          *";
		cout << "*************";
	}

	void MonsterDungeon() {
		cout << "********************";
		cout << "*^                @*";
		cout << "********[***********";
		cout << "* +-; [            *";
		cout << "*******           ^*";
		cout << "*G    ***!**********";
		cout << "*     !      *;* -+*";
		cout << "*******      * *[***";
		cout << "*^                 *";
		cout << "********************";
	}

};


int main() {

	cout << "Welcome to Magic Tower: Revenge of the Warlock Part VII" << endl << endl;
	cout << "1) Enter a dungeon" << endl << "2) Design a dungeon" << endl << "3) Exit" << endl;
	int option1;
	cin >> option1;

	cout << "Dungeons available: " << endl << endl << "1) Tutorial" << endl << "2) Forest" << endl;

	cout << "walls = *";
	cout << "player = @";
	cout << "goal = G";
	cout << "keys = ^";
	cout << "locked doors = [";
	cout << "enemies = !";
	cout << "health potions = +";
	cout << "strength potions = -";
	cout << "defense potions = ;";

	




}