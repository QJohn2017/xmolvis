
#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] = "16.08";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 3;
	static const long BUILD = 1;
	static const long REVISION = 2;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 24;
	#define RC_FILEVERSION 0,3,1,2
	#define RC_FILEVERSION_STRING "0, 3, 1, 2\24"
	static const char FULLVERSION_STRING [] = "0.3.1.2";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 24;
	

}
#endif //VERSION_H

