#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <PNMreader.h>

using namespace std;



PNMreader::PNMreader(char* filename){
	
	im.theFilter = this;
	

	
	imageName = new char[strlen(filename) +1];
	strcpy(imageName, filename);
	
}

void PNMreader::Update(){
	
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);

	Execute();

	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);


}

const char* PNMreader::SourceName(){
	return "PNMreader";
}


void PNMreader::Execute(){
	FILE* f_in;

	f_in = fopen(this->imageName, "r");
	if (f_in == NULL){
	char msg[1024];
	sprintf(msg, "%s: wrong filename", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}
	
	char magicNum[128];
	int width, height, maxval;
	fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

	im.ResetSize(width, height);

	fread(im.getPix(), sizeof(Pixel), height * width, f_in);
	
	fclose(f_in);

	//im.isUpdated = true;
}

PNMreader::~PNMreader(){

	delete [] imageName;
}




