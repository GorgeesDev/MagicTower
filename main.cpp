#include <iostream>
#include <vector>

using namespace std;

class Player {
public:
	int x = 0;
	int y = 0;
	int hp = 100;
	int shield = 95;
	int damage = 40;
	int keys = 0;

	void playerStats() {
		cout << "HP: " << hp << endl;
		cout << "Shield: " << shield << endl;
		cout << "Damage: " << damage << endl;
		cout << "Keys owned: " << keys << endl;
	}
};

class Enemy {
public:
	string name;
	int hp;
	int shield;
	int damage;
	int x;
	int y;

	Enemy(string n, int h, int s, int d, int startR = 0, int startC = 0) {
		name = n;
		hp = h;
		shield = s;
		damage = d;
		y = startR;
		x = startC;
	}

	void showStats() {
		cout << "Enemy: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Shield: " << shield << endl;
		cout << "Damage: " << damage << endl;
	}

	void takeDamage(int amount) {
		hp -= amount;
		if (hp < 0) {
			hp = 0;
		}
	}

	bool isDead() {
		return hp <= 0;
	}
};

class Map {
public:
	vector<vector<char>> grid;
	int rows;
	int cols;

	void setupMap(int r, int c) {
		rows = r;
		cols = c;
		grid = vector<vector<char>>(rows, vector<char>(cols, ' '));
	}

	void loadTutorialMap() {
		setupMap(7, 13);

		for (int i = 0; i < 13; i++) {
			grid[0][i] = '*';
		}

		grid[1][0] = '*';
		grid[1][4] = '!';
		grid[1][7] = '+';
		grid[1][8] = '-';
		grid[1][9] = ';';
		grid[1][11] = '@';
		grid[1][12] = '*';

		grid[2][0] = '*';
		for (int i = 5; i < 13; i++) {
			grid[2][i] = '*';
		}

		grid[3][0] = '*';
		grid[3][5] = '^';
		grid[3][12] = '*';

		for (int i = 0; i < 10; i++) {
			grid[4][i] = '*';
		}
		grid[4][10] = '[';
		grid[4][11] = '*';
		grid[4][12] = '*';

		grid[5][0] = '*';
		grid[5][1] = 'G';
		grid[5][12] = '*';

		for (int i = 0; i < 13; i++) {
			grid[6][i] = '*';
		}
	}

	void loadForestDungeon() {
		setupMap(10, 20);

		string sketch[10] = {
			"********************",
			"*^                @*",
			"********[***********",
			"* +-; [            *",
			"*******           ^*",
			"*G    ***!**********",
			"*     !      *;* -+*",
			"*******      * *[***",
			"*^                 *",
			"********************"
		};

		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 20; c++) {
				grid[r][c] = sketch[r][c];
			}
		}
	}

	void buildCustomMap(int r, int c) {
		setupMap(r, c);
	}

	void showMap() {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				cout << grid[r][c] << ' ';
			}
			cout << endl;
		}
	}

	void setTile(int row, int col, char symbol) {
		if (row >= 0 && row < rows && col >= 0 && col < cols) {
			grid[row][col] = symbol;
		}
	}
};

class SavedDungeon {
public:
	string name;
	Map mapData;
	vector<Enemy> enemyData;
	int startX;
	int startY;

	SavedDungeon(string dungeonName, Map m, vector<Enemy> e, int x, int y) {
		name = dungeonName;
		mapData = m;
		enemyData = e;
		startX = x;
		startY = y;
	}
};

class Game {
private:
	Player hero;
	vector<Enemy> enemies;
	Map map;
	vector<SavedDungeon> customDungeons;

public:

	void showMenu() {
		int choice = 0;

		while (choice != 3) {
			cout << endl;
			cout << "|| MENU ||" << endl;
			cout << "1. Enter a Dungeon" << endl;
			cout << "2. Design a dungeon" << endl;
			cout << "3. Exit" << endl;
			cin >> choice;

			if (choice == 1) {
				playDungeonMenu();
			}
			else if (choice == 2) {
				customDungeon();
			}
			else if (choice == 3) {
				cout << "You have existed Dungeon Escape, good bye!" << endl;
			}
			else {
				cout << "Invalid choice. Try again!" << endl;
			}
		}
	}

