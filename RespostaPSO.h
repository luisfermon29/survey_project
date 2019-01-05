#ifndef RESPOSTAPSO_H
#define RESPOSTAPSO_H

#include "RespostaModel.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class RespostaPSO
{
public:
	RespostaPSO(QSqlDatabase * sql=NULL);

	bool lerRespostaIdCliente(RespostaModel * modelo, uint idCliente);
	bool lerRespostaIdClientePergunta(RespostaModel * modelo, uint idCliente, uint idPergunta);
	bool lerRespostaIdClienteBlocoOpcao(RespostaModel * modelo, uint idCliente, uint idBlocoOpcao);
	bool lerRespostaIdClienteOpcao(RespostaModel * modelo, uint idCliente, uint idOpcao);
	void lerResposta(QSqlCursor * cursor, RespostaVO * resposta);

	bool grvResposta(RespostaModel * modelo, QSqlDatabase * sql=NULL);
	bool grvResposta(RespostaVO * resposta, QSqlDatabase * sql=NULL);

	bool updResposta(RespostaModel * modelo);
	bool updResposta(RespostaVO * resposta, QSqlDatabase * sql=NULL);

	bool delResposta(RespostaModel * modelo);
	bool delResposta(RespostaVO * resposta, QSqlDatabase * sql=NULL);
	bool delRespostaIdCliente(uint idCliente, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
};

#endif 	// RESPOSTAPSO_H