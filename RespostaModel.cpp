#include "RespostaModel.h"


RespostaModel::RespostaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

RespostaModel::~RespostaModel()
{
	list.clear();
}

void RespostaModel::insereResposta(const uint idCliente, const uint idOpcao, const uint idOpcaoRelacionada, const QString tagSelecionada, const QString tagRelacionada, const QString texto)
{
	list.append(new RespostaVO(idCliente, idOpcao, idOpcaoRelacionada, tagSelecionada, tagRelacionada, texto));
}