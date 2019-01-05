#ifndef RECHAMADAVO_H
#define RECHAMADAVO_H

#include <qstring.h>
#include <qdatetime.h>

class RechamadaVO
{
public:
	RechamadaVO (const uint idRechamada=0, const uint idCampanha=0, const uint idCliente=0, const uint idLogin=0, const QDateTime data=QDateTime::QDateTime(), const bool flagLig=false)
	{
		setIdRechamada (idRechamada);
		setIdCampanha (idCampanha);
		setIdCliente (idCliente);
		setIdLogin (idLogin);
		setData (data);
		setFlagLig (flagLig);
	}

	void setIdRechamada (const uint id) { idRechamada = id; }
	void setIdCampanha (const uint id) { idCampanha= id; }
	void setIdCliente (const uint id) { idCliente = id; }
	void setIdLogin (const uint id) { idLogin = id; }
	void setData (const QDateTime dt) { data = dt; }
	void setFlagLig (const bool flag) { flagLig = flag; }

	uint getIdRechamada () { return idRechamada; }
	uint getIdCampanha () { return idCampanha; }
	uint getIdCliente () { return idCliente; }
	uint getIdLogin () { return idLogin; }
	QDateTime getData () { return data; }
	bool getFlagLig () { return flagLig; }

private:
	uint idRechamada;
	uint idCampanha;
	uint idCliente;
	uint idLogin;
	QDateTime data;
	bool flagLig;
};

#endif 	// RECHAMADAVO_H