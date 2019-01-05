#ifndef EMPREGADOMODEL_H
#define EMPREGADOMODEL_H


#include "EmpregadoVO.h"
#include "Observer.h"

#include <qsqldatabase.h>


class EmpregadoModel
{
public:
    EmpregadoModel(QSqlDatabase *sql=NULL);
    ~EmpregadoModel();

	void attach(const Observer *s) { registry.append(s); }
	void dettach(const Observer *s) { registry.remove(s); }

	void insereEmpregado(const uint idEmpregado=0, const QString matricula="", const QString nome="");

	QSqlDatabase * db;
	QPtrList<EmpregadoVO> list;
	QPtrList<Observer> registry;
	int linha;
};

#endif 	// EMPREGADOMODEL_H