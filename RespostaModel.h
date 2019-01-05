#ifndef RESPOSTAMODEL_H
#define RESPOSTAMODEL_H


#include "RespostaVO.h"

#include <qsqldatabase.h>


class RespostaModel
{
public:
    RespostaModel(QSqlDatabase *sql=NULL);
    ~RespostaModel();

	void insereResposta (const uint idCliente=0, const uint idOpcao=0, const uint idOpcaoRelacionada=0, const QString tagSelecionada="", const QString tagRelacionada="", const QString texto="");

	QSqlDatabase *db;
	QPtrList<RespostaVO> list;
};

#endif 	// RESPOSTAMODEL_H