#include "BlocoOpcaoPSO.h"


BlocoOpcaoPSO::BlocoOpcaoPSO(QSqlDatabase * sql)
{
	db = sql;

	opcaoPso = new OpcaoPSO(db);
}

BlocoOpcaoPSO::~BlocoOpcaoPSO()
{
	if (opcaoPso != NULL)
		delete opcaoPso;
}

bool BlocoOpcaoPSO::lerBlocoOpcaoIdPergunta(BlocoOpcaoModel * modelo, uint idPergunta, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_bloco_opcao");
	if (!cursor.select("id_pergunta = " + QString::number(idPergunta)))
		return false;

	while (cursor.next()) {
		modelo->insereBlocoOpcao();
		lerBlocoOpcao(&cursor, modelo->list.last());

		if (lerOpcoes)
			opcaoPso->lerOpcaoIdBlocoOpcao(modelo->list.last(), modelo->list.last()->getIdBlocoOpcao());
	}
	return true;
}

bool BlocoOpcaoPSO::lerBlocoOpcaoIdPergunta(PerguntaVO * pergunta, uint idPergunta, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_bloco_opcao");
	if (!cursor.select("id_pergunta = " + QString::number(idPergunta)))
		return false;

	while (cursor.next()) {
		pergunta->insereBlocoOpcao();
		lerBlocoOpcao(&cursor, pergunta->listaBlocoOpcoes.last());

		if (lerOpcoes)
			opcaoPso->lerOpcaoIdBlocoOpcao(pergunta->listaBlocoOpcoes.last(), pergunta->listaBlocoOpcoes.last()->getIdBlocoOpcao());
	}
	return true;
}

bool BlocoOpcaoPSO::lerBlocoOpcaoId(BlocoOpcaoVO * blocoOpcao, uint idBlocoOpcao, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_bloco_opcao");
	if (!cursor.select("id_bloco_opcao = " + QString::number(idBlocoOpcao)))
		return false;

	if (!cursor.next())
		return false;

	lerBlocoOpcao(&cursor, blocoOpcao);

	if (lerOpcoes)
		opcaoPso->lerOpcaoIdBlocoOpcao(blocoOpcao, blocoOpcao->getIdBlocoOpcao());

	return true;
}

void BlocoOpcaoPSO::lerBlocoOpcao(QSqlCursor * cursor, BlocoOpcaoVO * blocoOpcao)
{
	blocoOpcao->setIdBlocoOpcao(cursor->value("id_bloco_opcao").toUInt());
	blocoOpcao->setIdPergunta(cursor->value("id_pergunta").toUInt());
	blocoOpcao->setNome(cursor->value("nm_bloco_opcao").toString());
}

bool BlocoOpcaoPSO::grvBlocoOpcao(BlocoOpcaoModel * modelo, bool grvOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvBlocoOpcao(modelo->list.at(index), grvOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::grvBlocoOpcao(PerguntaVO * pergunta, bool grvOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<pergunta->listaBlocoOpcoes.count(); index++) {
		if (!grvBlocoOpcao(pergunta->listaBlocoOpcoes.at(index), grvOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::grvBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool grvOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_bloco_opcao (id_bloco_opcao, id_pergunta, nm_bloco_opcao) values (id_bloco_opcao.nextval, :pergunta, :nome)");
	qry.bindValue(":pergunta", blocoOpcao->getIdPergunta());
	qry.bindValue(":nome", blocoOpcao->getNome());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_bloco_opcao.currval from dual");
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
	blocoOpcao->setIdBlocoOpcao(qry.value(0).toUInt());

	if (grvOpcoes) {
		for (uint i=0; i<blocoOpcao->listaOpcoes.count(); i++) {
			blocoOpcao->listaOpcoes.at(i)->setIdBlocoOpcao(blocoOpcao->getIdBlocoOpcao());
			if (!opcaoPso->grvOpcao(blocoOpcao->listaOpcoes.at(i))) {
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

bool BlocoOpcaoPSO::updBlocoOpcao(BlocoOpcaoModel * modelo, bool updOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updBlocoOpcao(modelo->list.at(index), updOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::updBlocoOpcao(PerguntaVO * pergunta, bool updOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<pergunta->listaBlocoOpcoes.count(); index++) {
		if (!updBlocoOpcao(pergunta->listaBlocoOpcoes.at(index), updOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::updBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool updOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_bloco_opcao");
	if (!cursor.select("id_bloco_opcao = " + QString::number(blocoOpcao->getIdBlocoOpcao()))) {
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
	buffer->setValue("id_pergunta", blocoOpcao->getIdPergunta());
	buffer->setValue("nm_bloco_opcao", blocoOpcao->getNome());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (updOpcoes) {
		for (uint i=0; i<blocoOpcao->listaOpcoes.count(); i++) {
			if (!opcaoPso->updOpcao(blocoOpcao->listaOpcoes.at(i))) {
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

bool BlocoOpcaoPSO::delBlocoOpcao(BlocoOpcaoModel * modelo, bool delOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delBlocoOpcao(modelo->list.at(index), delOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::delBlocoOpcao(PerguntaVO * pergunta, bool delOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<pergunta->listaBlocoOpcoes.count(); index++) {
		if (!delBlocoOpcao(pergunta->listaBlocoOpcoes.at(index), delOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool BlocoOpcaoPSO::delBlocoOpcao(BlocoOpcaoVO * blocoOpcao, bool delOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	if (delOpcoes) {
		for (uint i=0; i<blocoOpcao->listaOpcoes.count(); i++) {
			if (!opcaoPso->delOpcao(blocoOpcao->listaOpcoes.at(i))) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	QSqlCursor cursor("tb_pesq_bloco_opcao");
	if (!cursor.select("id_bloco_opcao = " + QString::number(blocoOpcao->getIdBlocoOpcao()))) {
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