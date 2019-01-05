#ifndef PERFILMODEL_H
#define PERFILMODEL_H


#include "PerfilVO.h"

#include <qsqldatabase.h>


class PerfilModel
{
public:
    PerfilModel(QSqlDatabase *sql=NULL);
    ~PerfilModel();

	void inserePerfil(const uint idPerfil=0, const QString nome="");

	QSqlDatabase * db;
	QPtrList<PerfilVO> list;
};

#endif 	// PERFILMODEL_H