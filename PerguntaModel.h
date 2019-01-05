#ifndef PERGUNTAMODEL_H
#define PERGUNTAMODEL_H


#include "PerguntaVO.h"

#include <qsqldatabase.h>


class PerguntaModel
{
public:
    PerguntaModel(QSqlDatabase *sql=NULL);
    ~PerguntaModel();

	void inserePergunta (const uint idPergunta=0, const uint idBloco=0, const uint tipo=0, const QString textoPergunta="", const QString textoExplicativo="", const bool textoAntes=false, const uint ordem=0);

	QSqlDatabase *db;
	QPtrList<PerguntaVO> list;
};

#endif 	// PERGUNTAMODEL_H