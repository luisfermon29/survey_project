#include "RespostaPSO.h"


RespostaPSO::RespostaPSO(QSqlDatabase * sql)
{
	db = sql;
}

bool RespostaPSO::lerRespostaIdCliente(RespostaModel * modelo, uint idCliente)
{
	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(idCliente)))
		return false;

	while (cursor.next()) {
		modelo->insereResposta();
		lerResposta(&cursor, modelo->list.last());
	}

	return true;
}

bool RespostaPSO::lerRespostaIdClientePergunta(RespostaModel * modelo, uint idCliente, uint idPergunta)
{
	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(idCliente) + " and id_opcao in (select tb_pesq_opcao.id_opcao from tb_pesq_opcao, tb_pesq_bloco_opcao where tb_pesq_opcao.id_bloco_opcao = tb_pesq_bloco_opcao.id_bloco_opcao and tb_pesq_bloco_opcao.id_pergunta = " + QString::number(idPergunta) + ")"))
		return false;

	while (cursor.next()) {
		modelo->insereResposta();
		lerResposta(&cursor, modelo->list.last());
	}

	return true;
}

bool RespostaPSO::lerRespostaIdClienteBlocoOpcao(RespostaModel * modelo, uint idCliente, uint idBlocoOpcao)
{
	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(idCliente) + " and id_opcao in (select id_opcao from tb_pesq_opcao where id_bloco_opcao = " + QString::number(idBlocoOpcao) + ")"))
		return false;

	while (cursor.next()) {
		modelo->insereResposta();
		lerResposta(&cursor, modelo->list.last());
	}

	return true;
}

bool RespostaPSO::lerRespostaIdClienteOpcao(RespostaModel * modelo, uint idCliente, uint idOpcao)
{
	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(idCliente) + " and id_opcao = " + QString::number(idOpcao)))
		return false;

	while (cursor.next()) {
		modelo->insereResposta();
		lerResposta(&cursor, modelo->list.last());
	}

	return true;
}

void RespostaPSO::lerResposta(QSqlCursor * cursor, RespostaVO * resposta)
{
	resposta->setIdCliente(cursor->value("id_cliente").toUInt());
	resposta->setIdOpcao(cursor->value("id_opcao").toUInt());
	resposta->setIdOpcaoRelacionada(cursor->value("id_opcao_relacionada").toUInt());
	resposta->setTagSelecionada(cursor->value("sg_tag_selecionada").toString());
	resposta->setTagRelacionada(cursor->value("sg_tag_relacionada_selecionada").toString());
	resposta->setTexto(cursor->value("texto").toString());
}

bool RespostaPSO::grvResposta(RespostaModel * modelo, QSqlDatabase * sql)
{
	int index;

	if (sql != NULL)
		sql->transaction();

	for (index=0; (uint)index<modelo->list.count(); index++) {
		if ((modelo->list.at(index)->getIdOpcao() == 0) || (modelo->list.at(index)->getIdOpcaoRelacionada() == 0)) {
			modelo->list.remove(index);
			index--;
			continue;
		}

		if (!grvResposta(modelo->list.at(index))) {
			if (sql != NULL)
				sql->rollback();

			return false;
		}
	}
	if (sql != NULL)
		sql->commit();

	return true;
}

bool RespostaPSO::grvResposta(RespostaVO * resposta, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry(sql);
	qry.prepare("insert into tb_pesq_respostas (id_cliente, id_opcao, id_opcao_relacionada, sg_tag_selecionada, sg_tag_relacionada_selecionada, texto) values (:cliente, :opcao, :opcaoRelacionada, :tagSelecionada, :tagRelacionada, :texto)");
	qry.bindValue(":cliente", resposta->getIdCliente());
	qry.bindValue(":opcao", resposta->getIdOpcao());
	qry.bindValue(":opcaoRelacionada", resposta->getIdOpcaoRelacionada());
	qry.bindValue(":tagSelecionada", resposta->getTagSelecionada());
	qry.bindValue(":tagRelacionada", resposta->getTagRelacionada());
	qry.bindValue(":texto", resposta->getTexto());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool RespostaPSO::updResposta(RespostaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updResposta(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool RespostaPSO::updResposta(RespostaVO * resposta, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(resposta->getIdCliente()) + " and id_opcao = " + QString::number(resposta->getIdOpcao()))) {
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
	buffer->setValue("id_opcao_relacionada", resposta->getIdOpcaoRelacionada());
	buffer->setValue("sg_tag_selecionada", resposta->getTagSelecionada());
	buffer->setValue("sg_tag_relacionada_selecionada", resposta->getTagRelacionada());
	buffer->setValue("texto", resposta->getTexto());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool RespostaPSO::delResposta(RespostaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delResposta(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool RespostaPSO::delResposta(RespostaVO * resposta, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_respostas");
	if (!cursor.select("id_cliente = " + QString::number(resposta->getIdCliente()) + " and id_opcao = " + QString::number(resposta->getIdOpcao()))) {
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

bool RespostaPSO::delRespostaIdCliente(uint idCliente, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry(sql);
	qry.prepare("delete tb_pesq_respostas where id_cliente = :idCliente");
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