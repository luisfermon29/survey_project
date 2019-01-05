#include "CondicaoPSO.h"


CondicaoPSO::CondicaoPSO(QSqlDatabase * sql)
{
	db = sql;
}

bool CondicaoPSO::lerCondicaoId(CondicaoVO * condicao, uint idCondicao)
{
	QSqlCursor cursor("tb_pesq_condicao");
	if (!cursor.select("id_condicao = " + QString::number(idCondicao)))
		return false;

	if (!cursor.next())
		return false;

	lerCondicao(&cursor, condicao);

	return true;
}

bool CondicaoPSO::lerCondicaoIdOpcao(OpcaoVO * opcao, uint idOpcao)
{
	QSqlCursor cursor("tb_pesq_condicao");
	if (!cursor.select("id_opcao = " + QString::number(idOpcao) + " order by id_condicao asc"))
		return false;

	while (cursor.next()) {
		opcao->insereCondicao();
		lerCondicao(&cursor, opcao->listaCondicoes.last());
	}

	return true;
}

void CondicaoPSO::lerCondicao(QSqlCursor * cursor, CondicaoVO * condicao)
{
	condicao->setIdCondicao(cursor->value("id_condicao").toUInt());
	uint op = cursor->value("id_opcao").toUInt();
	condicao->setIdOpcao(op);
	condicao->setIdProximaPergunta(cursor->value("id_proxima_pergunta").toUInt());
	op = cursor->value("tp_condicao").toUInt();
	condicao->setTipo(op);
}

bool CondicaoPSO::grvCondicao(OpcaoVO * opcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<opcao->listaCondicoes.count(); index++) {
		if (!grvCondicao(opcao->listaCondicoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CondicaoPSO::grvCondicao(CondicaoVO * condicao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_condicao");
	QSqlRecord * buffer = cursor.primeInsert();
	buffer->setValue("id_condicao", condicao->getIdCondicao());
	buffer->setValue("id_opcao", condicao->getIdOpcao());
	buffer->setValue("id_proxima_pergunta", condicao->getIdProximaPergunta());
	buffer->setValue("tp_condicao", condicao->getTipo());

	if (cursor.insert() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_condicao (id_condicao, id_opcao, id_proxima_pergunta, tp_condicao) values (id_condicao.nextval, :opcao, :proxima, :tipo)");
	qry.bindValue(":opcao", condicao->getIdOpcao());
	qry.bindValue(":proxima", condicao->getIdProximaPergunta());
	qry.bindValue(":tipo", condicao->getTipo());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_condicao.currval from dual");
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
	condicao->setIdCondicao(qry.value(0).toUInt());

	if (sql != NULL)
		sql->commit();
	return true;
}

bool CondicaoPSO::updCondicao(OpcaoVO * opcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<opcao->listaCondicoes.count(); index++) {
		if (!updCondicao(opcao->listaCondicoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CondicaoPSO::updCondicao(CondicaoVO * condicao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_condicao");
	if (!cursor.select("id_condicao = " + QString::number(condicao->getIdCondicao()))) {
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
	buffer->setValue("id_opcao", condicao->getIdOpcao());
	buffer->setValue("id_proxima_pergunta", condicao->getIdProximaPergunta());
	buffer->setValue("tp_condicao", condicao->getTipo());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool CondicaoPSO::delCondicao(OpcaoVO * opcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<opcao->listaCondicoes.count(); index++) {
		if (!delCondicao(opcao->listaCondicoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CondicaoPSO::delCondicao(CondicaoVO * condicao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_condicao");
	if (!cursor.select("id_condicao = " + QString::number(condicao->getIdCondicao()))) {
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