#ifndef CAMPANHAMODEL_H
#define CAMPANHAMODEL_H


#include "CampanhaVO.h"

#include <qsqldatabase.h>


class CampanhaModel
{
public:
    CampanhaModel(QSqlDatabase *sql=NULL);
    ~CampanhaModel();

	void insereCampanha(const uint idCampanha=0, const uint idTipoCampanha=0, const QString descricao="", const QString caminhoScript="", const QDate dataInicio=QDate::QDate(), const QDate dataTermino=QDate::QDate());

	QSqlDatabase * db;
	QPtrList<CampanhaVO> list;
};

#endif 	// CAMPANHAMODEL_H