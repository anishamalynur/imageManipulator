#include <iostream>
#include <filters.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Shrinker::Shrinker(){
	im.theFilter = this;
	//getOutput()->SetFilter(im);
}


LRConcat::LRConcat(){
	im.theFilter = this;
	//getOutput()->SetFilter(this);
}

TBConcat::TBConcat(){
	im.theFilter = this;
	//getOutput()->SetFilter(this);
}

Blender::Blender(){
	im.theFilter = this;
	//getOutput()->SetFilter(this);
}


Blur::Blur(){
	im.theFilter = this;

}

Rotate::Rotate(){
	im.theFilter = this;
}

Subtract::Subtract(){
	im.theFilter = this;
}

Mirror::Mirror(){
	im.theFilter = this;
}

Grayscale::Grayscale(){
	im.theFilter = this;
}

Color::Color(int w, int h, int r,  int g ,int b){
	im.ResetSize(w, h);
	red = r;
	green = g;
	blue = b;
	im.theFilter = this;	

}
const char* Shrinker::SourceName(){
	return "Shrinker";
}


const char* LRConcat::SourceName(){
	return "LRConcat";
}

const char* TBConcat::SourceName(){
	return "TBConcat";
}

const char* Blender::SourceName(){
	return "Blender";
}

const char* Blur::SourceName(){
	return "Blur";
}

const char* Rotate::SourceName(){
	return "Rotate";
}

const char* Subtract::SourceName(){
	return "Subtract";
}

const char* Mirror::SourceName(){
	return "Mirror";
}


const char* Grayscale::SourceName(){
	return "Grayscale";
}

const char* Color::SourceName(){
	return "Color";
}

void Color::Update(){
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);

	Execute();

	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
}

void Filter::Update(){

	char msg[128];

	if(getInput() == NULL){
	char msg[1024];
	sprintf(msg, "%s: No input! ", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}

	if(getInput() == GetOutput() || getInput2() == GetOutput()){
	char msg[1024];
	sprintf(msg, "%s: Passing inself ", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}


	if(isInput == true && !(getInput()->isUpdated)){
		
		addElement(this);

		sprintf(msg, "%s: about to update input 1", SourceName());
		Logger::LogEvent(msg);

		getInput()->Update();

		sprintf(msg, "%s: done updating input 1", SourceName());
		Logger::LogEvent(msg);

		getInput()->isUpdated = true;
	}

	if(isInput2 == true && !(getInput2()->isUpdated)){
		
		

		sprintf(msg, "%s: about to update input 2", SourceName());
		Logger::LogEvent(msg);

		getInput2()->Update();

		sprintf(msg, "%s: done updating input 2", SourceName());
		Logger::LogEvent(msg);

		getInput2()->isUpdated = true;
	}

	sprintf(msg,"%s:done executing", SourceName());
	Logger::LogEvent(msg);
	this->Execute();
}

	






void Shrinker::Execute(){

	
	im.ResetSize(im1->getWidth()/2,im1->getHeight()/2);
	Pixel* myPix = im1->getPix();
	Pixel* thePix = im.getPix();
	
	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){

			thePix[ i * im.getWidth() + j] = myPix[ 2 *(i * im1->getWidth()) +  2*j];

		}
	}
	

}

void LRConcat::Execute(){


	
	//fprintf(stderr, "in execute %p %p", im1, im2);
	if(isInput2 == false){
	char msg[1024];
	sprintf(msg, "%s: missing input 2 ", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}

	if (im1->getHeight() != im2->getHeight()){
	char msg[1024];
	sprintf(msg, "%s: heights must match: %d, %d", SourceName(), im1->getHeight(), im2->getHeight());
	DataFlowException e(SourceName(), msg);
	throw e;}


	im.ResetSize(im1->getWidth() + im2->getWidth(), im1->getHeight());
	
	Pixel* myPix1 = im1->getPix();
	Pixel* myPix2 = im2->getPix();
	Pixel* thePix = im.getPix();

	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im1->getWidth(); j++){
			thePix[ i * im.getWidth() + j] = myPix1[ (i * im1->getWidth()) +  j];
}
			
		for(int j = 0; j< im2->getWidth(); j++){
			thePix[ i * im.getWidth() + j + im1->getWidth()] = myPix2[ (i * im2->getWidth()) +  j];}

}


}


void TBConcat::Execute(){
	
	if(isInput2 == false){
	char msg[1024];
	sprintf(msg, "%s: missing input 2 ", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}


	if (im1->getWidth() != im2->getWidth()){
	char msg[1024];
	sprintf(msg, "%s: Widths must match: %d, %d", SourceName(), im1->getWidth(), im2->getWidth());
	DataFlowException e(SourceName(), msg);
	throw e;}
	
	im.ResetSize(im1->getWidth(),im1->getHeight() + im2->getHeight());
	Pixel* myPix1 = im1->getPix();
	Pixel* myPix2 = im2->getPix();
	Pixel* thePix = im.getPix();

	


	for(int i = 0; i< im1->getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			thePix[ i * im.getWidth() + j] = myPix1[ (i * im1->getWidth()) +  j];}
	}		//curPlace++;
	for(int i = 0; i< im2->getHeight(); i++){	
		for(int j = 0; j< im.getWidth(); j++){




			int input1Row ;
			int input2Row;
			int input1Index;
			int input2Index;
			int outputRow;
			int outputIndex;
			thePix[ (i + im1->getHeight()) * im.getWidth() + j] = myPix2[ (i * im2->getWidth()) +  j];
			if(((i + im1->getHeight()) * im.getWidth() + j) >= im.getHeight() * im.getWidth() ){
				//printf("BAD MEMORY %d", (i + im2->getHeight()) * im.getWidth() + j);
				//printf("%d  ", im.getHeight() * im.getWidth()); 105105
}

			}

	}


}

