#ifndef BLOCOOPCAOMODEL_H
#define BLOCOOPCAOMODEL_H


#include "BlocoOpcaoVO.h"

#include <qsqldatabase.h>


class BlocoOpcaoModel
{
public:
    BlocoOpcaoModel(QSqlDatabase *sql=NULL);
    ~BlocoOpcaoModel();

	void insereBlocoOpcao (const uint idBlocoOpcao=0, const uint idPergunta=0, const QString nome="");

	QSqlDatabase *db;
	QPtrList<BlocoOpcaoVO> list;
};

#endif 	// BLOCOOPCAOMODEL_H