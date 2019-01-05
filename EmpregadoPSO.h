#ifndef EMPREGADOPSO_H
#define EMPREGADOPSO_H

#include "EmpregadoModel.h"
#include "LoginPSO.h"

#include <qsqlcursor.h>


class EmpregadoPSO
{
public:
	EmpregadoPSO(QSqlDatabase * sql=NULL);
	~EmpregadoPSO();

	bool lerEmpregado(EmpregadoModel * modelo, bool lerLogins=true);
	bool lerEmpregadoId(EmpregadoVO * empregado, uint idEmpregado, bool lerLogins=true);
	bool lerEmpregadoNome(EmpregadoModel * modelo, QString nome, bool lerLogins=true);
	bool lerEmpregadoMatricula(EmpregadoModel * modelo, QString matricula, bool lerLogins=true);
	void lerEmpregado(QSqlCursor * cursor, EmpregadoVO * Empregado);

	bool grvEmpregado(EmpregadoModel * modelo, bool grvLogins);
	bool grvEmpregado(EmpregadoVO * empregado, bool grvLogins, QSqlDatabase * sql=NULL);

	bool updEmpregado(EmpregadoModel * modelo, bool updLogins);
	bool updEmpregado(EmpregadoVO * empregado, bool updLogins, QSqlDatabase * sql=NULL);

	bool delEmpregado(EmpregadoModel * modelo, bool delLogins=true);
	bool delEmpregado(EmpregadoVO * empregado, bool delLogins=true, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
	LoginPSO * loginPso;
};

#endif 	// EMPREGADOPSO_H