#include "ClienteModel.h"


ClienteModel::ClienteModel(QSqlDatabase *sql)
{
	list.clear();
	listEstado.clear();
	list.setAutoDelete(TRUE);
	listEstado.setAutoDelete(TRUE);

	db = sql;
}

ClienteModel::~ClienteModel()
{
	list.clear();
	listEstado.clear();
}

void ClienteModel::insereCliente(const uint idCliente, const uint idSegmento, const QString nomeCliente, const uint idCampanha, const QString site, const QDate dataContato, const QString agente, const QString supervisor, const QString solicitacao, const QDate dataFechamento, const QString categoria, const QString prePos, const QString segmento, const QString regiao, const QString estado, const QString obs, const QString extra1, const QString extra2, const QString extra3, const QString extra4, const QString extra5, const QString extra6, const QString extra, const QString extra20, const QString extra21, const QString extra22, const QString extra23, const QString extra24, const QString extra25, const QString extra26, const QString extra27, const QString extra28, const QString extra29)
{
	list.append(new ClienteVO(idCliente, idSegmento, nomeCliente, idCampanha, site, dataContato, agente, supervisor, solicitacao, dataFechamento, categoria, prePos, segmento, regiao, estado, obs, extra1, extra2, extra3, extra4, extra5, extra6, extra, extra20, extra21, extra22, extra23, extra24, extra25, extra26, extra27, extra28, extra29));
}