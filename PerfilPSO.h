#ifndef PERFILPSO_H
#define PERFILPSO_H

#include "PerfilModel.h"

#include <qsqlcursor.h>


class PerfilPSO
{
public:
	PerfilPSO(QSqlDatabase * sql=NULL);

	bool lerPerfil(PerfilModel * modelo);
	void lerPerfil(QSqlCursor * cursor, PerfilVO * perfil);

	QSqlDatabase * db;
};

#endif 	// PERFILPSO_H