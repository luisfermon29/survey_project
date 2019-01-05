#include "OpcaoPSO.h"


#define OPCAO_CAMPOS "tb_pesq_opcao.id_opcao, id_bloco_opcao, tp_opcao, nu_ordem, sg_tag_opcao, tx_explicativo, tb_pesq_opcao_texto.tx_opcao"


OpcaoPSO::OpcaoPSO(QSqlDatabase * sql)
{
	db = sql;

	condicaoPso = new CondicaoPSO(db);
}

OpcaoPSO::~OpcaoPSO()
{
	delete condicaoPso;
}

bool OpcaoPSO::lerOpcaoId(OpcaoVO * opcao, uint idOpcao)
{
	QSqlCursor cursor("tb_pesq_opcao, tb_pesq_opcao_texto");
	if (!cursor.select("tb_pesq_opcao.id_opcao = tb_pesq_opcao_texto.id_opcao and tb_pesq_opcao.id_opcao = " + QString::number(idOpcao)))
		return false;

	if (!cursor.next())
		return false;

	lerOpcaoTexto(&cursor, opcao);
	condicaoPso->lerCondicaoIdOpcao(opcao, opcao->getIdOpcao());

	return true;
}
/*
bool OpcaoPSO::lerOpcaoIdBlocoOpcao(BlocoOpcaoVO * blocoOpcao, uint idBlocoOpcao)
{
	QSqlQuery qry(db);
	QString str = "select ";
	str += OPCAO_CAMPOS;
	str += " from tb_pesq_opcao, tb_pesq_opcao_texto where tb_pesq_opcao.id_opcao = tb_pesq_opcao_texto.id_opcao and id_bloco_opcao = :idBlocoOpcao order by nu_ordem asc";
	qry.prepare(str);
	//qry.bindValue(":campos", OPCAO_CAMPOS);
	qry.bindValue(":idBlocoOpcao", idBlocoOpcao);
	if (!qry.exec())
		return false;

	while (qry.next()) {
		blocoOpcao->insereOpcao();
		lerOpcaoTexto(&qry, blocoOpcao->listaOpcoes.last());
		condicaoPso->lerCondicaoIdOpcao(blocoOpcao->listaOpcoes.last(), blocoOpcao->listaOpcoes.last()->getIdOpcao());
	}

	return true;
}
*/
bool OpcaoPSO::lerOpcaoIdBlocoOpcao(BlocoOpcaoVO * blocoOpcao, uint idBlocoOpcao)
{
/*	QSqlQuery qry(db);
	QString str = "select ";
	str += OPCAO_CAMPOS;
	str += " from tb_pesq_opcao, tb_pesq_opcao_texto where tb_pesq_opcao.id_opcao = tb_pesq_opcao_texto.id_opcao and id_bloco_opcao = :idBlocoOpcao order by nu_ordem asc";
	qry.prepare(str);
	//qry.bindValue(":campos", OPCAO_CAMPOS);
	qry.bindValue(":idBlocoOpcao", idBlocoOpcao);
	if (!qry.exec())
		return false;

	QPtrList<OpcaoVO> lista;
	QPtrList<OpcaoVO> perg5;
	lista.setAutoDelete(false);
	uint ordem = 0;
	uint lc = 0;

	while (qry.next()) {
		lista.append(new OpcaoVO);
		lerOpcaoTexto(&qry, lista.last());
		condicaoPso->lerCondicaoIdOpcao(lista.last(), lista.last()->getIdOpcao());
		ordem += lista.last()->getOrdem();
	}
	QTime hora = QTime::currentTime();
	srand(hora.second() + hora.msec());
	uint pos = 0, index = 1;
	
	
	lc = lista.count();
	if (idBlocoOpcao == 13){
		ordem = 0;
		lc = lista.count() - 1;
		perg5.append(lista.at(6));
	}

	while (lc > 0) {
		if (ordem == 0) { // rodiziar opções
			pos = rand() % lc;
			lista.at(pos)->setTag(QString::number(index++));
		}
		blocoOpcao->listaOpcoes.append(lista.at(pos));
		lista.remove(pos);

		if (idBlocoOpcao == 13){
			lc = lista.count() - 1;
			ordem = 0;
		}else
			lc = lista.count();
	}
	if (idBlocoOpcao == 13)
			blocoOpcao->listaOpcoes.append(perg5.at(0));

////	while (qry.next()) {
////		blocoOpcao->insereOpcao();
////		lerOpcaoTexto(&qry, blocoOpcao->listaOpcoes.last());
////		condicaoPso->lerCondicaoIdOpcao(blocoOpcao->listaOpcoes.last(), blocoOpcao->listaOpcoes.last()->getIdOpcao());
////	}

	return true;
*/

	QSqlQuery qry(db);
	QString str = "select ";
	str += OPCAO_CAMPOS;
	str += " from tb_pesq_opcao, tb_pesq_opcao_texto where tb_pesq_opcao.id_opcao = tb_pesq_opcao_texto.id_opcao and id_bloco_opcao = :idBlocoOpcao order by nu_ordem asc";
	qry.prepare(str);
	//qry.bindValue(":campos", OPCAO_CAMPOS);
	qry.bindValue(":idBlocoOpcao", idBlocoOpcao);
	if (!qry.exec())
		return false;
	QPtrList<OpcaoVO> lista;
	lista.setAutoDelete(false);
	uint ordem = 0;

	while (qry.next()) {
		lista.append(new OpcaoVO);
		lerOpcaoTexto(&qry, lista.last());
		condicaoPso->lerCondicaoIdOpcao(lista.last(), lista.last()->getIdOpcao());
		ordem += lista.last()->getOrdem();
	}
	QTime hora = QTime::currentTime();
	srand(hora.second() + hora.msec());
	uint pos = 0, index = 1;
	while (lista.count() > 0) {
		if (ordem == 0) { // rodiziar opções
			pos = rand() % lista.count();
			lista.at(pos)->setTag(QString::number(index++));
		}
		blocoOpcao->listaOpcoes.append(lista.at(pos));
		lista.remove(pos);
	}

	return true;

}

