#include "ListaModel.h"


ListaModel::ListaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

ListaModel::~ListaModel()
{
	list.clear();
}

void ListaModel::insereLista(const uint idLista, const uint idCampanha, const uint idCliente, const bool flagLig, const uint tp)
{
	list.append(new ListaVO(idLista, idCampanha, idCliente, flagLig, tp));
}