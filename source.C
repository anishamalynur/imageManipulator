#include <source.h>
#include <stdio.h>
#include <iterator>

/*void Source::Source(){
	getOutput()->SetFilter(&this);
}*/

int Source::arraySize = 0;
Source* Source::sourceArray[500] = {};

using namespace std;

Image* Source::GetOutput(){ 
	return &this->im;
}


void Source::addElement(Source* el){
	bool exists = false;
//printf("i got the the beg of the add");

	for(int i= 0; i<500; i++){
		if (sourceArray[i] == el){
//printf("i got to the mid of add");
			exists = true;
}
}
	

	if(exists && !im.isUpdated){
	char msg[1024];
	sprintf(msg, "Cyclical structure");
	DataFlowException e(SourceName(), msg);
	throw e;}

	sourceArray[arraySize++] = el;
}

void Source::delElement(Source* el){
	//printf("i got the the beg of the delete");
	for(int i= 0; i<500; i++){
		if (sourceArray[i] == el){
			//printf("i got here");
			sourceArray[i] == NULL;
			arraySize--;
}
}
}

//void Source::Update(){printf("i updatedddd");}
