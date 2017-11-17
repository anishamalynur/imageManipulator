#include <image.h>
#include <stdio.h>
#include <source.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>

class Filter;

Image::Image(void){
	
	width = 0;
	height = 0;
	pixList = NULL;
	isUpdated = false; 
}

Image::Image(int w, int h, Pixel* pixL){
	width = w;
	height = h;
	pixList= new Pixel[height*width];
	memcpy(pixList, pixL, height*width * sizeof(Pixel));
	isUpdated = false; 
}

Image::Image(Image &im){
	width = im.getWidth();
	height = im.getHeight(); 
	pixList= new Pixel[height*width];
	memcpy(pixList, im.pixList, height*width * sizeof(Pixel));
	isUpdated = false; 

}

void Image::ResetSize(int width, int height){
	this->width = width;
	this->height = height;
	delete [] pixList;
	this->pixList= new Pixel[height*width];
}

Pixel* Image::getPix() const{
	return this->pixList;

}

int Image::getWidth() const{
	
	return this->width;
}

int Image::getHeight() const{
	return this->height;
}

void Image::Update() const{
	if (isUpdated == false){
		
		theFilter->Update();
}
}

void Image::setFilter(Source* aFilter){
	this->theFilter = aFilter;
}

Image::~Image(){
	delete [] pixList;
}
