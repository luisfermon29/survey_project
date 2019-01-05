#ifndef CHAMADAVO_H
#define CHAMADAVO_H

#include <qstring.h>
#include <qdatetime.h>

class ChamadaVO;
class FinalizacaoChamadaVO;
class ExcecaoChamadaVO;

class ChamadaVO
{
public:
	ChamadaVO (const uint idChamada=0, const int idFinalizacao=-1, const int idExcecao=-1, const uint idCampanha=0, const uint idCliente=0, const uint telefone=0, const uint ramal=0, const QDateTime data=QDateTime::QDateTime(), const uint idLogin=0, const uint duracao=0)
	{
		setIdChamada (idChamada);
		setIdFinalizacao (idFinalizacao);
		setIdExcecao (idExcecao);
		setIdCampanha (idCampanha);
		setIdCliente (idCliente);
		setTelefone (telefone);
		setRamal (ramal);
		setData (data);
		setIdLogin (idLogin);
		setDuracao (duracao);
	}

	void setIdChamada (const uint id) { idChamada = id; }
	void setIdFinalizacao (const int id) { idFinalizacao = id; }
	void setIdExcecao (const int id) { idExcecao = id; }
	void setIdCampanha (const uint id) { idCampanha= id; }
	void setIdCliente (const uint id) { idCliente = id; }
	void setTelefone (const uint id) { telefone = id; }
	void setRamal (const uint id) { ramal = id; }
	void setData (const QDateTime dt) { data = dt; }
	void setIdLogin (const uint id) { idLogin = id; }
	void setDuracao (const uint id) { duracao = id; }

	uint getIdChamada () { return idChamada; }
	int getIdFinalizacao () { return idFinalizacao; }
	int getIdExcecao () { return idExcecao; }
	uint getIdCampanha () { return idCampanha; }
	uint getIdCliente () { return idCliente; }
	uint getTelefone () { return telefone; }
	uint getRamal () { return ramal; }
	QDateTime getData () { return data; }
	uint getIdLogin () { return idLogin; }
	uint getDuracao () { return duracao; }

private:
	uint idChamada;
	int idFinalizacao;
	int idExcecao;
	uint idCampanha;
	uint idCliente;
	uint telefone;
	uint ramal;
	QDateTime data;
	uint idLogin;
	uint duracao;
};


class FinalizacaoChamadaVO
{
public:
	FinalizacaoChamadaVO (const int idFinalizacao=-1, const uint idCampanha=0, const QString nome="", const QString descricao="")
	{
		setIdFinalizacao (idFinalizacao);
		setIdCampanha (idCampanha);
		setNome (nome);
		setDescricao (descricao);
	}

	void setIdFinalizacao (const int id) { idFinalizacao = id; }
	void setIdCampanha (const uint id) { idCampanha = id; }
	void setNome (const QString str) { nome = str; }
	void setDescricao (const QString str) { descricao = str; }

	int getIdFinalizacao () { return idFinalizacao; }
	uint getIdCampanha () { return idCampanha; }
	QString getNome () { return nome; }
	QString getDescricao () { return descricao; }

private:
	int idFinalizacao;
	uint idCampanha;
	QString nome;
	QString descricao;
};


class ExcecaoChamadaVO
{
public:
	ExcecaoChamadaVO (const int idExcecao=-1, const uint idCampanha=0, const QString nome="", const QString descricao="", const uint qtLimiteChamadas=0)
	{
		setIdExcecao (idExcecao);
		setIdCampanha (idCampanha);
		setNome (nome);
		setDescricao (descricao);
		setQtLimiteChamadas (qtLimiteChamadas);
	}

	void setIdExcecao (const int id) { idExcecao = id; }
	void setIdCampanha (const uint id) { idCampanha = id; }
	void setNome (const QString str) { nome = str; }
	void setDescricao (const QString str) { descricao = str; }
	void setQtLimiteChamadas (const uint id) { qtLimiteChamadas = id; }

	int getIdExcecao () { return idExcecao; }
	uint getIdCampanha () { return idCampanha; }
	QString getNome () { return nome; }
	QString getDescricao () { return descricao; }
	uint getQtLimiteChamadas () { return qtLimiteChamadas; }

private:
	int idExcecao;
	uint idCampanha;
	QString nome;
	QString descricao;
	uint qtLimiteChamadas;
};

#endif 	// CHAMADAVO_H