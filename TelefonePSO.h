#ifndef TELEFONEPSO_H
#define TELEFONEPSO_H

#include "ClienteVO.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class TelefonePSO
{
public:
	TelefonePSO(QSqlDatabase * sql=NULL);

	bool lerTelefoneId(TelefoneVO * telefone, uint idTelefone);
	bool lerTelefoneIdCliente(ClienteVO * cliente, uint idCliente);
	void lerTelefone(QSqlCursor * cursor, TelefoneVO * telefone);

	bool grvTelefone(ClienteVO * cliente);
	bool grvTelefone(TelefoneVO * telefone, QSqlDatabase * sql=NULL);

	bool updTelefone(ClienteVO * cliente);
	bool updTelefone(TelefoneVO * telefone, QSqlDatabase * sql=NULL);

	bool delTelefone(ClienteVO * cliente);
	bool delTelefone(TelefoneVO * telefone, QSqlDatabase * sql=NULL);
	bool delTelefonesIdCliente(uint idCliente, QSqlDatabase * sql=NULL);

	int verificaTelefone (uint telefone, uint ddd);

	QSqlDatabase * db;
};

#endif 	// TELEFONEPSO_H