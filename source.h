#ifndef SOURCE_H
#define SOURCE_H
#include <iostream>
#include <image.h>
#include <logging.h>

using namespace std;



class Source{
	protected:
		Image im;
		virtual void Execute() = 0;
		
		
	public:
		static Source* sourceArray[500];
		static int arraySize;
		void addElement(Source* el);
		void delElement(Source* el);
		virtual const char* SourceName() = 0;
		Image* GetOutput();
		virtual void Update() = 0;
		
};


#endif
