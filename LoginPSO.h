#ifndef LOGINPSO_H
#define LOGINPSO_H

#include "LoginModel.h"
#include "EmpregadoModel.h"

#include <qsqlcursor.h>


class LoginPSO
{
public:
	LoginPSO(QSqlDatabase * sql=NULL);

	bool lerLoginId(LoginVO * login, uint idLogin);
	bool lerLoginIdEmpregado(LoginModel * modelo, uint idEmpregado);
	bool lerLoginIdEmpregado(EmpregadoVO * empregado, uint idEmpregado);
	bool lerLoginUsername(LoginVO * login, QString nome, QString senha);
	void lerLogin(QSqlCursor * cursor, LoginVO * login);

	bool grvLogin(LoginModel * modelo);
	bool grvLogin(EmpregadoVO * empregado);
	bool grvLogin(LoginVO * login, QSqlDatabase * sql=NULL);

	bool updLogin(LoginModel * modelo);
	bool updLogin(EmpregadoVO * empregado);
	bool updLogin(LoginVO * login, QSqlDatabase * sql=NULL);

	bool delLogin(LoginModel * modelo);
	bool delLogin(EmpregadoVO * empregado);
	bool delLogin(LoginVO * login, QSqlDatabase * sql=NULL);
	bool delLoginIdEmpregado(uint idEmpregado, QSqlDatabase * sql=NULL);

	int verificaLogin(QString login);
	bool resetLogin(QString login);

	QSqlDatabase * db;
};

#endif 	// LOGINPSO_H