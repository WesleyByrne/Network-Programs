#if !defined IMAGE_LOADER
#define IMAGE_LOADER

class wxBitmap;

class ImageLoader
{
	private:
		ImageLoader() {};
		
	public:
		virtual ~ImageLoader() {};
		static ImageLoader* getImageLoader();
		wxBitmap* loadImageRGBA(const char* id);
};

#endif 
