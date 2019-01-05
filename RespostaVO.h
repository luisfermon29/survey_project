#ifndef RESPOSTAVO_H
#define RESPOSTAVO_H

#include <qstring.h>

class RespostaVO
{
public:
	RespostaVO (const uint idCliente=0, const uint idOpcao=0, const uint idOpcaoRelacionada=0, const QString tagSelecionada="", const QString tagRelacionada="", const QString texto="")
	{
		setIdCliente (idCliente);
		setIdOpcao (idOpcao);
		setIdOpcaoRelacionada (idOpcaoRelacionada);
		setTagSelecionada (tagSelecionada);
		setTagRelacionada (tagRelacionada);
		setTexto (texto);
	}

	void setIdCliente (const uint id) { idCliente = id; }
	void setIdOpcao (const uint id) { idOpcao = id; }
	void setIdOpcaoRelacionada (const uint id) { idOpcaoRelacionada = id; }
	void setTagSelecionada (const QString str) { tagSelecionada = str; }
	void setTagRelacionada (const QString str) { tagRelacionada = str; }
	void setTexto (const QString str) { texto = str; }

	uint getIdCliente () { return idCliente; }
	uint getIdOpcao () { return idOpcao; }
	uint getIdOpcaoRelacionada () { return idOpcaoRelacionada; }
	QString getTagSelecionada () { return tagSelecionada; }
	QString getTagRelacionada () { return tagRelacionada; }
	QString getTexto () { return texto; }

private:
	uint idCliente;
	uint idOpcao;
	uint idOpcaoRelacionada;
	QString tagSelecionada;
	QString tagRelacionada;
	QString texto;
};

#endif 	// RESPOSTAVO_H