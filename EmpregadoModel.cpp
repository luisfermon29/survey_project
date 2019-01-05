#include "EmpregadoModel.h"


EmpregadoModel::EmpregadoModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

EmpregadoModel::~EmpregadoModel()
{
	list.clear();
}

void EmpregadoModel::insereEmpregado(const uint idEmpregado, const QString matricula, const QString nome)
{
	list.append(new EmpregadoVO(idEmpregado, matricula, nome));
}