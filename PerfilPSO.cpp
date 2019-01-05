#include "PerfilPSO.h"


PerfilPSO::PerfilPSO(QSqlDatabase * sql)
{
	db = sql;
}


bool PerfilPSO::lerPerfil(PerfilModel * modelo)
{
	QSqlCursor cursor("tb_pesq_perfil");
	if (!cursor.select())
		return false;

	while (cursor.next()) {
		modelo->inserePerfil();
		lerPerfil(&cursor, modelo->list.last());
	}

	return true;
}


void PerfilPSO::lerPerfil(QSqlCursor * cursor, PerfilVO * perfil)
{
	perfil->setIdPerfil(cursor->value("id_perfil").toUInt());
	perfil->setNome(cursor->value("nm_perfil").toString());
}