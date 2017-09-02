#include <stdio.h>
#include <stdlib.h>

FILE* OpenFile(int argc, char** argv);
int GetHeaders(FILE* fp, int* w, int* h);
char* GetRaw(FILE* fp, int bytes);
int Pad(int num, int bits);
void PutBraille(char* rawBraille, int row, int col, int wchars);
char* BmpToBraille(char* bmp, int w, int h, int wbytes, int bytes, int* wchars, int* hchars);
char* RawToUnicodeBraille(char* rawBraille, int wchars, int hchars);

const char* BRAILLE = "⠀";

int main(int argc, char** argv)
{
	FILE* fp = OpenFile(argc, argv);

	if (fp == NULL) {
		perror("Failed to open stream");
		return EXIT_FAILURE;
	}

	int w = 0,
	    h = 0,
	    wbytes = 0,
	    bytes = 0;
	char* bitmap;

	if ( !GetHeaders(fp, &w, &h) ) {
		fputs("Error: not a valid PBM file!\n", stderr);
		return EXIT_FAILURE;
	}

	wbytes = Pad(w, 8);
	bytes = wbytes * h;

	if ( (bitmap = GetRaw(fp, bytes)) == NULL ) {
		fputs("Error: not a valid PBM file!\n", stderr);
		return EXIT_FAILURE;
	}

	int wchars,
	    hchars;

	char* rawBraille = BmpToBraille(bitmap, w, h, wbytes, bytes, &wchars, &hchars);
	char* braille = RawToUnicodeBraille(rawBraille, wchars, hchars);

	printf("%s\n", braille);


	free(bitmap);
	free(rawBraille);
	free(braille);

	fclose(fp);
	return 0;
}

FILE* OpenFile(int argc, char** argv)
{
	if (argc == 2) {
		return fopen(argv[1], "rb");
	} else {
		return stdin;
	}
}

int GetHeaders(FILE* fp, int* w, int* h)
{
	int word = 0;
	while (word < 3) {
		int c = getc(fp);
		if (c == EOF)
			return 0;
		if (c == '#') {
			while (c != '\n') {
				c = getc(fp);
				if (c == EOF)
					return 0;
			}
		} else if (c == ' ' || c == '\n') {
			word++;
		} else if (word) {
			int* num = word == 1 ? w : h;
			*num *= 10;
			*num += c - 48;
		}
	}
	return 1;
}

char* GetRaw(FILE* fp, int bytes)
{
	char* bitmap = (char*)malloc(bytes);
	for (int i = 0; i < bytes; i++) {
		int c = getc(fp);
		if (c == EOF) {
			free(bitmap);
			return NULL;
		} else {
			bitmap[i] = c;
		}
	}
	return bitmap;
}

int Pad(int num, int bits)
{
	return (num + bits - 1) / bits;
}

void PutBraille(char* rawBraille, int row, int col, int wchars)
{
	int posX = col % 2;
	int posY = row % 4;
	int pos = 0;
	/*
	   0 3
	   1 4
	   2 5
	   6 7
	*/
	if (posY != 3) {
		pos = posY + 3 * posX;
	} else {
		pos = 6 + posX;
	}

	rawBraille[(row / 4) * wchars + (col / 2)] |= 1 << pos;
}

char* BmpToBraille(char* bmp, int w, int h, int wbytes, int bytes, int* wchars, int* hchars)
{
	*wchars = Pad(w, 2);
	*hchars = Pad(h, 4);
	int chars = *wchars * *hchars;

	char* rawBraille = (char*)malloc(chars);

	for (int i = 0; i < chars; i++) {
		rawBraille[i] = 0;
	}

	for (int bytei = 0; bytei < bytes; bytei++) {
		int bytecol = bytei % wbytes;
		int row = bytei / wbytes;

		for (int bitcol = 0; bitcol < 8; bitcol++) {
			if (bmp[bytei] & (char)(1 << bitcol)) {
				int col = bytecol * 8 + 7 - bitcol;
				PutBraille(rawBraille, row, col, *wchars);
			}
		}
	}

	return rawBraille;
}

char* RawToUnicodeBraille(char* rawBraille, int wchars, int hchars)
{
	int chars = wchars * hchars;
	int destChars = chars * 3 + hchars;
	char* braille = (char*)malloc(destChars);
	int strIndex = 0;
	for (int i = 0; i < chars; i++) {
		if ((i % wchars == 0) && i) {
			braille[strIndex] = '\n';
			strIndex++;
		}
		braille[strIndex] = BRAILLE[0];
		strIndex++;
		braille[strIndex] = BRAILLE[1] | ((unsigned char)rawBraille[i] / (1 << 6));
		strIndex++;
		braille[strIndex] = BRAILLE[2] | ((unsigned char)rawBraille[i] % (1 << 6));
		strIndex++;
	}
	braille[destChars - 1] = '\0';
	return braille;
}
