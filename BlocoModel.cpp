#include "BlocoModel.h"


BlocoModel::BlocoModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

BlocoModel::~BlocoModel()
{
	list.clear();
}

void BlocoModel::insereBloco (const uint idBloco, const QString nome, const QString descricao, const QString tipo)
{
	list.append(new BlocoVO(idBloco, nome, descricao, tipo));
}