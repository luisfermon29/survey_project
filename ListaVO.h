#ifndef LISTAVO_H
#define LISTAVO_H

#include <qstring.h>

class ListaVO
{
public:
	ListaVO (const uint idLista=0, const uint idCampanha=0, const uint idCliente=0, const bool flagLig=false, const uint tp=0)
	{
		setIdLista (idLista);
		setIdCampanha (idCampanha);
		setIdCliente (idCliente);
		setFlagLig (flagLig);
		setTp (tp);
	}

	void setIdLista (const uint id) { idLista = id; }
	void setIdCampanha (const uint id) { idCampanha= id; }
	void setIdCliente (const uint id) { idCliente = id; }
	void setFlagLig (const bool flag) { flagLig = flag; }
	void setTp (const uint id) { tp = id; }

	uint getIdLista () { return idLista; }
	uint getIdCampanha () { return idCampanha; }
	uint getIdCliente () { return idCliente; }
	bool getFlagLig () { return flagLig; }
	uint getTp () { return tp; }

private:
	uint idLista;
	uint idCampanha;
	uint idCliente;
	bool flagLig;
	uint tp;
};

#endif 	// LISTAVO_H