#ifndef LISTAPSO_H
#define LISTAPSO_H

#include "ListaModel.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class ListaPSO
{
public:
	ListaPSO(QSqlDatabase * sql=NULL);

	bool lerListaId(ListaVO * lista, uint idLista);
	bool lerListaIdCliente(ListaVO * lista, uint idCliente);
	bool lerListaIdCampanha(ListaVO * lista, uint idCampanha, QString uf, uint tp);
	void lerLista(QSqlCursor * cursor, ListaVO * lista);

	bool grvLista(ListaModel * modelo);
	bool grvLista(ListaVO * lista, QSqlDatabase * sql=NULL);

	bool updLista(ListaModel * modelo);
	bool updLista(ListaVO * lista, QSqlDatabase * sql=NULL);

	bool delLista(ListaModel * modelo);
	bool delLista(ListaVO * lista, QSqlDatabase * sql=NULL);
	bool delListaIdCliente(uint idCliente, QSqlDatabase * sql);
	bool delListaIdCampanha(uint idCampanha, QSqlDatabase * sql);
	bool delListaIdCampanhaSite(uint idCampanha, QString site, QSqlDatabase * sql);

	QSqlDatabase * db;
};

#endif 	// LISTAPSO_H