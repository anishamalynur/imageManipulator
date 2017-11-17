#include <iostream>
#include <Filter.h>

using namespace std;

class Shrinker: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Shrinker();
};


class LRConcat: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		LRConcat();
};

class TBConcat: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		TBConcat();
};

class Blender: public Filter{
	private:
		float factor;
	public:
		virtual const char* SourceName();
		virtual void Execute();
		void SetFactor(float num);
		Blender();
		
};

class Blur: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Blur();
		
};

class Rotate: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Rotate();
		
};

class Subtract: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Subtract();
		
};

class Mirror: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Mirror();
		
};

class Grayscale: public Filter{
	public:
		virtual const char* SourceName();
		virtual void Execute();
		Grayscale();
		
};


class Color: public Source{
	
	public:	
		int red, green, blue;
		virtual void Update();
		virtual const char* SourceName();
		virtual void Execute();
		Color(int width, int height, int r,  int g ,int b);
		
};

class CheckSum: public Sink{
	
	public:	
		void OutputCheckSum( char* name);
};