	void playDungeonMenu() {
		int dungeonChoice;

		cout << endl;
		cout << "Choose a Dungeon:" << endl;
		cout << "1. Tutorial Dungeon" << endl;
		cout << "2. Forest Dungeon" << endl;

		for (int i = 0; i < customDungeons.size(); i++) {
			cout << i + 3 << ". " << customDungeons[i].name << endl;
		}

		cin >> dungeonChoice;

		if (dungeonChoice == 1) {
			map.loadTutorialMap();
			loadEnemiesForMap1();
			hero.x = 11;
			hero.y = 1;
			cout << endl << "Tutorial Dungeon loaded." << endl;
			showMapWithPlayer();
			cout << endl;
			showGameStats();
			movePlayer();
		}
		else if (dungeonChoice == 2) {
			map.loadForestDungeon();
			loadEnemiesForMap2();
			hero.x = 18;
			hero.y = 1;
			cout << endl << "Forest Dungeon loaded." << endl;
			showMapWithPlayer();
			cout << endl;
			showGameStats();
			movePlayer();
		}
		else if (dungeonChoice >= 3 && dungeonChoice < customDungeons.size() + 3) {
			int index = dungeonChoice - 3;

			map = customDungeons[index].mapData;
			enemies = customDungeons[index].enemyData;
			hero.x = customDungeons[index].startX;
			hero.y = customDungeons[index].startY;

			cout << endl << customDungeons[index].name << " loaded." << endl;
			showMapWithPlayer();
			cout << endl;
			showGameStats();
			movePlayer();
		}
		else {
			cout << "Invalid dungeon choice!" << endl;
		}
	}

	void saveCustomDungeon() {
		string dungeonName;

		cout << "Enter a name for this dungeon: ";
		cin >> dungeonName;

		customDungeons.push_back(SavedDungeon(dungeonName, map, enemies, hero.x, hero.y));

		cout << "Dungeon saved!" << endl;
	}

	void customDungeon() {
		int rows, cols;

		cout << endl;
		cout << "Enter number of rows: ";
		cin >> rows;
		cout << "Enter number of cols: ";
		cin >> cols;

		map.buildCustomMap(rows, cols);
		enemies.clear();
		hero.x = -1;
		hero.y = -1;

		buildCustomDungeonEditor();

		char saveChoice;
		cout << "Save this dungeon? (y/n): ";
		cin >> saveChoice;

		if (saveChoice == 'y' || saveChoice == 'Y') {
			saveCustomDungeon();
		}

		cout << "Returning to main menu..." << endl;
	}

	void showCustomGridWithNumbers() {
		cout << "   ";
		for (int c = 0; c < map.cols; c++) {
			cout << c + 1 << ' ';
		}
		cout << endl;

		for (int r = 0; r < map.rows; r++) {
			cout << r + 1 << ' ';
			if (r + 1 < 10) {
				cout << ' ';
			}

			for (int c = 0; c < map.cols; c++) {
				if (hero.x >= 0 && hero.y >= 0 && r == hero.y && c == hero.x) {
					cout << '@' << ' ';
				}
				else {
					cout << map.grid[r][c] << ' ';
				}
			}
			cout << endl;
		}
	}

