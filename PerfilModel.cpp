#include "PerfilModel.h"


PerfilModel::PerfilModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

PerfilModel::~PerfilModel()
{
	list.clear();
}

void PerfilModel::inserePerfil(const uint idPerfil, const QString nome)
{
	list.append(new PerfilVO(idPerfil, nome));
}