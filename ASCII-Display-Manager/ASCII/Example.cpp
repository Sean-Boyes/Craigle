#include "Cursor.h"
#include "TextEffects.h"

int main()
{
	//cout << "works?";
	//CsrMove('l', 1);
	//cout << "!" << endl;
	//Pobject pika;
	//pika.load("pika.txt");
	//pika.place(0, 2);
	//CsrMove('d', 2);
	//Pobject canvas;
	//canvas.load("canvas.txt");
	//canvas.place();
	//string colour;
	//bool bright;
	//bool background;
	//while (true)
	//{	
	//	cout << endl << "colour :";
	//	cin >> colour;
	//	cout << endl << "bright? :";
	//	cin >> bright;
	//	cout << endl << "background? :";
	//	cin >> background;
	//	getColour(colour, bright, background);
	//}
	//CsrMoveTo(0, 0);
	//int mod;
	//cin >> mod;
	//cout << endl;

	//
	//SGRCodeTest();

	//cout << "\x1b[48;2;255;0;255m" << "hello" << endl;

	//cout << endl << endl;

	ASCIIobject screen, menu, border;
	screen.createCanvas(40, 20);
	screen.paint(getEffect('u'));
	screen.place();

	menu.createCanvas(20, 5, "~", "|");
	menu.paint(getColour("white", 0, 1));
	menu.place(3, 3);

	border.createCanvas(15, 10, "_", "}", "O", "O", "O", "O");
	border.paint(getColour("blue", 1, 0));
	border.place(24, 9);

	CsrMoveTo(screen.dimension[0] + 1, screen.dimension[1] + 1);

	return 0;
}