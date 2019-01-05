#ifndef OPCAOVO_H
#define OPCAOVO_H


#include "CondicaoVO.h"

#include <qptrlist.h>


class OpcaoBaseVO
{
public:
	OpcaoBaseVO (const uint idOpcao=0, const uint idBlocoOpcao=0, const uint tipo=0, const uint ordem=0, const QString tag="", const QString textoExplicativo="")
	{
		setIdOpcao (idOpcao);
		setIdBlocoOpcao (idBlocoOpcao);
		setTipo(tipo);
		setOrdem (ordem);
		setTag (tag);
		setTextoExplicativo (textoExplicativo);

		listaCondicoes.clear();
		listaCondicoes.setAutoDelete(true);
	}

	~OpcaoBaseVO()
	{
		listaCondicoes.clear();
	}

	void insereCondicao(const uint idCondicao=0, const uint idOpcao=0, const uint idProximaPergunta=0, const uint tipo=0)
	{
		listaCondicoes.append(new CondicaoVO(idCondicao, idOpcao, idProximaPergunta, tipo));
	}

	void setIdOpcao (const uint id) { idOpcao = id; }
	void setIdBlocoOpcao (const uint id) { idBlocoOpcao = id; }
	void setTipo (const uint id) { tipo = id; }
	void setOrdem (const uint id) { ordem = id; }
	void setTag (const QString str) { tag = str; }
	void setTextoExplicativo (const QString str) { textoExplicativo = str; }

	uint getIdOpcao () { return idOpcao; }
	uint getIdBlocoOpcao () { return idBlocoOpcao; }
	uint getTipo () { return tipo; }
	uint getOrdem () { return ordem; }
	QString getTag () { return tag; }
	QString getTextoExplicativo () { return textoExplicativo; }

private:
	uint idOpcao;
	uint idBlocoOpcao;
	uint tipo;
	uint ordem;
	QString tag;
	QString textoExplicativo;

public:
	QPtrList<CondicaoVO> listaCondicoes;
};


class OpcaoVO: public OpcaoBaseVO
{
public:
	OpcaoVO (const uint idOpcao=0, const uint idBlocoOpcao=0, const uint tipo=0, const uint ordem=0, const QString tag="", const QString textoExplicativo="", const QString texto="")
		:OpcaoBaseVO(idOpcao, idBlocoOpcao, tipo, ordem, tag, textoExplicativo)
	{
		setTexto(texto);
	}

	void setTexto (const QString str) { texto = str; }

	QString getTexto () { return texto; }

private:
	QString texto;
};

#endif 	// OPCAOVO_H