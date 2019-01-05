#ifndef CLIENTEVO_H
#define CLIENTEVO_H


#include "TelefoneVO.h"

#include <qdatetime.h>
#include <qptrlist.h>


class ClienteVO
{
public:
	ClienteVO (const uint idCliente=0, const uint idSegmento=0, const QString nomeCliente="", const uint idCampanha=0, const QString site="", const QDate dataContato=QDate::QDate(), const QString agente="", const QString supervisor="", const QString solicitacao="", const QDate dataFechamento=QDate::QDate(), const QString categoria="", const QString prePos="", const QString segmento="", const QString regiao="", const QString estado="", const QString obs="", const QString extra1="", const QString extra2="", const QString extra3="", const QString extra4="", const QString extra5="", const QString extra6="", const QString extra="", const QString extra20="", const QString extra21="", const QString extra22="", const QString extra23="", const QString extra24="", const QString extra25="", const QString extra26="", const QString extra27="", const QString extra28="", const QString extra29="")
	{
		setIdCliente (idCliente);
		setIdSegmento (idSegmento);
		setNomeCliente (nomeCliente);
		setIdCampanha (idCampanha);
		setSite (site);
		setDataContato (dataContato);
		setAgente (agente);
		setSupervisor (supervisor);
		setSolicitacao (solicitacao);
		setDataFechamento (dataFechamento);
		setCategoria (categoria);
		setPrePos (prePos);
		setSegmento (segmento);
		setRegiao (regiao);
		setEstado (estado);
		setObs (obs);

		setExtra1 (extra1);
		setExtra2 (extra2);
		setExtra3 (extra3);
		setExtra4 (extra4);
		setExtra5 (extra5);
		setExtra6 (extra6);
		setExtra (extra);

		setExtra20 (extra20);
		setExtra21 (extra21);
		setExtra22 (extra22);
		setExtra23 (extra23);
		setExtra24 (extra24);
		setExtra25 (extra25);
		setExtra26 (extra26);
		setExtra27 (extra27);
		setExtra28 (extra28);
		setExtra29 (extra29);


		
		listaTel.clear();
		listaTel.setAutoDelete(true);
	}

	~ClienteVO()
	{
		listaTel.clear();
	}

	void insereTelefone(const uint idTelefone=0, const uint idCliente=0, const uint ordem=0, const uint telefone=0, const uint ramal=0, const uint ddd=0, const uint ddi=0)
	{
		listaTel.append(new TelefoneVO(idTelefone, idCliente, ordem, telefone, ramal, ddd, ddi));
	}

	void setIdCliente (const uint id) { idCliente = id; }
	void setIdSegmento (const uint id) { idSegmento = id; }
	void setNomeCliente (const QString nome) { nomeCliente = nome; }
	void setIdCampanha (const uint id) { idCampanha = id; }
	void setSite (const QString str) { site = str; }
	void setDataContato (const QDate data) { dataContato = data; }
	void setAgente (const QString str) { agente = str; }
	void setSupervisor (const QString str) { supervisor = str; }
	void setSolicitacao (const QString str) { solicitacao = str; }
	void setDataFechamento (const QDate data) { dataFechamento = data; }
	void setCategoria (const QString str) { categoria = str; }
	void setPrePos (const QString str) { prePos = str; }
	void setSegmento (const QString str) { segmento = str; }
	void setRegiao (const QString str) { regiao = str; }
	void setEstado (const QString str) { estado = str; }
	void setObs (const QString str) { obs = str; }

	void setExtra1 (const QString str) { extra1 = str; }
	void setExtra2 (const QString str) { extra2 = str; }
	void setExtra3 (const QString str) { extra3 = str; }
	void setExtra4 (const QString str) { extra4 = str; }
	void setExtra5 (const QString str) { extra5 = str; }
	void setExtra6 (const QString str) { extra6 = str; }
	void setExtra (const QString str) { extra = str; }

	void setExtra20 (const QString str) { extra20 = str; }
	void setExtra21 (const QString str) { extra21 = str; }
	void setExtra22 (const QString str) { extra22 = str; }
	void setExtra23 (const QString str) { extra23 = str; }
	void setExtra24 (const QString str) { extra24 = str; }
	void setExtra25 (const QString str) { extra25 = str; }
	void setExtra26 (const QString str) { extra26 = str; }
	void setExtra27 (const QString str) { extra27 = str; }
	void setExtra28 (const QString str) { extra28 = str; }
	void setExtra29 (const QString str) { extra29 = str; }

	uint getIdCliente () { return idCliente; }
	uint getIdSegmento () { return idSegmento; }
	QString getNomeCliente () { return nomeCliente; }
	uint getIdCampanha () { return idCampanha; }
	QString getSite () { return site; }
	QDate getDataContato () { return dataContato; }
	QString getAgente () { return agente; }
	QString getSupervisor () { return supervisor; }
	QString getSolicitacao () { return solicitacao; }
	QDate getDataFechamento () { return dataFechamento; }
	QString getCategoria () { return categoria; }
	QString getPrePos () { return prePos; }
	QString getSegmento () { return segmento; }
	QString getRegiao () { return regiao; }
	QString getEstado () { return estado; }
	QString getObs () { return obs; }

	QString getExtra1 () { return extra1; }
	QString getExtra2 () { return extra2; }
	QString getExtra3 () { return extra3; }
	QString getExtra4 () { return extra4; }
	QString getExtra5 () { return extra5; }
	QString getExtra6 () { return extra6; }
	QString getExtra () { return extra; }

	QString getExtra20 () { return extra20; }
	QString getExtra21 () { return extra21; }
	QString getExtra22 () { return extra22; }
	QString getExtra23 () { return extra23; }
	QString getExtra24 () { return extra24; }
	QString getExtra25 () { return extra25; }
	QString getExtra26 () { return extra26; }
	QString getExtra27 () { return extra27; }
	QString getExtra28 () { return extra28; }
	QString getExtra29 () { return extra29; }
	
private:
	uint idCliente;
	uint idSegmento;
	QString nomeCliente;
	uint idCampanha;
	QString site;
	QDate dataContato;
	QString agente;
	QString supervisor;
	QString solicitacao;
	QDate dataFechamento;
	QString categoria;
	QString prePos;
	QString segmento;
	QString regiao;
	QString estado;
	QString obs;

	QString extra1;
	QString extra2;
	QString extra3;
	QString extra4;
	QString extra5;
	QString extra6;
	QString extra;

	QString extra20;
	QString extra21;
	QString extra22;
	QString extra23;
	QString extra24;
	QString extra25;
	QString extra26;
	QString extra27;
	QString extra28;
	QString extra29;

public:
	QPtrList<TelefoneVO> listaTel;
};


class EstadoVO
{
public:
	EstadoVO (const QString sigla="", const QString nome="")
	{
		setSigla (sigla);
		setNome (nome);
	}

	void setSigla (const QString sig) {sigla = sig;}
	void setNome (const QString nm) {nome = nm;}

	QString getSigla () {return sigla;}
	QString getNome () {return nome;}

private:
	QString sigla, nome;
};

#endif 	// CLIENTEVO_H