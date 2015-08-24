/* **************************
   Header file for background
   ************************** */

#ifndef background_h
#define background_h


struct Background{
	Bitmap bkground;
	int x, y;
};

void InitializeBackground(Background *b);
void DrawBackground(Background *b);

#endif