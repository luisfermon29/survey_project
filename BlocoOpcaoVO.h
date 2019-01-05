#ifndef BLOCOOPCAOVO_H
#define BLOCOOPCAOVO_H


#include "OpcaoVO.h"

#include <qptrlist.h>


class BlocoOpcaoVO
{
public:
	BlocoOpcaoVO (const uint idBlocoOpcao=0, const uint idPergunta=0, const QString nome="")
	{
		setIdBlocoOpcao (idBlocoOpcao);
		setIdPergunta (idPergunta);
		setNome (nome);

		listaOpcoes.clear();
		listaOpcoes.setAutoDelete(true);
	}

	~BlocoOpcaoVO()
	{
		listaOpcoes.clear();
	}

	void insereOpcao(const uint idOpcao=0, const uint idBlocoOpcao=0, const uint tipo=0, const uint ordem=0, const QString tag="", const QString textoExplicativo="")
	{
		listaOpcoes.append(new OpcaoVO(idOpcao, idBlocoOpcao, tipo, ordem, tag, textoExplicativo));
	}

	void setIdBlocoOpcao (const uint id) { idBlocoOpcao = id; }
	void setIdPergunta (const uint id) { idPergunta = id; }
	void setNome (const QString str) { nome = str; }

	uint getIdBlocoOpcao () { return idBlocoOpcao; }
	uint getIdPergunta () { return idPergunta; }
	QString getNome () { return nome; }

private:
	uint idBlocoOpcao;
	uint idPergunta;
	QString nome;

public:
	QPtrList<OpcaoVO> listaOpcoes;
};

#endif 	// BLOCOOPCAOVO_H