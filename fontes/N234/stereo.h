
#ifndef stereo_h
#define stereo_h

#include "gl.h"
#include "n234.h"

class Stereo{
	private:
		GLdouble leftL,rightL,leftR,rightR,top,bottom;
		GLdouble upx,upy,upz;
		GLdouble eyexL,eyeyL,eyezL,centerxL,centeryL,centerzL;
		GLdouble eyexR,eyeyR,eyezR,centerxR,centeryR,centerzR;
		CAMERA *camera;
	public:

		Stereo(CAMERA *camera);

		void viewPre(void);

		/** Define a visualiza��o esquerda */
		void viewLeft(void);

		/** Define a visualiza��o direita */
		void viewRight(void);

		void viewPost(void);
};

#endif