	void buildCustomDungeonEditor() {
		int row, col;
		char symbol;

		while (true) {
			cout << endl;
			showCustomGridWithNumbers();
			cout << endl;

			cout << "Choose a row (1-" << map.rows << ") to add an object | Enter 0 to finish & save: ";
			cin >> row;

			if (row == 0) {
				break;
			}

			cout << "Choose a col (1-" << map.cols << "): ";
			cin >> col;

			cout << "Choose a symbol to place:" << endl;
			cout << "* = wall" << endl;
			cout << "G = goal" << endl;
			cout << "^ = key" << endl;
			cout << "[ = locked door" << endl;
			cout << "! = enemy" << endl;
			cout << "+ = health potion" << endl;
			cout << "- = strength potion" << endl;
			cout << "; = defense potion" << endl;
			cout << "@ = hero start" << endl;
			cout << "Enter symbol: ";
			cin >> symbol;

			if (row >= 1 && row <= map.rows && col >= 1 && col <= map.cols) {
				if (symbol == '@') {
					hero.x = col - 1;
					hero.y = row - 1;
					map.setTile(row - 1, col - 1, ' ');
				}
				else if (symbol == '!') {
					string enemyName;

					cout << "Enter enemy name: ";
					cin >> enemyName;

					addCustomEnemy(enemyName, 50, 50, 50, col - 1, row - 1);
					map.setTile(row - 1, col - 1, '!');
				}
				else {
					map.setTile(row - 1, col - 1, symbol);
				}
			}
			else {
				cout << "Invalid row or col." << endl;
			}
		}
	}