bool OpcaoPSO::lerOpcaoIdBlocoOpcao(OpcaoModel * modelo, uint idBlocoOpcao)
{
	QSqlCursor cursor("tb_pesq_opcao, tb_pesq_opcao_texto");
	if (!cursor.select("tb_pesq_opcao.id_opcao = tb_pesq_opcao_texto.id_opcao and id_bloco_opcao = " + QString::number(idBlocoOpcao) + " order by nu_ordem asc"))
		return false;

	while (cursor.next()) {
		modelo->insereOpcao();
		lerOpcaoTexto(&cursor, modelo->list.last());
		condicaoPso->lerCondicaoIdOpcao(modelo->list.last(), modelo->list.last()->getIdOpcao());
	}

	return true;
}

void OpcaoPSO::lerOpcao(QSqlCursor * cursor, OpcaoVO * opcao)
{
	opcao->setIdOpcao(cursor->value("id_opcao").toUInt());
	opcao->setIdBlocoOpcao(cursor->value("id_bloco_opcao").toUInt());
	opcao->setTipo(cursor->value("tp_opcao").toUInt());
	opcao->setOrdem(cursor->value("nu_ordem").toUInt());
	opcao->setTag(cursor->value("sg_tag_opcao").toString());
	opcao->setTextoExplicativo(cursor->value("tx_explicativo").toString());
}

void OpcaoPSO::lerOpcaoTexto(QSqlQuery * qry, OpcaoVO * opcao)
{
	if (qry == NULL)
		return;
	opcao->setIdOpcao(qry->value(0).toUInt());
	opcao->setIdBlocoOpcao(qry->value(1).toUInt());
	opcao->setTipo(qry->value(2).toUInt());
	opcao->setOrdem(qry->value(3).toUInt());
	opcao->setTag(qry->value(4).toString());
	opcao->setTextoExplicativo(qry->value(5).toString());
	opcao->setTexto(qry->value(6).toString());
}

