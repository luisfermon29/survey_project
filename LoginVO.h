#ifndef LOGINVO_H
#define LOGINVO_H


#include <qstring.h>


class LoginVO
{
public:
	LoginVO (const uint idLogin=0, const uint idEmpregado=0, const uint perfil=0, const QString login="", const QString senha="", const uint status=0)
	{
		setIdLogin (idLogin);
		setIdEmpregado (idEmpregado);
		setPerfil (perfil);
		setLogin (login);
		setSenha (senha);
		setStatus (status);
	}

	void setIdLogin (uint id) { idLogin = id; }
	void setIdEmpregado (uint id) { idEmpregado = id; }
	void setPerfil (uint id) { perfil = id; }
	void setLogin (QString str) { login = str; }
	void setSenha (QString str) { senha = str; }
	void setStatus (uint id) { status = id; }

	uint getIdLogin () { return idLogin; }
	uint getIdEmpregado () { return idEmpregado; }
	uint getPerfil () { return perfil; }
	QString getLogin () { return login; }
	QString getSenha () { return senha; }
	uint getStatus () { return status; }

private:
	uint idLogin;
	uint idEmpregado;
	uint perfil;
	QString login;
	QString senha;
	uint status;
};

#endif 	// LOGINVO_H