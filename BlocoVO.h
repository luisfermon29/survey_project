#ifndef BLOCOVO_H
#define BLOCOVO_H


#include "PerguntaVO.h"


class BlocoVO
{
public:
	BlocoVO (const uint idBloco=0, const QString nome="", const QString descricao="", const QString tipo="")
	{
		setIdBloco (idBloco);
		setNome (nome);
		setDescricao (descricao);
		setTipo (tipo);

		listaPerguntas.clear();
		listaPerguntas.setAutoDelete(true);
	}

	~BlocoVO()
	{
		listaPerguntas.clear();
	}

	void inserePergunta(const uint idPergunta=0, const uint idBloco=0, const uint tipo=0, const QString textoPergunta="", const QString textoExplicativo="", const bool textoAntes=false, const uint ordem=0)
	{
		listaPerguntas.append(new PerguntaVO(idPergunta, idBloco, tipo, textoPergunta, textoExplicativo, textoAntes, ordem));
	}

	void setIdBloco (const uint id) { idBloco = id; }
	void setNome (const QString str) { nome = str; }
	void setDescricao (const QString str) { descricao = str; }
	void setTipo (const QString str) { tipo = str; }

	uint getIdBloco () { return idBloco; }
	QString getNome () { return nome; }
	QString getDescricao () { return descricao; }
	QString getTipo () { return tipo; }

private:
	uint idBloco;
	QString nome;
	QString descricao;
	QString tipo;

public:
	QPtrList<PerguntaVO> listaPerguntas;
};

#endif 	// BLOCOVO_H