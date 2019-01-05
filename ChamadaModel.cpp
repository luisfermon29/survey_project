#include "ChamadaModel.h"


ChamadaModel::ChamadaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

ChamadaModel::~ChamadaModel()
{
	list.clear();
}

void ChamadaModel::insereChamada(const uint idChamada, const int idFinalizacao, const int idExcecao, const uint idCampanha, const uint idCliente, const uint telefone, const uint ramal, const QDateTime data, const uint idLogin, const uint duracao)
{
	list.append(new ChamadaVO(idChamada, idFinalizacao, idExcecao, idCampanha, idCliente, telefone, ramal, data, idLogin, duracao));
}

///////////////////////////

FinalizacaoChamadaModel::FinalizacaoChamadaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

FinalizacaoChamadaModel::~FinalizacaoChamadaModel()
{
	list.clear();
}

void FinalizacaoChamadaModel::insereFinalizacaoChamada(const int idFinalizacao, const uint idCampanha, const QString nome, const QString descricao)
{
	list.append(new FinalizacaoChamadaVO(idFinalizacao, idCampanha, nome, descricao));
}

///////////////////////////

ExcecaoChamadaModel::ExcecaoChamadaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

ExcecaoChamadaModel::~ExcecaoChamadaModel()
{
	list.clear();
}

void ExcecaoChamadaModel::insereExcecaoChamada(const int idExcecao, const uint idCampanha, const QString nome, const QString descricao, const uint qtLimiteChamadas)
{
	list.append(new ExcecaoChamadaVO(idExcecao, idCampanha, nome, descricao, qtLimiteChamadas));
}