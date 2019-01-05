#include "LoginModel.h"


LoginModel::LoginModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

LoginModel::~LoginModel()
{
	list.clear();
}

void LoginModel::insereLogin(const uint idLogin, const uint idEmpregado, const uint perfil, const QString login, const QString senha, const uint status)
{
	list.append(new LoginVO(idLogin, idEmpregado, perfil, login, senha, status));
}