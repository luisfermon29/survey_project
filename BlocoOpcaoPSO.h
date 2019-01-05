#ifndef BLOCOOPCAOPSO_H
#define BLOCOOPCAOPSO_H

#include "BlocoOpcaoModel.h"
#include "OpcaoPSO.h"
#include "PerguntaVO.h"

#include <qsqlcursor.h>


class BlocoOpcaoPSO
{
public:
	BlocoOpcaoPSO(QSqlDatabase * sql=NULL);
	~BlocoOpcaoPSO();

	bool lerBlocoOpcaoIdPergunta(BlocoOpcaoModel * modelo, uint idPergunta, bool lerOpcoes=true);
	bool lerBlocoOpcaoIdPergunta(PerguntaVO * pergunta, uint idPergunta, bool lerOpcoes=true);
	bool lerBlocoOpcaoId(BlocoOpcaoVO * blocoOpcao, uint idBlocoOpcao, bool lerOpcoes=true);
	void lerBlocoOpcao(QSqlCursor * cursor, BlocoOpcaoVO * blocoOpcao);

	bool grvBlocoOpcao(BlocoOpcaoModel * modelo, bool grvOpcoes);
	bool grvBlocoOpcao(PerguntaVO * pergunta, bool grvOpcoes);
	bool grvBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool grvOpcoes, QSqlDatabase * sql=NULL);

	bool updBlocoOpcao(BlocoOpcaoModel * modelo, bool updOpcoes);
	bool updBlocoOpcao(PerguntaVO * pergunta, bool updOpcoes);
	bool updBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool updOpcoes, QSqlDatabase * sql=NULL);

	bool delBlocoOpcao(BlocoOpcaoModel * modelo, bool delOpcoes=true);
	bool delBlocoOpcao(PerguntaVO * pergunta, bool delOpcoes=true);
	bool delBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool delOpcoes=true, QSqlDatabase * sql=NULL);


	QSqlDatabase * db;
	OpcaoPSO * opcaoPso;
};

#endif 	// BLOCOOPCAOPSO_H