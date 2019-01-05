#ifndef CONDICAOPSO_H
#define CONDICAOPSO_H

#include "OpcaoVO.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>


class CondicaoPSO
{
public:
	CondicaoPSO(QSqlDatabase * sql=NULL);

	bool lerCondicaoId(CondicaoVO * condicao, uint idCondicao);
	bool lerCondicaoIdOpcao(OpcaoVO * opcao, uint idOpcao);
	void lerCondicao(QSqlCursor * cursor, CondicaoVO * condicao);

	bool grvCondicao(OpcaoVO * opcao);
	bool grvCondicao(CondicaoVO * condicao, QSqlDatabase * sql=NULL);

	bool updCondicao(OpcaoVO * opcao);
	bool updCondicao(CondicaoVO * condicao, QSqlDatabase * sql=NULL);

	bool delCondicao(OpcaoVO * opcao);
	bool delCondicao(CondicaoVO * condicao, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
};

#endif 	// CONDICAOPSO_H