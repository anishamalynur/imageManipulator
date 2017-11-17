#include <stdlib.h>
#include <sink.h>
#include <stdio.h>

#include <iostream>

using namespace std;

Sink::Sink(){
	im1 = NULL;
	im2 = NULL;
	isInput = false;
	isInput2 = false;
	//HasBeenSetTwice = false;
	//HasBeenSetTwice2 = false;

}

const Image* Sink::getInput(){
	return this->im1;
	
}
const Image* Sink::getInput2(){
	return this->im2;
}
void Sink::SetInput( Image* theImage){

	//if (isInput == true){
		//HasBeenSetTwice = true;}

	isInput = true;
	im1 = theImage;

}
void Sink::SetInput2( Image* theImage){

	//if (isInput2 == true){
		//HasBeenSetTwice2 = true;	}

	isInput2 = true;
	im2 = theImage;
}
