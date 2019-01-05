#include "BlocoOpcaoModel.h"


BlocoOpcaoModel::BlocoOpcaoModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

BlocoOpcaoModel::~BlocoOpcaoModel()
{
	list.clear();
}

void BlocoOpcaoModel::insereBlocoOpcao (const uint idBlocoOpcao, const uint idPergunta, const QString nome)
{
	list.append(new BlocoOpcaoVO(idBlocoOpcao, idPergunta, nome));
}