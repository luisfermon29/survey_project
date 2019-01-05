#ifndef PERGUNTAPSO_H
#define PERGUNTAPSO_H

#include "PerguntaModel.h"
#include "BlocoOpcaoPSO.h"
#include "BlocoVO.h"

#include <qsqlcursor.h>


class PerguntaPSO
{
public:
	PerguntaPSO(QSqlDatabase * sql=NULL);
	~PerguntaPSO();

	bool lerPerguntaId(PerguntaVO * pergunta, uint idPergunta, bool lerOpcoes=true);
	bool lerPerguntaIdBloco(PerguntaModel * modelo, uint idBloco, bool lerOpcoes=true);
	bool lerPerguntaIdBloco(BlocoVO * bloco, uint idBloco, bool lerOpcoes=true);
	void lerPergunta(QSqlCursor * cursor, PerguntaVO * pergunta);

	bool grvPergunta(PerguntaModel * modelo, bool grvOpcoes);
	bool grvPergunta(BlocoVO * bloco, bool grvOpcoes);
	bool grvPergunta(PerguntaVO * pergunta, bool grvOpcoes, QSqlDatabase * sql=NULL);

	bool updPergunta(PerguntaModel * modelo, bool updOpcoes);
	bool updPergunta(BlocoVO * bloco, bool updOpcoes);
	bool updPergunta(PerguntaVO * pergunta, bool updOpcoes, QSqlDatabase * sql=NULL);

	bool delPergunta(PerguntaModel * modelo, bool delOpcoes=true);
	bool delPergunta(BlocoVO * bloco, bool delOpcoes=true);
	bool delPergunta(PerguntaVO * pergunta, bool delOpcoes=true, QSqlDatabase * sql=NULL);


	QSqlDatabase * db;
	BlocoOpcaoPSO * blocoOpcaoPso;
};

#endif 	// PERGUNTAPSO_H