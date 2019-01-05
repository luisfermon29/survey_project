#ifndef RECHAMADAPSO_H
#define RECHAMADAPSO_H


#include "RechamadaVO.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class RechamadaPSO
{
public:
	RechamadaPSO(QSqlDatabase * sql=NULL);

	bool lerRechamadaId(RechamadaVO * rechamada, uint idRechamada);
	bool lerRechamadaIdLogin(RechamadaVO * rechamada, uint idLogin);
	void lerRechamada(QSqlCursor * cursor, RechamadaVO * rechamada);
	void lerRechamada(QSqlQuery * qry, RechamadaVO * rechamada);

	bool grvRechamada(RechamadaVO * rechamada, QSqlDatabase * sql=NULL);

	bool updRechamada(RechamadaVO * rechamada, QSqlDatabase * sql=NULL);

	bool delRechamada(RechamadaVO * rechamada, QSqlDatabase * sql=NULL);

	bool updRechamadaIdClienteOn(uint idCliente, QSqlDatabase * sql=NULL);

	bool lerRetornoIdCliente(RechamadaVO * rechamada);
	void lerRetorno(QSqlQuery * qry, RechamadaVO * rechamada);

	QSqlDatabase * db;
};

#endif 	// RECHAMADAPSO_H