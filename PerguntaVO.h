#ifndef PERGUNTAVO_H
#define PERGUNTAVO_H


#include "BlocoOpcaoVO.h"
#include "RespostaModel.h"

#include <qptrlist.h>


class PerguntaVO
{
public:
	PerguntaVO (const uint idPergunta=0, const uint idBloco=0, const uint tipo=0, const QString textoPergunta="", const QString textoExplicativo="", const bool textoAntes=false, const uint ordem=0)
	{
		setIdPergunta (idPergunta);
		setIdBloco (idBloco);
		setTipo(tipo);
		setTextoPergunta (textoPergunta);
		setTextoExplicativo (textoExplicativo);
		setTextoAntes (textoAntes);
		setOrdem (ordem);

		listaBlocoOpcoes.clear();
		listaBlocoOpcoes.setAutoDelete(true);

		respostaModel = new RespostaModel;
	}

	~PerguntaVO()
	{
		listaBlocoOpcoes.clear();

		if (respostaModel != NULL)
			delete respostaModel;
	}

	void insereBlocoOpcao(const uint idBlocoOpcao=0, const uint idPergunta=0, const QString nome="")
	{
		listaBlocoOpcoes.append(new BlocoOpcaoVO(idBlocoOpcao, idPergunta, nome));
	}

	void setIdPergunta (const uint id) { idPergunta = id; }
	void setIdBloco (const uint id) { idBloco = id; }
	void setTipo (const uint id) { tipo = id; }
	void setTextoPergunta (const QString str) { textoPergunta = str; }
	void setTextoExplicativo (const QString str) { textoExplicativo = str; }
	void setTextoAntes (const bool flag) { textoAntes = flag; }
	void setOrdem (const uint ord) { ordem = ord; }

	uint getIdPergunta () { return idPergunta; }
	uint getIdBloco () { return idBloco; }
	uint getTipo () { return tipo; }
	QString getTextoPergunta () { return textoPergunta; }
	QString getTextoExplicativo () { return textoExplicativo; }
	bool getTextoAntes () { return textoAntes; }
	uint getOrdem () { return ordem; }

private:
	uint idPergunta;
	uint idBloco;
	uint tipo;
	QString textoPergunta;
	QString textoExplicativo;
	bool textoAntes;
	uint ordem;

public:
	QPtrList<BlocoOpcaoVO> listaBlocoOpcoes;
	RespostaModel * respostaModel;
};

#endif 	// PERGUNTAVO_H