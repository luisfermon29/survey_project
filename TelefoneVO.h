#ifndef TELEFONEVO_H
#define TELEFONEVO_H

#include <qstring.h>

class TelefoneVO
{
public:
	TelefoneVO (const uint idTelefone=0, const uint idCliente=0, const uint ordem=0, const uint telefone=0, const uint ramal=0, const uint ddd=0, const uint ddi=0)
	{
		setIdTelefone (idTelefone);
		setIdCliente (idCliente);
		setOrdem (ordem);
		setTelefone (telefone);
		setRamal (ramal);
		setDdd (ddd);
		setDdi (ddi);
	}

	void setIdTelefone (const uint id) { idTelefone = id; }
	void setIdCliente (const uint id) { idCliente = id; }
	void setOrdem (const uint id) { ordem = id; }
	void setTelefone (const uint id) { telefone = id; }
	void setRamal (const uint id) { ramal = id; }
	void setDdd (const uint id) { ddd = id; }
	void setDdi (const uint id) { ddi = id; }

	uint getIdTelefone () { return idTelefone; }
	uint getIdCliente () { return idCliente; }
	uint getOrdem () { return ordem; }
	uint getTelefone () { return telefone; }
	uint getRamal () { return ramal; }
	uint getDdd () { return ddd; }
	uint getDdi () { return ddi; }

private:
	uint idTelefone;
	uint idCliente;
	uint ordem;
	uint telefone;
	uint ramal;
	uint ddd;
	uint ddi;
};

#endif 	// TELEFONEVO_H