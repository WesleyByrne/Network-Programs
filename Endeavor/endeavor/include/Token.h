#if !defined ENDEAVOR_TOKEN
#define ENDEAVOR_TOKEN

#include "wx/wx.h"

#include "EndeavorHeader.h"

class Token
{
   private:
      EndeavorTokenType token_type;
      wxBitmap* token_img;

   public:
      Token(EndeavorTokenType token_type, wxBitmap* img);
      virtual ~Token();

      EndeavorTokenType getTokenType();
      wxBitmap* getTokenImage();
};

#endif
