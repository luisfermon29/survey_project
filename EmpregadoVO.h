#ifndef EMPREGADOVO_H
#define EMPREGADOVO_H


#include "LoginVO.h"

#include <qptrlist.h>


class EmpregadoVO
{
public:
	EmpregadoVO (const uint idEmpregado=0, const QString matricula="", const QString nome="")
	{
		setIdEmpregado (idEmpregado);
		setMatricula (matricula);
		setNome (nome);
	}

	~EmpregadoVO()
	{
		listaLogin.clear();
	}

	void insereLogin(const uint idLogin=0, const uint idEmpregado=0, const uint perfil=0, const QString login="", const QString senha="")
	{
		listaLogin.append(new LoginVO(idLogin, idEmpregado, perfil, login, senha));
	}

	void setIdEmpregado (uint id) { idEmpregado = id; }
	void setMatricula (QString str) { matricula = str; }
	void setNome (QString str) { nome = str; }

	uint getIdEmpregado () { return idEmpregado; }
	QString getMatricula () { return matricula; }
	QString getNome () { return nome; }

private:
	uint idEmpregado;
	QString matricula;
	QString nome;

public:
	QPtrList<LoginVO> listaLogin;
};

#endif 	// EMPREGADOVO_H