#ifndef PERFILVO_H
#define PERFILVO_H


#include <qstring.h>


class PerfilVO
{
public:
	PerfilVO (const uint idPerfil=0, const QString nome="")
	{
		setIdPerfil (idPerfil);
		setNome (nome);
	}

	void setIdPerfil (const uint id) { idPerfil = id; }
	void setNome (const QString str) { nome = str; }

	uint getIdPerfil () { return idPerfil; }
	QString getNome () { return nome; }

private:
	uint idPerfil;
	QString nome;
};

#endif 	// PERFILVO_H