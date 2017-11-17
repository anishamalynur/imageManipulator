#ifndef PNMwriter_H
#define PNMwriter_H

#include <sink.h>

class PNMwriter: public Sink{

	public:
		void Write(char* filename);

};


#endif
