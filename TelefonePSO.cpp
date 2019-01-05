#include "TelefonePSO.h"


TelefonePSO::TelefonePSO(QSqlDatabase * sql)
{
	db = sql;
}


bool TelefonePSO::lerTelefoneId(TelefoneVO * telefone, uint idTelefone)
{
	QSqlCursor cursor("tb_pesq_telefone");
	if (!cursor.select("id_telefone = " + QString::number(idTelefone)))
		return false;

	if (!cursor.next())
		return false;

	lerTelefone(&cursor, telefone);

	return true;
}

bool TelefonePSO::lerTelefoneIdCliente(ClienteVO * cliente, uint idCliente)
{
	QSqlCursor cursor("tb_pesq_telefone");
	if (!cursor.select("id_cliente = " + QString::number(idCliente) + " order by nu_ordem asc"))
		return false;

	while (cursor.next()) {
		cliente->insereTelefone();
		lerTelefone(&cursor, cliente->listaTel.last());
	}

	return true;
}

void TelefonePSO::lerTelefone(QSqlCursor * cursor, TelefoneVO * telefone)
{
	telefone->setIdTelefone(cursor->value("id_telefone").toUInt());
	telefone->setIdCliente(cursor->value("id_cliente").toUInt());
	telefone->setOrdem(cursor->value("nu_ordem").toUInt());
	telefone->setTelefone(cursor->value("nu_telefone").toUInt());
	telefone->setRamal(cursor->value("nu_ramal").toUInt());
	telefone->setDdd(cursor->value("nu_ddd").toUInt());
	telefone->setDdi(cursor->value("nu_ddi").toUInt());
}

bool TelefonePSO::grvTelefone(ClienteVO * cliente)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<cliente->listaTel.count(); index++) {
		if (!grvTelefone(cliente->listaTel.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool TelefonePSO::grvTelefone(TelefoneVO * telefone, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_telefone (id_telefone, id_cliente, nu_ordem, nu_telefone, nu_ramal, nu_ddd, nu_ddi) values (id_telefone.nextval, :cliente, :ordem, :telefone, :ramal, :ddd, :ddi)");
	qry.bindValue(":cliente", telefone->getIdCliente());
	qry.bindValue(":ordem", telefone->getOrdem());
	qry.bindValue(":telefone", telefone->getTelefone());
	qry.bindValue(":ramal", telefone->getRamal());
	qry.bindValue(":ddd", telefone->getDdd());
	qry.bindValue(":ddi", telefone->getDdi());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_telefone.currval from dual");
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
	telefone->setIdTelefone(qry.value(0).toUInt());

	if (sql != NULL)
		sql->commit();
	return true;
}

bool TelefonePSO::updTelefone(ClienteVO * cliente)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<cliente->listaTel.count(); index++) {
		if (!updTelefone(cliente->listaTel.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool TelefonePSO::updTelefone(TelefoneVO * telefone, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_telefone");
	if (!cursor.select("id_telefone = " + QString::number(telefone->getIdTelefone()))) {
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
	buffer->setValue("id_cliente", telefone->getIdCliente());
	buffer->setValue("nu_ordem", telefone->getOrdem());
	buffer->setValue("nu_telefone", telefone->getTelefone());
	buffer->setValue("nu_ramal", telefone->getRamal());
	buffer->setValue("nu_ddd", telefone->getDdd());
	buffer->setValue("nu_ddi", telefone->getDdi());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool TelefonePSO::delTelefone(ClienteVO * cliente)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<cliente->listaTel.count(); index++) {
		if (!delTelefone(cliente->listaTel.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool TelefonePSO::delTelefone(TelefoneVO * telefone, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_telefone");
	if (!cursor.select("id_telefone = " + QString::number(telefone->getIdTelefone()))) {
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

bool TelefonePSO::delTelefonesIdCliente(uint idCliente, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("delete tb_pesq_telefone where id_cliente = :idCliente");
	qry.bindValue(":idCliente", idCliente);
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

int TelefonePSO::verificaTelefone(uint telefone, uint ddd)
{
	QSqlQuery qry;
	qry.prepare("select count(*) from tb_pesq_telefone where nu_telefone = :tel and nu_ddd = :ddd");
	qry.bindValue(":tel", telefone);
	qry.bindValue(":ddd", ddd);
	if (!qry.exec())
		return -1;
	if (!qry.next())
		return 0;

	return qry.value(0).toInt();
}