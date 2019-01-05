#ifndef BLOCOPSO_H
#define BLOCOPSO_H

#include "BlocoModel.h"
#include "PerguntaPSO.h"

#include <qsqlcursor.h>


class BlocoPSO
{
public:
	BlocoPSO(QSqlDatabase * sql=NULL);
	~BlocoPSO();

	bool lerBloco(BlocoModel * modelo, bool lerPerguntas=true, bool lerOpcoes=true);
	bool lerBlocoId(BlocoVO * bloco, uint idBloco, bool lerPerguntas=true, bool lerOpcoes=true);
	void lerBloco(QSqlCursor * cursor, BlocoVO * bloco);

	bool grvBloco(BlocoModel * modelo, bool grvPerguntas, bool grvOpcoes);
	bool grvBloco(BlocoVO * bloco, bool grvPerguntas, bool grvOpcoes, QSqlDatabase * sql=NULL);

	bool updBloco(BlocoModel * modelo, bool updPerguntas, bool updOpcoes);
	bool updBloco(BlocoVO * bloco, bool updPerguntas, bool updOpcoes, QSqlDatabase * sql=NULL);

	bool delBloco(BlocoModel * modelo, bool delPerguntas=true, bool delOpcoes=true);
	bool delBloco(BlocoVO * bloco, bool delPerguntas=true, bool delOpcoes=true, QSqlDatabase * sql=NULL);


	QSqlDatabase * db;
	PerguntaPSO * perguntaPso;
};

#endif 	// BLOCOPSO_H