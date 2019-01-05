#include "ChamadaPSO.h"


ChamadaPSO::ChamadaPSO(QSqlDatabase * sql)
{
	db = sql;
}


bool ChamadaPSO::lerChamadaId(ChamadaVO * chamada, uint idChamada)
{
	QSqlCursor cursor("tb_pesq_chamada");
	if (!cursor.select("id_chamada = " + QString::number(idChamada)))
		return false;

	if (!cursor.next())
		return false;

	lerChamada(&cursor, chamada);

	return true;
}

bool ChamadaPSO::lerChamadaIdCliente(ChamadaModel * modelo, uint idCliente)
{
	QSqlCursor cursor("tb_pesq_chamada");
	if (!cursor.select("id_cliente = " + QString::number(idCliente)))
		return false;

	while (cursor.next()) {
		modelo->insereChamada();
		lerChamada(&cursor, modelo->list.last());
	}

	return true;
}

void ChamadaPSO::lerChamada(QSqlCursor * cursor, ChamadaVO * chamada)
{
	chamada->setIdChamada(cursor->value("id_chamada").toUInt());
	chamada->setIdFinalizacao(cursor->value("id_finalizacao").toInt());
	chamada->setIdExcecao(cursor->value("id_excecao").toInt());
	chamada->setIdCampanha(cursor->value("id_campanha").toUInt());
	chamada->setIdCliente(cursor->value("id_cliente").toUInt());
	chamada->setTelefone(cursor->value("nu_telefone").toUInt());
	chamada->setRamal(cursor->value("nu_ramal").toUInt());
	chamada->setData(cursor->value("dt_chamada").toDateTime());
	chamada->setIdLogin(cursor->value("id_login").toUInt());
	chamada->setDuracao(cursor->value("nu_duracao_chamada").toUInt());
}

bool ChamadaPSO::grvChamada(ChamadaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvChamada(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ChamadaPSO::grvChamada(ChamadaVO * chamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	QString str = "insert into tb_pesq_chamada (id_chamada, ";
	if (chamada->getIdFinalizacao() != -1)
		str += "id_finalizacao";
	else
		str += "id_excecao";
	
	str += ", id_campanha, id_cliente, nu_telefone, nu_ramal, dt_chamada, id_login, nu_duracao_chamada) values (id_chamada.nextval, :finalizacao, :campanha, :cliente, :telefone, :ramal, :dataChamada, :idLogin, :duracao)";
	qry.prepare(str);

	if (chamada->getIdFinalizacao() != -1)
		qry.bindValue(":finalizacao", chamada->getIdFinalizacao());
	else
		qry.bindValue(":finalizacao", chamada->getIdExcecao());

	qry.bindValue(":campanha", chamada->getIdCampanha());
	qry.bindValue(":cliente", chamada->getIdCliente());
	qry.bindValue(":telefone", chamada->getTelefone());
	qry.bindValue(":ramal", chamada->getRamal());
	qry.bindValue(":dataChamada", chamada->getData());
	qry.bindValue(":idLogin", chamada->getIdLogin());
	qry.bindValue(":duracao", chamada->getDuracao());

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_chamada.currval from dual");
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
	chamada->setIdChamada(qry.value(0).toUInt());

	if (sql != NULL)
		sql->commit();
	return true;
}

bool ChamadaPSO::updChamada(ChamadaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updChamada(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ChamadaPSO::updChamada(ChamadaVO * chamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_chamada");
	if (!cursor.select("id_chamada = " + QString::number(chamada->getIdChamada()))) {
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
	buffer->setValue("id_finalizacao", chamada->getIdFinalizacao());
	buffer->setValue("id_excecao", chamada->getIdExcecao());
	buffer->setValue("id_campanha", chamada->getIdCampanha());
	buffer->setValue("id_cliente", chamada->getIdCliente());
	buffer->setValue("nu_telefone", chamada->getTelefone());
	buffer->setValue("nu_ramal", chamada->getRamal());
	buffer->setValue("dt_chamada", chamada->getData());
	buffer->setValue("id_login", chamada->getIdLogin());
	buffer->setValue("nu_duracao_chamada", chamada->getDuracao());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool ChamadaPSO::delChamada(ChamadaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delChamada(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ChamadaPSO::delChamada(ChamadaVO * chamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_chamada");
	if (!cursor.select("id_chamada = " + QString::number(chamada->getIdChamada()))) {
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

int ChamadaPSO::verificaChamadaIdCliente(uint idCliente)
{
	QSqlQuery qry;
	qry.prepare("select count(*) from tb_pesq_chamada where id_cliente = :cliente");
	qry.bindValue(":cliente", idCliente);
	if (!qry.exec())
		return -1;
	if (!qry.next())
		return -2;
	return qry.value(0).toUInt();
}

bool ChamadaPSO::lerFinalizacaoChamada(FinalizacaoChamadaModel * modelo)
{
	QSqlCursor cursor("tb_pesq_finalizacao_chamada");
	if (!cursor.select())
		return false;

	while (cursor.next()) {
		modelo->insereFinalizacaoChamada();
		modelo->list.last()->setIdFinalizacao(cursor.value("id_finalizacao").toInt());
		modelo->list.last()->setIdCampanha(cursor.value("id_campanha").toUInt());
		modelo->list.last()->setNome(cursor.value("nm_motivo_finalizacao").toString());
		modelo->list.last()->setDescricao(cursor.value("ds_motivo_finalizacao").toString());
	}
	return true;
}

bool ChamadaPSO::lerExcecaoChamada(ExcecaoChamadaModel * modelo)
{
	QSqlQuery qry;
	qry.prepare("select tb_pesq_excecao_chamada.id_excecao, id_campanha, nm_excecao, ds_excecao, qt_limite_chamadas from tb_pesq_tipo_terminacao, tb_pesq_excecao_chamada where tb_pesq_tipo_terminacao.id_excecao = tb_pesq_excecao_chamada.id_excecao");
	if (!qry.exec())
		return false;

	while (qry.next()) {
		modelo->insereExcecaoChamada();
		modelo->list.last()->setIdExcecao(qry.value(0).toInt());
		modelo->list.last()->setIdCampanha(qry.value(1).toUInt());
		modelo->list.last()->setNome(qry.value(2).toString());
		modelo->list.last()->setDescricao(qry.value(3).toString());
		modelo->list.last()->setQtLimiteChamadas(qry.value(4).toUInt());
	}
	return true;
}

bool ChamadaPSO::lerExcecaoChamadaIdCampanha(ExcecaoChamadaModel * modelo, uint idCampanha)
{
	QSqlQuery qry;
	qry.prepare("select tb_pesq_excecao_chamada.id_excecao, id_campanha, nm_excecao, ds_excecao, qt_limite_chamadas from tb_pesq_tipo_terminacao, tb_pesq_excecao_chamada where tb_pesq_tipo_terminacao.id_excecao = tb_pesq_excecao_chamada.id_excecao and id_campanha = :campanha");
	qry.bindValue(":campanha", idCampanha);
	if (!qry.exec())
		return false;

	while (qry.next()) {
		modelo->insereExcecaoChamada();
		modelo->list.last()->setIdExcecao(qry.value(0).toInt());
		modelo->list.last()->setIdCampanha(qry.value(1).toUInt());
		modelo->list.last()->setNome(qry.value(2).toString());
		modelo->list.last()->setDescricao(qry.value(3).toString());
		modelo->list.last()->setQtLimiteChamadas(qry.value(4).toUInt());
	}
	return true;
}