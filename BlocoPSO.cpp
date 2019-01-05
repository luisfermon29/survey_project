#include "BlocoPSO.h"


BlocoPSO::BlocoPSO(QSqlDatabase * sql)
{
	db = sql;

	perguntaPso = new PerguntaPSO(db);
}

BlocoPSO::~BlocoPSO()
{
	delete perguntaPso;
}

bool BlocoPSO::lerBloco(BlocoModel * modelo, bool lerPerguntas, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_bloco");
	if (!cursor.select("id_bloco >= 0 order by id_bloco asc"))
		return false;

	while (cursor.next()) {
		modelo->insereBloco();
		lerBloco(&cursor, modelo->list.last());

		if (lerPerguntas)
			perguntaPso->lerPerguntaIdBloco(modelo->list.last(), modelo->list.last()->getIdBloco(), lerOpcoes);
	}
	return true;
}

bool BlocoPSO::lerBlocoId(BlocoVO * bloco, uint idBloco, bool lerPerguntas, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_bloco");
	if (!cursor.select("id_bloco = " + QString::number(idBloco)))
		return false;

	if (!cursor.next())
		return false;

	lerBloco(&cursor, bloco);

	if (lerPerguntas)
		perguntaPso->lerPerguntaIdBloco(bloco, bloco->getIdBloco(), lerOpcoes);

	return true;
}

void BlocoPSO::lerBloco(QSqlCursor * cursor, BlocoVO * bloco)
{
	bloco->setIdBloco(cursor->value("id_bloco").toUInt());
	bloco->setNome(cursor->value("nm_bloco").toString());
	bloco->setDescricao(cursor->value("ds_bloco").toString());
	bloco->setTipo(cursor->value("tp_bloco").toString());
}

bool BlocoPSO::grvBloco(BlocoModel * modelo, bool grvPerguntas, bool grvOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvBloco(modelo->list.at(index), grvPerguntas, grvOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoPSO::grvBloco(BlocoVO * bloco, bool grvPerguntas, bool grvOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_bloco (id_bloco, nm_bloco, ds_bloco, tp_bloco) values (id_bloco.nextval, :nome, :descricao, :tipo)");
	qry.bindValue(":nome", bloco->getNome());
	qry.bindValue(":descricao", bloco->getDescricao());
	qry.bindValue(":tipo", bloco->getTipo());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_bloco.currval from dual");
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
	bloco->setIdBloco(qry.value(0).toUInt());

	if (grvPerguntas) {
		for (uint i=0; i<bloco->listaPerguntas.count(); i++) {
			bloco->listaPerguntas.at(i)->setIdBloco(bloco->getIdBloco());
			if (!perguntaPso->grvPergunta(bloco->listaPerguntas.at(i), grvOpcoes)) {
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

bool BlocoPSO::updBloco(BlocoModel * modelo, bool updPerguntas, bool updOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updBloco(modelo->list.at(index), updPerguntas, updOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoPSO::updBloco(BlocoVO * bloco, bool updPerguntas, bool updOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_bloco");
	if (!cursor.select("id_bloco = " + QString::number(bloco->getIdBloco()))) {
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
	buffer->setValue("nm_bloco", bloco->getNome());
	buffer->setValue("ds_bloco", bloco->getDescricao());
	buffer->setValue("tp_bloco", bloco->getTipo());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (updPerguntas) {
		for (uint i=0; i<bloco->listaPerguntas.count(); i++) {
			if (!perguntaPso->updPergunta(bloco->listaPerguntas.at(i), updOpcoes)) {
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

bool BlocoPSO::delBloco(BlocoModel * modelo, bool delPerguntas, bool delOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delBloco(modelo->list.at(index), delPerguntas, delOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoPSO::delBloco(BlocoVO * bloco, bool delPerguntas, bool delOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	if (delPerguntas) {
		for (uint i=0; i<bloco->listaPerguntas.count(); i++) {
			if (!perguntaPso->delPergunta(bloco->listaPerguntas.at(i), delOpcoes)) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	QSqlCursor cursor("tb_pesq_bloco");
	if (!cursor.select("id_bloco = " + QString::number(bloco->getIdBloco()))) {
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