void Blender::SetFactor(float num){

	this->factor = num;

}



void Blender::Execute(){


	if(factor < 0 || factor > 1){
	char msg[1024];
	sprintf(msg, "%s: invalid factor: %f ", SourceName(), factor);
	DataFlowException e(SourceName(), msg);
	throw e;}

	if (im1->getHeight() != im2->getHeight() || im1->getWidth() != im2->getWidth() ){
	char msg[1024];
	sprintf(msg, "%s: dimensions must match", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}

	im.ResetSize(im1->getWidth(),im1->getHeight());
	Pixel* myPix1 = im1->getPix();
	Pixel* myPix2 = im2->getPix();
	Pixel* thePix = im.getPix();
	
	
	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			thePix[ i * im.getWidth() + j].r = myPix1[ (i * im1->getWidth()) +  j].r * this->factor + myPix2[ (i * im2->getWidth()) +  j].r * (1 - this->factor);
			thePix[ i * im.getWidth() + j].g = myPix1[ (i * im1->getWidth()) +  j].g * this->factor + myPix2[ (i * im2->getWidth()) +  j].g * (1 - this->factor);
			thePix[ i * im.getWidth() + j].b = myPix1[ (i * im1->getWidth()) +  j].b * this->factor + myPix2[ (i * im2->getWidth()) +  j].b * (1 - this->factor);

		}
	}

}


void Blur::Execute(){


	im.ResetSize(im1->getWidth(),im1->getHeight());
	Pixel* myPix1 = im1->getPix();
	//Pixel* myPix2 = im2->getPix();
	Pixel* thePix = im.getPix();
	
	
	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			if(i != 0 && i != im.getHeight() -1 && j != 0 && j !=  im.getWidth() -1){

			thePix[ i * im.getWidth() + j].r = myPix1[ (i-1) * im1->getWidth() +  j -1].r/8  + myPix1[ (i -1)* im1->getWidth() +  j ].r/8 +  myPix1[ (i-1) * im1->getWidth() +  j  +1].r/8  +  myPix1[ i * im1->getWidth()  +  j -1 ].r/8 + myPix1[ i * im1->getWidth()  +  j +1 ].r/8 + myPix1[ (i+1) * im1->getWidth() +  j -1 ].r/8 + myPix1[ (i+1)* im1->getWidth() +  j ].r/8 +  myPix1[ (i+ 1) * im1->getWidth() +  j+1].r/8;

			thePix[ i * im.getWidth() + j].g = myPix1[ (i-1) * im1->getWidth() +  j -1].g/8  + myPix1[ (i -1)* im1->getWidth() +  j ].g/8 +  myPix1[ (i-1) * im1->getWidth() +  j  +1].g/8  +  myPix1[ i * im1->getWidth()  +  j -1 ].g/8 + myPix1[ i * im1->getWidth()  +  j +1 ].g/8 + myPix1[ (i+1) * im1->getWidth() +  j -1 ].g/8 + myPix1[ (i+1)* im1->getWidth() +  j ].g/8 +  myPix1[ (i+ 1) * im1->getWidth() +  j+1].g/8;

			thePix[ i * im.getWidth() + j].b = myPix1[ (i-1) * im1->getWidth() +  j -1].b/8  + myPix1[ (i -1)* im1->getWidth() +  j ].b/8 +  myPix1[ (i-1) * im1->getWidth() +  j  +1].b/8  +  myPix1[ i * im1->getWidth()  +  j -1 ].b/8 + myPix1[ i * im1->getWidth()  +  j +1 ].b/8 + myPix1[ (i+1) * im1->getWidth() +  j -1 ].b/8 + myPix1[ (i+1)* im1->getWidth() +  j ].b/8 +  myPix1[ (i+ 1) * im1->getWidth() +  j+1].b/8;
			}
		else{
			thePix[ i * im.getWidth() + j] = myPix1[ i * im.getWidth() + j];
}

		}
	}

}




void Rotate::Execute(){


	
	im.ResetSize(im1->getHeight(), im1->getWidth());
	//printf("height is %d", im.getHeight());
	//printf("width is %d", im.getWidth());
	Pixel* myPix1 = im1->getPix();
	Pixel* thePix = im.getPix();



	
	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			//thePix[ i * im.getWidth() + j] = myPix1[ ((im1->getHeight() -1 ) -i )  * im1->getWidth() +  j];
			thePix[ i * im.getWidth() + j] = myPix1[ im1->getWidth() * (im1->getHeight() - (j +1) ) + i];
		}
	}

}

