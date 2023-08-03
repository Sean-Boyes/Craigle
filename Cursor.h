#pragma once

#include "Cursor.cpp"

inline void CsrMoveTo(int x, int y); // Moves cursor 'x' from the top, and 'y' from the left.
inline void CsrMove(char direction, int n);

class ASCIIobject
{
private:
	int numberOfColours = 8;
	double goldenRatio = (1 + sqrt(5)) / 2;
public:
	image data;
	int dimension[2] = { 0,0 };
	std::string file = "null.txt";

	void load(std::string file)
	{
		file = file;
		std::ifstream newfile(file);

		std::string tmpString;
		image tmpCanvas;
		line tmpLine;

		if (newfile.is_open())
		{
			dimension[1] = 0;
			while (getline(newfile, tmpString))
			{
				dimension[0] = 0;
				while (dimension[0] < tmpString.size())
				{
					std::string s;
					s.push_back(tmpString[dimension[0]]);
					tmpLine.push_back(s);
					dimension[0] += 1;
				}
				tmpCanvas.push_back(tmpLine);
				tmpLine.clear();
				dimension[1] += 1;
			}
			newfile.close();
		}
		data = tmpCanvas;
	}
	void place() // Places object where the cursor is at
	{
		for (line i : data)
		{
			for (std::string ii : i)
			{
				std::cout << ii;
			}
			std::cout << std::endl;
		}
	}
	void place(int x, int y) // Overloaded to place at coordinates
	{
		CsrMoveTo(x, y);
		for (line i : data)
		{
			for (std::string ii : i)
			{
				std::cout << ii;
			}
			std::cout << std::endl;
			CsrMove('r', x - 1);
		}
	}
	void add(std::string str, int x, int y)
	{
		int currentx = 0;
		while (currentx < str.length())
		{
			data[y][x] = str[currentx];
			currentx++;
		}
	}
	void add(ASCIIobject obj, int x, int y)
	{
		int currentx = 0;
		int currenty = 0;

		while (currenty < obj.dimension[1])
		{
			while (currentx < obj.dimension[0])
			{
				data[currenty + y][currentx + x] = obj.data[currenty][currentx];
				currentx++;
			}
			currentx = 0;
			currenty++;
		}
	}
	void createCanvas(int sizeX, int sizeY)
	{
		image tempData;
		line tempLine;
		std::string tempString;

		// Top canvas
		tempLine.push_back("/"); // insert "/"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back("-"); // insert "-"
		}
		tempLine.push_back("\\"); // insert "\"
		tempData.push_back(tempLine); // next line
		// Middle canvas
		for (int i = 0; i < sizeY - 2; i++)
		{
			tempLine.clear();
			tempLine.push_back("|"); // insert "|" in 
			for (int ii = 0; ii < sizeX - 2; ii++)
			{
				tempLine.push_back(" "); // insert "-" in
			}
			tempLine.push_back("|"); // insert "|"
			tempData.push_back(tempLine); // next line
		}
		tempLine.clear();

		// Bottom canvas
		tempLine.push_back("\\"); // insert "\"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back("-"); // insert "|"
		}
		tempLine.push_back("/"); // insert "/"
		tempData.push_back(tempLine); // next line

		data = tempData;
		dimension[0] = sizeX;
		dimension[1] = sizeY;
	}
	void createCanvas(int sizeX, int sizeY, std::string vLine, std::string hLine) // Multi-Character lines will skew the size.
	{
		image tempData;
		line tempLine;
		std::string tempString;

		// Top canvas
		tempLine.push_back("/"); // insert "/"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(vLine); // insert "-"
		}
		tempLine.push_back("\\"); // insert "\"
		tempData.push_back(tempLine); // next line
		// Middle canvas
		for (int i = 0; i < sizeY - 2; i++)
		{
			tempLine.clear();
			tempLine.push_back(hLine); // insert "|" in 
			for (int ii = 0; ii < sizeX - 2; ii++)
			{
				tempLine.push_back(" "); // insert "-" in
			}
			tempLine.push_back(hLine); // insert "|"
			tempData.push_back(tempLine); // next line
		}
		tempLine.clear();

		// Bottom canvas
		tempLine.push_back("\\"); // insert "\"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(vLine); // insert "|"
		}
		tempLine.push_back("/"); // insert "/"
		tempData.push_back(tempLine); // next line

		data = tempData;
		dimension[0] = sizeX;
		dimension[1] = sizeY;
	}
	void createCanvas(int sizeX, int sizeY, std::string hLine, std::string vLine, std::string cornerTL, std::string cornerTR, std::string cornerBL, std::string cornerBR) // Multi-Character lines and/or corners will skew the size.
	{
		image tempData;
		line tempLine;
		std::string tempString;

		// Top canvas
		tempLine.push_back(cornerTL); // insert "/"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(hLine); // insert "-"
		}
		tempLine.push_back(cornerTR); // insert "\"
		tempData.push_back(tempLine); // next line
		// Middle canvas
		for (int i = 0; i < sizeY - 2; i++)
		{
			tempLine.clear();
			tempLine.push_back(vLine); // insert "|" in 
			for (int ii = 0; ii < sizeX - 2; ii++)
			{
				tempLine.push_back(" "); // insert "-" in
			}
			tempLine.push_back(vLine); // insert "|"
			tempData.push_back(tempLine); // next line
		}
		tempLine.clear();

		// Bottom canvas
		tempLine.push_back(cornerBL); // insert "\"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(hLine); // insert "|"
		}
		tempLine.push_back(cornerBR); // insert "/"
		tempData.push_back(tempLine); // next line

		data = tempData;
		dimension[0] = sizeX;
		dimension[1] = sizeY;
	}
	void createCanvas(int sizeX, int sizeY, std::string topHLine, std::string leftVLine, std::string bottomHLine, std::string rightVLine, std::string cornerTL, std::string cornerTR, std::string cornerBL, std::string cornerBR) // Multi-Character lines and/or corners will skew the size.
	{
		image tempData;
		line tempLine;
		std::string tempString;

		// Top canvas
		tempLine.push_back(cornerTL); // insert "/"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(topHLine); // insert "-"
		}
		tempLine.push_back(cornerTR); // insert "\"
		tempData.push_back(tempLine); // next line
		// Middle canvas
		for (int i = 0; i < sizeY - 2; i++)
		{
			tempLine.clear();
			tempLine.push_back(leftVLine); // insert "|" in 
			for (int ii = 0; ii < sizeX - 2; ii++)
			{
				tempLine.push_back(" "); // insert "-" in
			}
			tempLine.push_back(rightVLine); // insert "|"
			tempData.push_back(tempLine); // next line
		}
		tempLine.clear();

		// Bottom canvas
		tempLine.push_back(cornerBL); // insert "\"
		for (int i = 0; i < sizeX - 2; i++)
		{
			tempLine.push_back(bottomHLine); // insert "|"
		}
		tempLine.push_back(cornerBR); // insert "/"
		tempData.push_back(tempLine); // next line

		data = tempData;
		dimension[0] = sizeX;
		dimension[1] = sizeY;
	}

	void paint(std::string colourCode)
	{
		std::string tempString;
		for (int ii = 0; ii < dimension[1]; ii++)
		{
			for (int i = 0; i < dimension[0]; i++)
			{
				tempString = data[ii][i];
				data[ii][i] = colourCode;
				data[ii][i] += tempString;
				data[ii][i] += "\x1b[0m";
			}
		}
	}
};