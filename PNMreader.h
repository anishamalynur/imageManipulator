

#ifndef PNMreader_H
#define PNMreader_H
#include <iostream>
#include <source.h>

using namespace std;

class PNMreader: public Source
{

	private:
		char* imageName;
	public:
		virtual void Execute();
		virtual void Update();
		PNMreader(char* filename);
		~PNMreader();
		virtual const char* SourceName();

};


#endif
