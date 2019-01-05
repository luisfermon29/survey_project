#ifndef CAMPANHAPSO_H
#define CAMPANHAPSO_H

#include "CampanhaModel.h"

#include <qsqlcursor.h>


class CampanhaPSO
{
public:
	CampanhaPSO(QSqlDatabase * sql=NULL);

	bool lerCampanha(CampanhaModel * modelo);
	bool lerCampanhaId(CampanhaVO * campanha, uint idCampanha);
	void lerCampanha(QSqlCursor * cursor, CampanhaVO * Campanha);

	bool grvCampanha(CampanhaModel * modelo);
	bool grvCampanha(CampanhaVO * campanha, QSqlDatabase * sql=NULL);

	bool updCampanha(CampanhaModel * modelo);
	bool updCampanha(CampanhaVO * campanha, QSqlDatabase * sql=NULL);

	bool delCampanha(CampanhaModel * modelo);
	bool delCampanha(CampanhaVO * campanha, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
};

#endif 	// CAMPANHAPSO_H