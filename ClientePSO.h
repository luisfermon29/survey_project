#ifndef CLIENTEPSO_H
#define CLIENTEPSO_H

#include "ClienteModel.h"
#include "TelefonePSO.h"

#include <qsqlcursor.h>


class ClientePSO
{
public:
	ClientePSO(QSqlDatabase * sql=NULL);
	~ClientePSO();

	bool lerClienteId(ClienteVO * cliente, uint idCliente, bool lerTelefones=true);
	bool lerClienteIdSegmento(ClienteModel * modelo, uint idSegmento, bool lerTelefones=true);
	bool lerClienteNome(ClienteModel * modelo, QString nome, bool lerTelefones=true);
	bool lerClienteTelefone(ClienteModel * modelo, uint telefone, bool lerTelefones=true);
	void lerCliente(QSqlCursor * cursor, ClienteVO * cliente);

	bool grvCliente(ClienteModel * modelo, bool grvTelefones);
	bool grvCliente(ClienteVO * cliente, bool grvTelefones, QSqlDatabase * sql=NULL);

	bool updCliente(ClienteModel * modelo, bool updTelefones);
	bool updCliente(ClienteVO * cliente, bool updTelefones, QSqlDatabase * sql=NULL);

	bool delCliente(ClienteModel * modelo, bool delTelefones=true);
	bool delCliente(ClienteVO * cliente, bool delTelefones=true, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
	TelefonePSO * telefonePso;
};

#endif 	// CLIENTEPSO_H