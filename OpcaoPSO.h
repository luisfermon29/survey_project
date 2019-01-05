#ifndef OPCAOPSO_H
#define OPCAOPSO_H

#include "BlocoOpcaoVO.h"
#include "OpcaoModel.h"
#include "CondicaoPSO.h"

#include <stdlib.h>
#include <qdatetime.h>
#include <time.h>

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class OpcaoPSO
{
public:
	OpcaoPSO(QSqlDatabase * sql=NULL);
	~OpcaoPSO();

	bool lerOpcaoId(OpcaoVO * opcao, uint idOpcao);
	bool lerOpcaoIdBlocoOpcao(BlocoOpcaoVO * blocoOpcao, uint idBlocoOpcao);
	bool lerOpcaoIdBlocoOpcao(OpcaoModel * modelo, uint idBlocoOpcao);
	void lerOpcao(QSqlCursor * cursor, OpcaoVO * opcao);
	void lerOpcaoTexto(QSqlQuery * qry, OpcaoVO * opcao);

	bool grvOpcao(BlocoOpcaoVO * blocoOpcao);
	bool grvOpcao(OpcaoModel * modelo);
	bool grvOpcao(OpcaoVO * opcao, QSqlDatabase * sql=NULL);

	bool updOpcao(BlocoOpcaoVO * blocoOpcao);
	bool updOpcao(OpcaoModel * modelo);
	bool updOpcao(OpcaoVO * opcao, QSqlDatabase * sql=NULL);

	bool delOpcao(BlocoOpcaoVO * blocoOpcao);
	bool delOpcao(OpcaoModel * modelo);
	bool delOpcao(OpcaoVO * opcao, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
	CondicaoPSO * condicaoPso;
};

#endif 	// OPCAOPSO_H