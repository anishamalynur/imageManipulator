#ifndef IMAGE
#define IMAGE

class Source;

struct Pixel;

struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};


class Image
{
	private:
		Pixel* pixList;
		int width;
		int height;
	public:
		void ResetSize(int width, int height);
		void setFilter(Source* aFilter);
		
		void Update() const;
		mutable bool isUpdated;
		Source* theFilter;
		
		Image(void);
		Image(int w, int h, Pixel* pixL);
		Image(Image &im);
		Pixel* getPix() const;
		
		int getWidth() const;
		int getHeight() const;
		~Image();
		
};

#endif
