#include <source.h>
#include <sink.h>

//class Source;
//class Sink;

class Filter: public Source, public Sink{

public:
	virtual void Update();

};