bool OpcaoPSO::grvOpcao(BlocoOpcaoVO * blocoOpcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<blocoOpcao->listaOpcoes.count(); index++) {
		if (!grvOpcao(blocoOpcao->listaOpcoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::grvOpcao(OpcaoModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvOpcao(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::grvOpcao(OpcaoVO * opcao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_opcao");
	QSqlRecord * buffer = cursor.primeInsert();
	buffer->setValue("id_opcao", opcao->getIdOpcao());
	buffer->setValue("id_bloco_opcao", opcao->getIdBlocoOpcao());
	buffer->setValue("tp_opcao", opcao->getTipo());
	buffer->setValue("nu_ordem", opcao->getOrdem());
	buffer->setValue("sg_tag_opcao", opcao->getTag());
	buffer->setValue("tx_explicativo", opcao->getTextoExplicativo());

	if (cursor.insert() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_opcao (id_opcao, id_bloco_opcao, tp_opcao, nu_ordem, sg_tag_opcao, tx_explicativo) values (id_opcao.nextval, :bloco, :tipo, :ordem, :tag, :texto)");
	qry.bindValue(":bloco", opcao->getIdBlocoOpcao());
	qry.bindValue(":tipo", opcao->getTipo());
	qry.bindValue(":ordem", opcao->getOrdem());
	qry.bindValue(":tag", opcao->getTag());
	qry.bindValue(":texto", opcao->getTextoExplicativo());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_opcao.currval from dual");
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
	opcao->setIdOpcao(qry.value(0).toUInt());

	for (uint i=0; i<opcao->listaCondicoes.count(); i++) {
		opcao->listaCondicoes.at(i)->setIdOpcao(opcao->getIdOpcao());
		if (!condicaoPso->grvCondicao(opcao->listaCondicoes.at(i))) {
			if (sql != NULL)
				sql->rollback();

			return false;
		}
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool OpcaoPSO::updOpcao(BlocoOpcaoVO * blocoOpcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<blocoOpcao->listaOpcoes.count(); index++) {
		if (!updOpcao(blocoOpcao->listaOpcoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::updOpcao(OpcaoModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updOpcao(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::updOpcao(OpcaoVO * opcao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_opcao");
	if (!cursor.select("id_opcao = " + QString::number(opcao->getIdOpcao()))) {
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
	buffer->setValue("id_bloco_opcao", opcao->getIdBlocoOpcao());
	buffer->setValue("tp_opcao", opcao->getTipo());
	buffer->setValue("nu_ordem", opcao->getOrdem());
	buffer->setValue("sg_tag_opcao", opcao->getTag());
	buffer->setValue("tx_explicativo", opcao->getTextoExplicativo());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	for (uint i=0; i<opcao->listaCondicoes.count(); i++) {
		if (!condicaoPso->updCondicao(opcao->listaCondicoes.at(i))) {
			if (sql != NULL)
				sql->rollback();

			return false;
		}
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool OpcaoPSO::delOpcao(BlocoOpcaoVO * blocoOpcao)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<blocoOpcao->listaOpcoes.count(); index++) {
		if (!delOpcao(blocoOpcao->listaOpcoes.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::delOpcao(OpcaoModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delOpcao(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool OpcaoPSO::delOpcao(OpcaoVO * opcao, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	for (uint i=0; i<opcao->listaCondicoes.count(); i++) {
		if (!condicaoPso->delCondicao(opcao->listaCondicoes.at(i))) {
			if (sql != NULL)
				sql->rollback();

			return false;
		}
	}

	QSqlCursor cursor("tb_pesq_opcao");
	if (!cursor.select("id_opcao = " + QString::number(opcao->getIdOpcao()))) {
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