	int findEnemyAtPosition(int x, int y) {
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].x == x && enemies[i].y == y && enemies[i].hp > 0) {
				return i;
			}
		}
		return -1;
	}

	void showMapWithPlayer() {
		for (int r = 0; r < map.rows; r++) {
			for (int c = 0; c < map.cols; c++) {
				if (r == hero.y && c == hero.x) {
					cout << '@' << ' ';
				}
				else {
					cout << map.grid[r][c] << ' ';
				}
			}
			cout << endl;
		}
	}

	void loadEnemiesForMap1() {
		enemies.clear();

		enemies.push_back(Enemy("Monster", 50, 50, 50, 1, 4));
	}
	
	void loadEnemiesForMap2() {
		enemies.clear();
		enemies.push_back(Enemy("One eyed Monster", 50, 50, 50, 5, 9));
		enemies.push_back(Enemy("Three eyed Monster", 50, 50, 50, 6, 6));
	}

	void addCustomEnemy(string name, int hp, int shield, int damage, int x, int y) {
		enemies.push_back(Enemy(name, hp, shield, damage, x, y));
	}

	void showGameStats() {
		cout << "-----| HERO |-----" << endl;
		hero.playerStats();
		cout << endl;

		cout << "-----| ENEMIES |-----" << endl;
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].showStats();
			cout << endl;
		}
	}

	void playerAttack(int enemyIndex) {
		if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
			int damageAmount = hero.damage;

			if (enemies[enemyIndex].shield >= damageAmount) {
				enemies[enemyIndex].shield -= damageAmount;
			}
			else {
				int leftoverDamage = damageAmount - enemies[enemyIndex].shield;
				enemies[enemyIndex].shield = 0;
				enemies[enemyIndex].hp -= leftoverDamage;

				if (enemies[enemyIndex].hp < 0) {
					enemies[enemyIndex].hp = 0;
				}
			}

			cout << "Hero attacks " << enemies[enemyIndex].name
				<< " for " << hero.damage << " damage." << endl;
		}
	}

	void enemyAttack(int enemyIndex) {
		if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
			int damageAmount = enemies[enemyIndex].damage;

			if (hero.shield >= damageAmount) {
				hero.shield -= damageAmount;
			}
			else {
				int leftoverDamage = damageAmount - hero.shield;
				hero.shield = 0;
				hero.hp -= leftoverDamage;

				if (hero.hp < 0) {
					hero.hp = 0;
				}
			}

			cout << enemies[enemyIndex].name
				<< " attacks hero for " << enemies[enemyIndex].damage
				<< " damage." << endl;
		}
	}

	void battleRound(int enemyIndex) {
		if (enemyIndex >= 0 && enemyIndex < enemies.size()) {
			while (hero.hp > 0 && enemies[enemyIndex].hp > 0) {
				playerAttack(enemyIndex);

				if (enemies[enemyIndex].hp > 0) {
					enemyAttack(enemyIndex);
				}
			}
		}
	}

	void checkGameOver() {
		if (hero.hp <= 0) {
			cout << "Hero lost." << endl;
			return;
		}

		bool allEnemiesDead = true;

		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].hp > 0) {
				allEnemiesDead = false;
			}
		}

		if (allEnemiesDead) {
			cout << endl << "All enemies defeated.";
		}
		else {
			cout << "Battle continues." << endl;
		}
	}

	void movePlayer() {
		string move;

		while (true) {
			cout << endl << endl;
			showMapWithPlayer();
			cout << endl;
			hero.playerStats();
			cout << endl;

			cout << "Move left(l), right(r), up(u), down(d), quit(q): ";
			cin >> move;

			if (move == "quit" || move == "q") {
				break;
			}
			else if (move == "left" || move == "l") {
				if (tryMove(hero.x - 1, hero.y)) {
					showMapWithPlayer();
					cout << endl;
					hero.playerStats();
					break;
				}
			}
			else if (move == "right" || move == "r") {
				if (tryMove(hero.x + 1, hero.y)) {
					showMapWithPlayer();
					cout << endl;
					hero.playerStats();
					break;
				}
			}
			else if (move == "up" || move == "u") {
				if (tryMove(hero.x, hero.y - 1)) {
					showMapWithPlayer();
					cout << endl;
					hero.playerStats();
					break;
				}
			}
			else if (move == "down" || move == "d") {
				if (tryMove(hero.x, hero.y + 1)) {
					showMapWithPlayer();
					cout << endl;
					hero.playerStats();
					break;
				}
			}
			else {
				cout << "Invalid move." << endl;
			}
		}
	}

	bool tryMove(int newX, int newY) {
		if (newX < 0 || newX >= map.cols || newY < 0 || newY >= map.rows) {
			cout << "Out of bounds." << endl;
			return false;
		}

		char tile = map.grid[newY][newX];

		if (tile == '*') {
			cout << endl << "You hit a wall.";
			return false;
		}

		if (tile == '[') {
			if (hero.keys > 0) {
				hero.keys--;
				cout << endl << "You used a key to open the door.";
				map.grid[newY][newX] = ' ';
			}
			else {
				cout << endl << "The door is locked. You need a key.";
				return false;
			}
		}

		if (tile == '^') {
			hero.keys++;
			cout << endl << "You picked up a key.";
			map.grid[newY][newX] = ' ';
		}
		else if (tile == '!') {
			int enemyIndex = findEnemyAtPosition(newX, newY);

			if (enemyIndex != -1) {
				cout << endl << "You encountered " << enemies[enemyIndex].name << "." << endl;
				battleRound(enemyIndex);
				checkGameOver();

				if (hero.hp <= 0) {
					cout << "GAME OVER. Hero is defeated." << endl;
					return true;
				}

				if (enemies[enemyIndex].hp <= 0) {
					map.grid[newY][newX] = ' ';
				}
				else {
					return false;
				}
			}
		}
		else if (tile == '+') {
			cout << endl << "You drank a health potion.";
			hero.hp += 5;
			map.grid[newY][newX] = ' ';
		}
		else if (tile == '-') {
			cout << endl << "You drank a strength potion.";
			hero.damage += 5;
			map.grid[newY][newX] = ' ';
		}
		else if (tile == ';') {
			cout << endl << "You drank a defense potion.";
			hero.shield += 5;
			map.grid[newY][newX] = ' ';
		}
		else if (tile == 'G') {
			cout << endl << "YOU REACHED THE GOAL!" << endl;
			map.grid[newY][newX] = ' ';
			return true;
		}

		map.grid[hero.y][hero.x] = ' ';
		hero.x = newX;
		hero.y = newY;
		return false;
	}
};

int main() {

	Game game;
	game.showMenu();

	return 0;
	
}