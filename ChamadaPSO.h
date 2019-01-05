#ifndef CHAMADAPSO_H
#define CHAMADAPSO_H

#include "ChamadaModel.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class ChamadaPSO
{
public:
	ChamadaPSO(QSqlDatabase * sql=NULL);

	bool lerChamadaId(ChamadaVO * chamada, uint idChamada);
	bool lerChamadaIdCliente(ChamadaModel * modelo, uint idCliente);
	void lerChamada(QSqlCursor * cursor, ChamadaVO * chamada);

	bool grvChamada(ChamadaModel * modelo);
	bool grvChamada(ChamadaVO * chamada, QSqlDatabase * sql=NULL);

	bool updChamada(ChamadaModel * modelo);
	bool updChamada(ChamadaVO * chamada, QSqlDatabase * sql=NULL);

	bool delChamada(ChamadaModel * modelo);
	bool delChamada(ChamadaVO * chamada, QSqlDatabase * sql=NULL);

	int verificaChamadaIdCliente(uint idCliente);

	bool lerFinalizacaoChamada(FinalizacaoChamadaModel * modelo);
	bool lerExcecaoChamada(ExcecaoChamadaModel * modelo);
	bool lerExcecaoChamadaIdCampanha(ExcecaoChamadaModel * modelo, uint idCampanha);

	QSqlDatabase * db;
};

#endif 	// CHAMADAPSO_H