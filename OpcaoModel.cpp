#include "OpcaoModel.h"


OpcaoModel::OpcaoModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

OpcaoModel::~OpcaoModel()
{
	list.clear();
}

void OpcaoModel::insereOpcao(const uint idOpcao, const uint idBlocoOpcao, const uint tipo, const uint ordem, const QString tag, const QString textoExplicativo, const QString texto)
{
	list.append(new OpcaoVO(idOpcao, idBlocoOpcao, tipo, ordem, tag, textoExplicativo, texto));
}