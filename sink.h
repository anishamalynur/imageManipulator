#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <logging.h>

class Image;

class Sink{
	protected:
		const Image* im1;
		const Image* im2;
		
	public:
		Sink();
		const Image* getInput();
		const Image* getInput2();
		void SetInput(Image* theImage);
		void SetInput2( Image* theImage);

		bool isInput;
		bool isInput2;

		
};



#endif
