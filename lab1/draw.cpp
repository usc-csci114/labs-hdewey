#include <iostream>
#include "bmplib.h"
#include "drawing.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}

	string inputFile = argv[1];
	// string outputFile = argv[2];
	string outputFile = "output.bmp";

	Drawing drawing;

	drawing.parse(inputFile);

	drawing.draw();

	drawing.write(outputFile);

	cout << "Drawing finished. Output saved to " << outputFile << endl;

	return 0;
}