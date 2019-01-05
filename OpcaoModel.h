#ifndef OPCAOMODEL_H
#define OPCAOMODEL_H


#include "OpcaoVO.h"

#include <qsqldatabase.h>


class OpcaoModel
{
public:
    OpcaoModel(QSqlDatabase *sql=NULL);
    ~OpcaoModel();

	void insereOpcao (const uint idOpcao=0, const uint idBlocoOpcao=0, const uint tipo=0, const uint ordem=0, const QString tag="", const QString textoExplicativo="", const QString texto="");

	QSqlDatabase *db;
	QPtrList<OpcaoVO> list;
};

#endif 	// OPCAOMODEL_H