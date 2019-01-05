#include "PerguntaPSO.h"


PerguntaPSO::PerguntaPSO(QSqlDatabase * sql)
{
	db = sql;

	blocoOpcaoPso = new BlocoOpcaoPSO(db);
}

PerguntaPSO::~PerguntaPSO()
{
	delete blocoOpcaoPso;
}

bool PerguntaPSO::lerPerguntaId(PerguntaVO * pergunta, uint idPergunta, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_perguntas");
	if (!cursor.select("id_pergunta = " + QString::number(idPergunta)))
		return false;

	if (!cursor.next())
		return false;

	lerPergunta(&cursor, pergunta);

	if (lerOpcoes)
		blocoOpcaoPso->lerBlocoOpcaoIdPergunta(pergunta, pergunta->getIdPergunta());

	return true;
}

bool PerguntaPSO::lerPerguntaIdBloco(PerguntaModel * modelo, uint idBloco, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_perguntas");
	if (!cursor.select("id_bloco = " + QString::number(idBloco) + " order by nu_ordem asc"))
		return false;

	while (cursor.next()) {
		modelo->inserePergunta();
		lerPergunta(&cursor, modelo->list.last());

		if (lerOpcoes)
			blocoOpcaoPso->lerBlocoOpcaoIdPergunta(modelo->list.last(), modelo->list.last()->getIdPergunta(), true);
	}

	return true;
}

bool PerguntaPSO::lerPerguntaIdBloco(BlocoVO * bloco, uint idBloco, bool lerOpcoes)
{
	QSqlCursor cursor("tb_pesq_perguntas");
	if (!cursor.select("id_bloco = " + QString::number(idBloco) + " order by nu_ordem asc"))
		return false;

	while (cursor.next()) {
		bloco->inserePergunta();
		lerPergunta(&cursor, bloco->listaPerguntas.last());

		if (lerOpcoes)
			blocoOpcaoPso->lerBlocoOpcaoIdPergunta(bloco->listaPerguntas.last(), bloco->listaPerguntas.last()->getIdPergunta(), true);
	}

	return true;
}

void PerguntaPSO::lerPergunta(QSqlCursor * cursor, PerguntaVO * pergunta)
{
	pergunta->setIdPergunta(cursor->value("id_pergunta").toUInt());
	pergunta->setIdBloco(cursor->value("id_bloco").toUInt());
	pergunta->setTipo(cursor->value("tp_pergunta").toUInt());
	pergunta->setTextoPergunta(cursor->value("tx_pergunta").toString());
	pergunta->setTextoExplicativo(cursor->value("tx_explicativo").toString());
	pergunta->setOrdem(cursor->value("nu_ordem").toUInt());

	bool flag = true;
	if (cursor->value("flg_texto_antes").toUInt() == 0)
		flag = false;
	pergunta->setTextoAntes(flag);
}

bool PerguntaPSO::grvPergunta(PerguntaModel * modelo, bool grvOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvPergunta(modelo->list.at(index), grvOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::grvPergunta(BlocoVO * bloco, bool grvOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<bloco->listaPerguntas.count(); index++) {
		if (!grvPergunta(bloco->listaPerguntas.at(index), grvOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::grvPergunta(PerguntaVO * pergunta, bool grvOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_perguntas");
	QSqlRecord * buffer = cursor.primeInsert();
	buffer->setValue("id_pergunta", pergunta->getIdPergunta());
	buffer->setValue("id_bloco", pergunta->getIdBloco());
	buffer->setValue("tp_pergunta", pergunta->getTipo());
	buffer->setValue("tx_pergunta", pergunta->getTextoPergunta());
	buffer->setValue("tx_explicativo", pergunta->getTextoExplicativo());
	buffer->setValue("nu_ordem", pergunta->getOrdem());

	uint flag = 0;
	if (pergunta->getTextoAntes())
		flag = 1;
	buffer->setValue("flg_texto_antes", flag);

	if (cursor.insert() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_perguntas (id_pergunta, id_bloco, tp_pergunta, tx_pergunta, tx_explicativo, nu_ordem) values (id_pergunta.nextval, :bloco, :tipo, :texto, :explcativo, :ordem)");
	qry.bindValue(":bloco", pergunta->getIdBloco());
	qry.bindValue(":tipo", pergunta->getTipo());
	qry.bindValue(":texto", pergunta->getTextoPergunta());
	qry.bindValue(":explicativo", pergunta->getTextoExplicativo());
	qry.bindValue(":ordem", pergunta->getOrdem());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_pergunta.currval from dual");
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
	pergunta->setIdPergunta(qry.value(0).toUInt());

	if (grvOpcoes) {
		for (uint i=0; i<pergunta->listaBlocoOpcoes.count(); i++) {
			pergunta->listaBlocoOpcoes.at(i)->setIdPergunta(pergunta->getIdPergunta());
			if (!blocoOpcaoPso->grvBlocoOpcao(pergunta->listaBlocoOpcoes.at(i), true)) {
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

bool PerguntaPSO::updPergunta(PerguntaModel * modelo, bool updOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updPergunta(modelo->list.at(index), updOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::updPergunta(BlocoVO * bloco, bool updOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<bloco->listaPerguntas.count(); index++) {
		if (!updPergunta(bloco->listaPerguntas.at(index), updOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::updPergunta(PerguntaVO * pergunta, bool updOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_perguntas");
	if (!cursor.select("id_pergunta = " + QString::number(pergunta->getIdPergunta()))) {
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
	buffer->setValue("id_bloco", pergunta->getIdBloco());
	buffer->setValue("tp_pergunta", pergunta->getTipo());
	buffer->setValue("tx_pergunta", pergunta->getTextoPergunta());
	buffer->setValue("tx_explicativo", pergunta->getTextoExplicativo());
	buffer->setValue("nu_ordem", pergunta->getOrdem());

	uint flag = 0;
	if (pergunta->getTextoAntes())
		flag = 1;
	buffer->setValue("flg_texto_antes", flag);

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (updOpcoes) {
		for (uint i=0; i<pergunta->listaBlocoOpcoes.count(); i++) {
			if (!blocoOpcaoPso->updBlocoOpcao(pergunta->listaBlocoOpcoes.at(i), true)) {
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

bool PerguntaPSO::delPergunta(PerguntaModel * modelo, bool delOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delPergunta(modelo->list.at(index), delOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::delPergunta(BlocoVO * bloco, bool delOpcoes)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<bloco->listaPerguntas.count(); index++) {
		if (!delPergunta(bloco->listaPerguntas.at(index), delOpcoes)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool PerguntaPSO::delPergunta(PerguntaVO * pergunta, bool delOpcoes, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	if (delOpcoes) {
		for (uint i=0; i<pergunta->listaBlocoOpcoes.count(); i++) {
			if (!blocoOpcaoPso->delBlocoOpcao(pergunta->listaBlocoOpcoes.at(i), true)) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	QSqlCursor cursor("tb_pesq_perguntas");
	if (!cursor.select("id_pergunta = " + QString::number(pergunta->getIdPergunta()))) {
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