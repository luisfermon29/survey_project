#include "CampanhaModel.h"


CampanhaModel::CampanhaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

CampanhaModel::~CampanhaModel()
{
	list.clear();
}

void CampanhaModel::insereCampanha(const uint idCampanha, const uint idTipoCampanha, const QString descricao, const QString caminhoScript, const QDate dataInicio, const QDate dataTermino)
{
	list.append(new CampanhaVO(idCampanha, idTipoCampanha, descricao, caminhoScript, dataInicio, dataTermino));
}