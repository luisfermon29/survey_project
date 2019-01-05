#ifndef LOGINMODEL_H
#define LOGINMODEL_H


#include "LoginVO.h"

#include <qsqldatabase.h>


class LoginModel
{
public:
    LoginModel(QSqlDatabase *sql=NULL);
    ~LoginModel();

	void insereLogin(const uint idLogin=0, const uint idEmpregado=0, const uint perfil=0, const QString login="", const QString senha="", const uint status=0);

	QSqlDatabase * db;
	QPtrList<LoginVO> list;
};

#endif 	// LOGINMODEL_H