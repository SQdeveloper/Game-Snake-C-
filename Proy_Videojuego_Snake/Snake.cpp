#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string>

using namespace std;

void erase_menu();
void change_position(int x, int y);
void cursor_invisible();
void draw_limit();
int mat[200][2];
class Snake {
	int x, y, count = 0, tam = 3;
	string tec = "der";
public:
	Snake(int _x, int _y) : x(_x), y(_y) {}
	int xsnake() { return x; }
	int ysnake() { return y; }
	int Tam() { return tam; }
	void aument_tam() { tam += 1; }
	void move();
	void draw();
	void erase();
	void traslate_snake();
	void save_position();
	void teclear();
};

void Snake::traslate_snake() {
	if (x < 12) {
		erase();
		x = 107;
	}
	else if (x > 107) {
		erase();
		x = 13;
	}
	else if (y < 3) {
		erase();
		y = 26;
	}
	else if (y > 26) {
		erase();
		y = 2;
	}
}

void Snake::save_position() {
	mat[count][0] = x;
	mat[count][1] = y;
	count++;
	if (count == tam) {
		count = 0;
	}
}

void Snake::erase() {
	for (int i = 0; i < tam; i++) {
		change_position(mat[i][0], mat[i][1]); printf(" ");
	}
}

void Snake::draw() {
	for (int i = 0; i < tam; i++) {
		change_position(x, y); printf("%c", 64);
		change_position(mat[i][0], mat[i][1]); printf("%c", 254);
	}
}

void Snake::teclear() {
	if (_kbhit()) {
		char tecla = _getch();
		if (tecla == 72 && tec != "down")tec = "up";
		if (tecla == 80 && tec != "up")tec = "down";
		if (tecla == 75 && tec != "der")tec = "iz";
		if (tecla == 77 && tec != "iz")tec = "der";
		if (tecla == 'q')exit(0);
	}
}

void Snake::move() {
	erase();
	save_position();
	draw();

	teclear();
	if (tec == "up")y--;
	if (tec == "down")y++;
	if (tec == "iz")x--;
	if (tec == "der")x++;
	Sleep(150);
}

class Apple {
	int x, y;
public:
	Apple(int _x, int _y) : x(_x), y(_y) {}
	void move(class Snake& s);
};

void Apple::move(class Snake& s) {
	change_position(x, y); printf(" ");
	if (x == s.xsnake() && y == s.ysnake()) {
		x = 11 + rand() % 98;
		y = 2 + rand() % 26;
		s.aument_tam();
	}
	change_position(x, y); printf("%c", 157);
}

int main() {
	cursor_invisible();
	draw_limit();

	Snake s(70, 24);

	Apple a(24, 15);

	bool game_over = false;
	bool continuar = false;
	int _y = 15;

	do {
		while (!game_over) {
			a.move(s);
			s.move();
			s.teclear();
			s.traslate_snake();

			for (int i = 0; i < s.Tam(); i++) {
				if (s.xsnake() == mat[i][0] && s.ysnake() == mat[i][1]) {
					game_over = true;
				}
			}
		}

		while (true) {
			change_position(44, 15); printf("JUGAR DE NUEVO");
			change_position(44, 18); printf("SALIR DEL JUEGO");
			change_position(42, _y); printf(">");
			int aux = _y;
			char tecla = _getch();
			if (tecla == 13 && _y == 15) {
				continuar = true;
				game_over = false;
				erase_menu();
				break;
			}
			else if (tecla == 13 && _y == 18) {
				continuar = false;
				break;
			}
			else if (tecla == 72) {
				_y = 15;
			}
			else if (tecla == 80) {
				_y = 18;
			}
			change_position(42, aux); printf(" ");

		}
	} while (continuar == true);
}

void draw_limit() {
	for (int i = 11; i < 109; i++) {
		change_position(i, 1); printf("%c", 205);
		change_position(i, 28); printf("%c", 205);
	}
	for (int i = 2; i < 28; i++) {
		change_position(10, i); printf("%c", 186);
		change_position(109, i); printf("%c", 186);
	}
	change_position(10, 1); printf("%c", 201);
	change_position(10, 28); printf("%c", 200);
	change_position(109, 1); printf("%c", 187);
	change_position(109, 28); printf("%c", 188);
}

void change_position(int x, int y) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void cursor_invisible() {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = 20;

	SetConsoleCursorInfo(hCon, &cci);
}

void erase_menu() {
	change_position(44, 15); printf("                ");
	change_position(44, 18); printf("                ");
	change_position(42, 15); printf(" ");
	change_position(42, 18); printf(" ");
}