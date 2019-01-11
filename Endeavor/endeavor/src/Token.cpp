#include "Token.h"

Token::Token(EndeavorTokenType type, wxBitmap* img)
{
   token_type = type;
   token_img = img;
}

Token::~Token()
{
	//delete token_img;
}

EndeavorTokenType Token::getTokenType()
{
   return token_type;
}

wxBitmap* Token::getTokenImage()
{
   return token_img;
}
