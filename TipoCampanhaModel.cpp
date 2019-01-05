#include "TipoCampanhaModel.h"


TipoCampanhaModel::TipoCampanhaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

TipoCampanhaModel::~TipoCampanhaModel()
{
	list.clear();
}

void TipoCampanhaModel::insereTipoCampanha(const uint idTipoCampanha, const QString nome, const QString descricao)
{
	list.append(new TipoCampanhaVO(idTipoCampanha, nome, descricao));
}