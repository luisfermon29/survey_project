#ifndef BLOCOMODEL_H
#define BLOCOMODEL_H


#include "BlocoVO.h"

#include <qsqldatabase.h>


class BlocoModel
{
public:
    BlocoModel(QSqlDatabase *sql=NULL);
    ~BlocoModel();

	void insereBloco (const uint idBloco=0, const QString nome="", const QString descricao="", const QString tipo="");

	QSqlDatabase *db;
	QPtrList<BlocoVO> list;
};

#endif 	// BLOCOMODEL_H