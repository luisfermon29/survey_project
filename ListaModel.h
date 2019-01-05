#ifndef LISTAMODEL_H
#define LISTAMODEL_H


#include "ListaVO.h"

#include <qsqldatabase.h>


class ListaModel
{
public:
    ListaModel(QSqlDatabase *sql=NULL);
    ~ListaModel();

	void insereLista(const uint idLista=0, const uint idCampanha=0, const uint idCliente=0, const bool flagLig=false, const uint tp=0);

	QSqlDatabase *db;
	QPtrList<ListaVO> list;
};

#endif 	// LISTAMODEL_H