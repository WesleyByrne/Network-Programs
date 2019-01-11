#include "ImageLoader.h"
#include "wx/wx.h"
#include <windows.h>

ImageLoader* ImageLoader::getImageLoader()
{
   static ImageLoader image_loader;
   return &image_loader;
}

wxBitmap* ImageLoader::loadImageRGBA(const char* img_id)
{
    HINSTANCE hInst = GetModuleHandle(0);
	
    HANDLE hBitMap = LoadImageA(hInst, img_id, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    BITMAP bitmap;
    GetObject(hBitMap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
	//std::cout << width << std::endl;
    int height = bitmap.bmHeight;
	//std::cout << height << std::endl;
    int depth = bitmap.bmBitsPixel;
	//std::cout << depth << std::endl;
    int size = height*width*depth/8;  //depth is 32, so need to remove alpha channel information

    byte* lpBits = new byte[size];
    GetBitmapBits((HBITMAP) hBitMap, size, lpBits);

    byte* rgb = new byte[(size*3)/4];
	//separate alpha channel array
	byte* a = new byte[size/4];
	
	//std::string id_str(img_id);
	
	bool opaque = true;
    for (int i = 0; i < size; i += 4)
    {
		byte alpha = lpBits[i+3];
		if (alpha > 0)
		{
			opaque = false;
			break;
		}
    }

    int count = 0;
	int alpha_count = 0;
	
	if (!opaque)
	{
		for (int i = 0; i < size; i += 4)
		{
			byte alpha = lpBits[i+3];
			
			byte red = lpBits[i+2];
			byte green = lpBits[i+1];
			byte blue = lpBits[i+0];
			
			a[alpha_count] = alpha;
			
			rgb[count] = red;
			rgb[count + 1] = green;
			rgb[count + 2] = blue;
			
			count += 3;
			alpha_count += 1;
		}
	}
	
	else
	{
		for (int i = 0; i < size; i += 4)
		{
			byte alpha = 255;

			byte red = lpBits[i+2];
			byte green = lpBits[i+1];
			byte blue = lpBits[i+0];
			
			a[alpha_count] = alpha;
			
			rgb[count] = red;
			rgb[count + 1] = green;
			rgb[count + 2] = blue;
			
			count += 3;
			alpha_count += 1;
		}
	}
	
    delete[] lpBits;

	wxImage wximage(width, height, (unsigned char*) rgb, (unsigned char*) a, true);
	wxBitmap* wxbitmap = new wxBitmap(wximage, 32);  //32 bit depth seems correct for alpha channel inclusion

	return wxbitmap;
}
