#ifndef TIPOCAMPANHAPSO_H
#define TIPOCAMPANHAPSO_H

#include "TipoCampanhaModel.h"

#include <qsqlcursor.h>


class TipoCampanhaPSO
{
public:
	TipoCampanhaPSO(QSqlDatabase * sql=NULL);

	bool lerTipoCampanha(TipoCampanhaModel * modelo);


	QSqlDatabase * db;
};

#endif 	// TIPOCAMPANHAPSO_H