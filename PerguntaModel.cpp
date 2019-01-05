#include "PerguntaModel.h"


PerguntaModel::PerguntaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

PerguntaModel::~PerguntaModel()
{
	list.clear();
}

void PerguntaModel::inserePergunta (const uint idPergunta, const uint idBloco, const uint tipo, const QString textoPergunta, const QString textoExplicativo, const bool textoAntes, const uint ordem)
{
	list.append(new PerguntaVO(idPergunta, idBloco, tipo, textoPergunta, textoExplicativo, textoAntes, ordem));
}