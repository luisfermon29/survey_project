#include "EmpregadoPSO.h"


EmpregadoPSO::EmpregadoPSO(QSqlDatabase * sql)
{
	db = sql;

	loginPso = new LoginPSO(db);
}

EmpregadoPSO::~EmpregadoPSO()
{
	delete loginPso;
}

bool EmpregadoPSO::lerEmpregado(EmpregadoModel * modelo, bool lerLogins)
{
	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select())
		return false;

	while (cursor.next()) {
		modelo->insereEmpregado();
		lerEmpregado(&cursor, modelo->list.last());

		if (lerLogins)
			loginPso->lerLoginIdEmpregado(modelo->list.last(), modelo->list.last()->getIdEmpregado());
	}

	return true;
}

bool EmpregadoPSO::lerEmpregadoId(EmpregadoVO * empregado, uint idEmpregado, bool lerLogins)
{
	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select("id_empregado = " + QString::number(idEmpregado)))
		return false;

	if (!cursor.next())
		return false;

	lerEmpregado(&cursor, empregado);

	if (lerLogins)
		loginPso->lerLoginIdEmpregado(empregado, empregado->getIdEmpregado());

	return true;
}

bool EmpregadoPSO::lerEmpregadoNome(EmpregadoModel * modelo, QString nome, bool lerLogins)
{
	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select("nm_empregado like '%" + nome + "%'"))
		return false;

	while (cursor.next()) {
		modelo->insereEmpregado();
		lerEmpregado(&cursor, modelo->list.last());

		if (lerLogins)
			loginPso->lerLoginIdEmpregado(modelo->list.last(), modelo->list.last()->getIdEmpregado());
	}

	return true;
}

bool EmpregadoPSO::lerEmpregadoMatricula(EmpregadoModel * modelo, QString matricula, bool lerLogins)
{
	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select("num_matricula = '" + matricula + "'"))
		return false;

	while (cursor.next()) {
		modelo->insereEmpregado();
		lerEmpregado(&cursor, modelo->list.last());

		if (lerLogins)
			loginPso->lerLoginIdEmpregado(modelo->list.last(), modelo->list.last()->getIdEmpregado());
	}

	return true;
}

void EmpregadoPSO::lerEmpregado(QSqlCursor * cursor, EmpregadoVO * empregado)
{
	empregado->setIdEmpregado(cursor->value("id_empregado").toUInt());
	empregado->setMatricula(cursor->value("num_matricula").toString());
	empregado->setNome(cursor->value("nm_empregado").toString());
}

bool EmpregadoPSO::grvEmpregado(EmpregadoModel * modelo, bool grvLogins)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvEmpregado(modelo->list.at(index), grvLogins)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool EmpregadoPSO::grvEmpregado(EmpregadoVO * empregado, bool grvLogins, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_empregado (id_empregado, num_matricula, nm_empregado) values (id_empregado.nextval, :matricula, :nome)");
	qry.bindValue(":matricula", empregado->getMatricula());
	qry.bindValue(":nome", empregado->getNome());

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_empregado.currval from dual");
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	if (!qry.next()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	empregado->setIdEmpregado(qry.value(0).toUInt());

	if (grvLogins) {
		for (uint i=0; i<empregado->listaLogin.count(); i++) {
			empregado->listaLogin.at(i)->setIdEmpregado(empregado->getIdEmpregado());
			if (!loginPso->grvLogin(empregado->listaLogin.at(i))) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool EmpregadoPSO::updEmpregado(EmpregadoModel * modelo, bool updLogins)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updEmpregado(modelo->list.at(index), updLogins)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool EmpregadoPSO::updEmpregado(EmpregadoVO * empregado, bool updLogins, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select("id_empregado = " + QString::number(empregado->getIdEmpregado()))) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	if (!cursor.next()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	QSqlRecord * buffer = cursor.primeUpdate();
	buffer->setValue("num_matricula", empregado->getMatricula());
	buffer->setValue("nm_empregado", empregado->getNome());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (updLogins) {
		for (uint i=0; i<empregado->listaLogin.count(); i++) {
			if (!loginPso->updLogin(empregado->listaLogin.at(i))) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool EmpregadoPSO::delEmpregado(EmpregadoModel * modelo, bool delLogins)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delEmpregado(modelo->list.at(index), delLogins)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool EmpregadoPSO::delEmpregado(EmpregadoVO * empregado, bool delLogins, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	if (delLogins) {
		for (uint i=0; i<empregado->listaLogin.count(); i++) {
			if (!loginPso->delLogin(empregado->listaLogin.at(i))) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	QSqlCursor cursor("tb_pesq_empregado");
	if (!cursor.select("id_empregado = " + QString::number(empregado->getIdEmpregado()))) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	if (!cursor.next()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	cursor.primeDelete();
	if (cursor.del() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}