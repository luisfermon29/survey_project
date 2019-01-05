#ifndef SK_H
#define SK_H


//#include <qstring.h>


class softKey
{
public:
	softKey();
	~softKey();

	int registraSK (const char fileName[] = "C:\\tsx.lic");
	int verificaSK (const char fileName[] = "C:\\tsx.lic");
};

#endif // SK_H