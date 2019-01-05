#include "LoginPSO.h"


LoginPSO::LoginPSO(QSqlDatabase * sql)
{
	db = sql;
}


bool LoginPSO::lerLoginId(LoginVO * login, uint idLogin)
{
	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("id_login = " + QString::number(idLogin)))
		return false;

	if (!cursor.next())
		return false;

	lerLogin(&cursor, login);

	return true;
}

bool LoginPSO::lerLoginIdEmpregado(LoginModel * modelo, uint idEmpregado)
{
	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("id_empregado = " + QString::number(idEmpregado)))
		return false;

	while (cursor.next()) {
		modelo->insereLogin();
		lerLogin(&cursor, modelo->list.last());
	}

	return true;
}

bool LoginPSO::lerLoginIdEmpregado(EmpregadoVO * empregado, uint idEmpregado)
{
	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("id_empregado = " + QString::number(idEmpregado)))
		return false;

	while (cursor.next()) {
		empregado->insereLogin();
		lerLogin(&cursor, empregado->listaLogin.last());
	}

	return true;
}

bool LoginPSO::lerLoginUsername(LoginVO * login, QString nome, QString senha)
{
	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("cd_login = '" + nome + "' and cd_senha = '" + senha + "'"))
		return false;

	if (!cursor.next())
		return false;

	lerLogin(&cursor, login);

	return true;
}

void LoginPSO::lerLogin(QSqlCursor * cursor, LoginVO * login)
{
	login->setIdLogin(cursor->value("id_login").toUInt());
	login->setIdEmpregado(cursor->value("id_empregado").toUInt());
	login->setPerfil(cursor->value("id_perfil").toUInt());
	login->setLogin(cursor->value("cd_login").toString());
	login->setSenha(cursor->value("cd_senha").toString());
	login->setStatus(cursor->value("status").toUInt());
}

bool LoginPSO::grvLogin(LoginModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvLogin(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::grvLogin(EmpregadoVO * empregado)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<empregado->listaLogin.count(); index++) {
		if (!grvLogin(empregado->listaLogin.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::grvLogin(LoginVO * login, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_login (id_login, id_empregado, id_perfil, cd_login, cd_senha, status) values (id_login.nextval, :empregado, :perfil, :codLogin, :senha, 0)");
	qry.bindValue(":empregado", login->getIdEmpregado());
	qry.bindValue(":perfil", login->getPerfil());
	qry.bindValue(":codLogin", login->getLogin());
	qry.bindValue(":senha", login->getSenha());

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_login.currval from dual");
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
	login->setIdLogin(qry.value(0).toUInt());

	if (sql != NULL)
		sql->commit();
	return true;
}

bool LoginPSO::updLogin(LoginModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updLogin(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::updLogin(EmpregadoVO * empregado)
{
	uint index;

	if (db != NULL)
		db->transaction();

	// Verifica se o empregado tem outros logins. Se tiver, exclui
	QSqlQuery qry;
	qry.prepare("select id_login, cd_login from tb_pesq_login where id_empregado = :empregado");
	qry.bindValue(":empregado", empregado->getIdEmpregado());
	if (!qry.exec()) {
		if (db != NULL)
			db->rollback();
		return false;
	}
	LoginModel *modelo = new LoginModel;
	while (qry.next()) {
		modelo->insereLogin();
		modelo->list.last()->setIdLogin(qry.value(0).toUInt());
		modelo->list.last()->setLogin(qry.value(1).toString());
	}

	// Atualiza logins do empregado
	for (index=0; index<empregado->listaLogin.count(); index++) {
		int index2 = -1;
		for (index2=0; (uint)index2<modelo->list.count(); index2++) {
			if (empregado->listaLogin.at(index)->getLogin() == modelo->list.at(index2)->getLogin()) {
				break;
			}
		}
		if ((index2 != -1) && ((uint)index2 < modelo->list.count())) {
			// Login encontrado - atualizar
			if (!updLogin(empregado->listaLogin.at(index))) {
				if (db != NULL)
					db->rollback();

				return false;
			}
			modelo->list.remove(index2);
		} else {
			// Login não encontrado - inserir
			if (!grvLogin(empregado->listaLogin.at(index))) {
				if (db != NULL)
					db->rollback();

				return false;
			}
		}
	}
	while (modelo->list.count() > 0) {
		// Exclui os demais logins
		if (!delLogin(modelo->list.first())) {
			if (db != NULL)
				db->rollback();

			return false;
		}
		modelo->list.removeFirst();
	}

	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::updLogin(LoginVO * login, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("id_login = " + QString::number(login->getIdLogin()))) {
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
	buffer->setValue("id_empregado", login->getIdEmpregado());
	buffer->setValue("id_perfil", login->getPerfil());
	buffer->setValue("cd_login", login->getLogin());
	buffer->setValue("cd_senha", login->getSenha());
	buffer->setValue("status", login->getStatus());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool LoginPSO::delLogin(LoginModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delLogin(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::delLogin(EmpregadoVO * empregado)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<empregado->listaLogin.count(); index++) {
		if (!delLogin(empregado->listaLogin.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool LoginPSO::delLogin(LoginVO * login, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_login");
	if (!cursor.select("id_login = " + QString::number(login->getIdLogin()))) {
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

bool LoginPSO::delLoginIdEmpregado(uint idEmpregado, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("delete tb_pesq_login where id_empregado = :empregado");
	qry.bindValue(":empregado", idEmpregado);
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

int LoginPSO::verificaLogin(QString login)
{
	QString str = "select count(*) from tb_pesq_login where upper(cd_login) = upper('" + login + "')";
	QSqlQuery qry;
	qry.prepare(str);
	if (!qry.exec())
		return -1;
	if (!qry.next())
		return 0;

	return qry.value(0).toUInt();
}

bool LoginPSO::resetLogin(QString login)
{

	QSqlQuery qry;
	qry.prepare("update tb_pesq_login set status = 0 where cd_login = :login");
	qry.bindValue(":login", login);
	if (!qry.exec()) {
		return false;
	}

	return true;
}