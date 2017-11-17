#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <PNMwriter.h>	

void WriteImage(char *filename, const Image &img)
{
	FILE * f_out;
	f_out = fopen(filename, "wb");
	int wid = img.getWidth();
	int heg = img.getHeight();
	//int maxva = img->maxval;
	//char* magNum = img->magicNum;

	fprintf(f_out, "%s\n", "P6");
	fprintf(f_out, "%d %d\n", wid, heg);
	fprintf(f_out, "%d\n", 255);
	
	
	fwrite(img.getPix(), sizeof(Pixel), wid * heg, f_out);
	fclose(f_out);

}

void PNMwriter::Write(char* filename){

	WriteImage(filename, *getInput());

}
