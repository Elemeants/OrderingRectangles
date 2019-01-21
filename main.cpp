#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <vector>

#define DEBUG true

struct Widget {
private:
	unsigned int width;
	unsigned int height;
	unsigned int PosX;
	unsigned int PosY;
public:
	Widget() {
		this->width = 0;
		this->height = 0;
		this->PosX = 1;
		this->PosY = 1;
	}
	Widget(int width, int height, int PosX, int PosY) {
		this->width = width;
		this->height = height;
		this->PosX = PosX;
		this->PosY = PosY;
	}
	Widget(int width, int height) {
		this->width = width;
		this->height = height;
		this->PosX = 1;
		this->PosY = 1;
	}
	unsigned int GetWidth() { return this->width; };
	void SetWidth(int _width) { this->width = _width; };
	unsigned int GetHeight() { return this->height; };
	void SetHeight(int _Height) { this->height = _Height; };
	unsigned int GetPosX() { return this->PosX; };
	void SetPosX(int _PosX) { this->PosX = _PosX; };
	unsigned int GetPosY() { return this->PosY; };
	void SetPosY(int _PosY) { this->PosY = _PosY; };
};

struct Graphic 
{
public:
	static void gotoxy(int, int);
	static void Rectangle(int, int, int, int, char);
};

void Graphic::gotoxy(int x, int y) {
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}

void Graphic::Rectangle(int w, int h, int _x, int _y, char character){
	for(int x = _x; x <= (_x + w); x++) {
		Graphic::gotoxy(x, _y); printf("%c", character);
		Graphic::gotoxy(x, (_y + h)); printf("%c", character);
	}for(int y = _y; y <= (_y + h); y++) {
		Graphic::gotoxy(_x, y); printf("%c", character);
		Graphic::gotoxy((_x + w), y); printf("%c", character);
	}
}

struct WidgetBehaivor
{
public:
	void PrintData(Widget &widget, int index, int PosX, int PosY);
	void PrintWidget(Widget &widget);
};

void WidgetBehaivor::PrintData(Widget &widget, int index, int PosX, int PosY) {
	Graphic::gotoxy(PosX, 1 + PosY); printf("Rectangulo %i: ", index);
	Graphic::gotoxy(PosX, 2 + PosY); printf("   SIZE: (W: %02i, H: %02i)",
		widget.GetWidth(), widget.GetHeight());
	Graphic::gotoxy(PosX, 3 + PosY); printf("   POS : (X: %02i, Y: %02i)",
		widget.GetPosX(), widget.GetPosY());
}

void WidgetBehaivor::PrintWidget(Widget &widget) {
	for(int x = widget.GetPosX(); x < (widget.GetPosX() + widget.GetWidth()); x++) {
		Graphic::gotoxy(x, widget.GetPosY()); printf("#");
		Graphic::gotoxy(x, widget.GetPosY() + widget.GetHeight() - 1); printf("#");
	}for(int y = widget.GetPosY(); y < (widget.GetPosY() + widget.GetHeight()); y++) {
		Graphic::gotoxy(widget.GetPosX(), y); printf("#");
		Graphic::gotoxy(widget.GetPosX() + widget.GetWidth() - 1, y); printf("#");
	}
}

std::vector<Widget> GenerateWidgets(){
	std::vector<Widget> Widgets;
	Widgets.push_back(Widget(8, 4));
	Widgets.push_back(Widget(10, 4));
	Widgets.push_back(Widget(12, 8));
	Widgets.push_back(Widget(4, 4));
	Widgets.push_back(Widget(10, 4));
	Widgets.push_back(Widget(12, 4));
	Widgets.push_back(Widget(4, 4));
	Widgets.push_back(Widget(4, 4));
	Widgets.push_back(Widget(4, 4));	
	return Widgets;
}

std::vector<Widget> SortByWidthWidgets(std::vector<Widget> &Widgets) {
	Widget AuxWidget;
	for (int x = 0; x < Widgets.size(); x++) { 
		for (int j = x; j < Widgets.size(); j++) {
			if (Widgets.at(x).GetWidth() >= Widgets.at(j).GetWidth()) {
				AuxWidget = Widgets.at(x);
				Widgets.at(x) = Widgets.at(j);
				Widgets.at(j) = AuxWidget;
			}
		}
	}
	return Widgets;
}

std::vector<Widget> OrderWidgets(std::vector<Widget> Widgets, int N_COLS) {
	WidgetBehaivor WidgetBehaivor;
	SortByWidthWidgets(Widgets);
	unsigned int Handler_PosX = 1;
	unsigned int Handler_PosY = 1;
	unsigned int LayerHeight = 0;
	for (int x = 0; x < Widgets.size(); x++) {
		if (((Handler_PosX + Widgets.at(x).GetWidth()) > N_COLS)) { 
			Handler_PosX = 1; 
			Handler_PosY += LayerHeight; 
		}
		if (Widgets.at(x).GetHeight() > LayerHeight) {
			LayerHeight = Widgets.at(x).GetHeight(); 
		}
		Widgets.at(x).SetPosX(Handler_PosX);
		Widgets.at(x).SetPosY(Handler_PosY);
		WidgetBehaivor.PrintWidget(Widgets.at(x));
		WidgetBehaivor.PrintData(Widgets.at(x), x, 30, x * 4);
		Handler_PosX += (Widgets.at(x).GetWidth());
	}
	Graphic::Rectangle(24, Handler_PosY + LayerHeight, 0, 0, '+');
	return Widgets;
}

int main(int argc, char const *argv[])
{
	system("cls");
	OrderWidgets(GenerateWidgets(), 24);
	getch();
	system("cls");
	return 0;
}