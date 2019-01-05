#ifndef CHAMADAMODEL_H
#define CHAMADAMODEL_H


#include "ChamadaVO.h"

#include <qsqldatabase.h>


class ChamadaModel;
class FinalizacaoChamadaModel;
class ExcecaoChamadaModel;


class ChamadaModel
{
public:
    ChamadaModel(QSqlDatabase *sql=NULL);
    ~ChamadaModel();

	void insereChamada(const uint idChamada=0, const int idFinalizacao=-1, const int idExcecao=-1, const uint idCampanha=0, const uint idCliente=0, const uint telefone=0, const uint ramal=0, const QDateTime data=QDateTime::QDateTime(), const uint idLogin=0, const uint duracao=0);

	QSqlDatabase *db;
	QPtrList<ChamadaVO> list;
};


class FinalizacaoChamadaModel
{
public:
    FinalizacaoChamadaModel(QSqlDatabase *sql=NULL);
    ~FinalizacaoChamadaModel();

	void insereFinalizacaoChamada(const int idFinalizacao=-1, const uint idCampanha=0, const QString nome="", const QString descricao="");

	QSqlDatabase *db;
	QPtrList<FinalizacaoChamadaVO> list;
};


class ExcecaoChamadaModel
{
public:
    ExcecaoChamadaModel(QSqlDatabase *sql=NULL);
    ~ExcecaoChamadaModel();

	void insereExcecaoChamada(const int idExcecao=-1, const uint idCampanha=0, const QString nome="", const QString descricao="", const uint qtLimiteChamadas=0);

	QSqlDatabase *db;
	QPtrList<ExcecaoChamadaVO> list;
};

#endif 	// CHAMADAMODEL_H