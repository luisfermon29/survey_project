#ifndef CONDICAOVO_H
#define CONDICAOVO_H

#include <qstring.h>

class CondicaoVO
{
public:
	CondicaoVO (const uint idCondicao=0, const uint idOpcao=0, const uint idProximaPergunta=0, const uint tipo=0)
	{
		setIdCondicao (idCondicao);
		setIdOpcao (idOpcao);
		setIdProximaPergunta (idProximaPergunta);
		setTipo(tipo);
	}

	void setIdCondicao (const uint id) { idCondicao = id; }
	void setIdOpcao (const uint id) { idOpcao = id; }
	void setIdProximaPergunta (const uint id) { idProximaPergunta = id; }
	void setTipo (const uint id) { tipo = id; }

	uint getIdCondicao () { return idCondicao; }
	uint getIdOpcao () { return idOpcao; }
	uint getIdProximaPergunta () { return idProximaPergunta; }
	uint getTipo () { return tipo; }

private:
	uint idCondicao;
	uint idOpcao;
	uint idProximaPergunta;
	uint tipo;
};

#endif 	// CONDICAOVO_H