#ifndef TIPOCAMPANHAVO_H
#define TIPOCAMPANHAVO_H


#include <qstring.h>


class TipoCampanhaVO
{
public:
	TipoCampanhaVO (const uint idTipoCampanha=0, const QString nome="", const QString descricao="")
	{
		setIdTipoCampanha (idTipoCampanha);
		setNome (nome);
		setDescricao (descricao);
	}

	void setIdTipoCampanha (const uint id) { idTipoCampanha = id; }
	void setNome (const QString str) { nome = str; }
	void setDescricao (const QString str) { descricao = str; }

	uint getIdTipoCampanha () { return idTipoCampanha; }
	QString getNome () { return nome; }
	QString getDescricao () { return descricao; }

private:
	uint idTipoCampanha;
	QString nome;
	QString descricao;
};

#endif 	// TIPOCAMPANHAVO_H