void Subtract::Execute(){

	if(isInput2 == false){
	char msg[1024];
	sprintf(msg, "%s: missing input 2 ", SourceName());
	DataFlowException e(SourceName(), msg);
	throw e;}

	
	if (im1->getHeight() != im2->getHeight() || im1->getWidth() != im2->getWidth()){
	char msg[1024];
	sprintf(msg, "%s: heights must match: %d, %d", SourceName(), im1->getHeight(), im2->getHeight());
	DataFlowException e(SourceName(), msg);
	throw e;}

	
	im.ResetSize(im1->getWidth(),im2->getHeight());
	Pixel* myPix1 = im1->getPix();
	Pixel* myPix2 = im2->getPix();
	Pixel* thePix = im.getPix();


	for(int i = 0; i< im1->getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			if(myPix1[ (i * im1->getWidth()) +  j].r > myPix2[ (i * im2->getWidth()) +  j].r){
				thePix[ i * im.getWidth() + j].r = myPix1[ (i * im1->getWidth()) +  j].r - myPix2[ (i * im2->getWidth()) +  j].r;}
			else{
				thePix[ i * im.getWidth() + j].r = 0;}
			if(myPix1[ (i * im1->getWidth()) +  j].g > myPix2[ (i * im2->getWidth()) +  j].g){
				thePix[ i * im.getWidth() + j].g = myPix1[ (i * im1->getWidth()) +  j].g - myPix2[ (i * im2->getWidth()) +  j].g;}
			else{
				thePix[ i * im.getWidth() + j].g = 0;}
			if(myPix1[ (i * im1->getWidth()) +  j].b > myPix2[ (i * im2->getWidth()) +  j].b){
				thePix[ i * im.getWidth() + j].b = myPix1[ (i * im1->getWidth()) +  j].b - myPix2[ (i * im2->getWidth()) +  j].b;}
			else{
				thePix[ i * im.getWidth() + j].b = 0;}
			
	}		

}		

}


void Mirror::Execute(){


	
	im.ResetSize(im1->getWidth(),im1->getHeight());
	//printf("height is %d", im.getHeight());
	//printf("width is %d", im.getWidth());
	Pixel* myPix1 = im1->getPix();
	Pixel* thePix = im.getPix();



	
	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			//thePix[ i * im.getWidth() + j] = myPix1[ ((im1->getHeight() -1 ) -i )  * im1->getWidth() +  j];
			//thePix[ i * im.getWidth() + j] = myPix1[ im1->getWidth() * (im1->getHeight() - (j +1) ) + i];
			thePix[ i * im.getWidth() + j] = myPix1[ i * im.getWidth() + (im.getWidth()  - j-1)];
		}
	}

}


void Grayscale::Execute(){


	
	im.ResetSize(im1->getWidth(),im1->getHeight());
	Pixel* myPix1 = im1->getPix();
	Pixel* thePix = im.getPix();


	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			thePix[ i * im.getWidth() + j].r = myPix1[ (i * im1->getWidth()) +  j].r/5 + myPix1[ (i * im1->getWidth()) +  j].g/2 + myPix1[ (i * im1->getWidth()) +  j].b/4;
			thePix[ i * im.getWidth() + j].b = myPix1[ (i * im1->getWidth()) +  j].r/5 + myPix1[ (i * im1->getWidth()) +  j].g/2 + myPix1[ (i * im1->getWidth()) +  j].b/4;
			thePix[ i * im.getWidth() + j].g = myPix1[ (i * im1->getWidth()) +  j].r/5 + myPix1[ (i * im1->getWidth()) +  j].g/2 + myPix1[ (i * im1->getWidth()) +  j].b/4;
			
	}		

}		

}

void Color::Execute(){

	Pixel* thePix = im.getPix();

	for(int i = 0; i< im.getHeight(); i++){
		for(int j = 0; j< im.getWidth(); j++){
			thePix[ i * im.getWidth() + j].r = red;
			thePix[ i * im.getWidth() + j].b = blue;
			thePix[ i * im.getWidth() + j].g = green;
			
	}		

}
}


void CheckSum::OutputCheckSum( char* name){
	FILE* file;
	unsigned int totRed = 0;
	unsigned int totGreen = 0;
	unsigned int totBlue = 0;

	Pixel* thePix = im1->getPix();
	
	for(int i = 0; i< im1->getHeight(); i++){
		for(int j = 0; j< im1 -> getWidth(); j++){
			totRed += thePix[ i * im1->getWidth() + j].r;
			totGreen += thePix[ i * im1->getWidth() + j].g;
			totBlue += thePix[ i * im1->getWidth() + j].b;
			
	}		

}
	totRed = totRed % 256;
	totGreen = totGreen % 256;
	totBlue = totBlue % 256;
	
	file = fopen(name, "w");
	

	
	fprintf(file, "CHECKSUM: %d, %d, %d\n", totRed, totGreen, totBlue);

	fclose(file);

}
