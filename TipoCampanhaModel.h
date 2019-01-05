#ifndef TIPOCAMPANHAMODEL_H
#define TIPOCAMPANHAMODEL_H


#include "TipoCampanhaVO.h"

#include <qsqldatabase.h>


class TipoCampanhaModel
{
public:
    TipoCampanhaModel(QSqlDatabase *sql=NULL);
    ~TipoCampanhaModel();

	void insereTipoCampanha(const uint idTipoCampanha=0, const QString nome="", const QString descricao="");

	QSqlDatabase *db;
	QPtrList<TipoCampanhaVO> list;
};

#endif 	// TIPOCAMPANHAMODEL_H