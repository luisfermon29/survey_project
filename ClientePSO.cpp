#include "ClientePSO.h"


ClientePSO::ClientePSO(QSqlDatabase * sql)
{
	db = sql;

	telefonePso = new TelefonePSO(db);
}

ClientePSO::~ClientePSO()
{
	delete telefonePso;
}


bool ClientePSO::lerClienteId(ClienteVO * cliente, uint idCliente, bool lerTelefones)
{
	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("id_cliente = " + QString::number(idCliente)))
		return false;

	if (!cursor.next())
		return false;

	lerCliente(&cursor, cliente);

	if (lerTelefones)
		telefonePso->lerTelefoneIdCliente(cliente, cliente->getIdCliente());

	return true;
}

bool ClientePSO::lerClienteIdSegmento(ClienteModel * modelo, uint idSegmento, bool lerTelefones)
{
	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("id_segmento = " + QString::number(idSegmento)))
		return false;

	while (cursor.next()) {
		modelo->insereCliente();
		lerCliente(&cursor, modelo->list.last());

		if (lerTelefones)
			telefonePso->lerTelefoneIdCliente(modelo->list.last(), modelo->list.last()->getIdCliente());
	}

	return true;
}

bool ClientePSO::lerClienteNome(ClienteModel * modelo, QString nome, bool lerTelefones)
{
	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("nm_cliente like '%" + nome + "%'"))
		return false;

	while (cursor.next()) {
		modelo->insereCliente();
		lerCliente(&cursor, modelo->list.last());

		if (lerTelefones)
			telefonePso->lerTelefoneIdCliente(modelo->list.last(), modelo->list.last()->getIdCliente());
	}

	return true;
}

bool ClientePSO::lerClienteTelefone(ClienteModel * modelo, uint telefone, bool lerTelefones)
{
	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("id_cliente in (select id_cliente from tb_pesq_telefone where nu_telefone = " + QString::number(telefone) + ")"))
		return false;

	while (cursor.next()) {
		modelo->insereCliente();
		lerCliente(&cursor, modelo->list.last());

		if (lerTelefones)
			telefonePso->lerTelefoneIdCliente(modelo->list.last(), modelo->list.last()->getIdCliente());
	}

	return true;
}

void ClientePSO::lerCliente(QSqlCursor * cursor, ClienteVO * cliente)
{
	cliente->setIdCliente(cursor->value("id_cliente").toUInt());
	cliente->setIdSegmento(cursor->value("id_segmento").toUInt());
	cliente->setNomeCliente(cursor->value("nm_cliente").toString());
	cliente->setIdCampanha(cursor->value("id_campanha").toUInt());
	cliente->setSite(cursor->value("site").toString());
	cliente->setDataContato(cursor->value("dt_contato").toDate());
	cliente->setAgente(cursor->value("cnpj").toString());
	cliente->setSupervisor(cursor->value("posse_produto").toString());
	cliente->setSolicitacao(cursor->value("tipo_solicitacao").toString());
	cliente->setDataFechamento(cursor->value("dt_fechamento").toDate());
	cliente->setCategoria(cursor->value("seg_aten").toString());
	cliente->setPrePos(cursor->value("pre_pos").toString());
	cliente->setSegmento(cursor->value("seg_att").toString());
	cliente->setRegiao(cursor->value("regiao").toString());
	cliente->setEstado(cursor->value("contato").toString());
	cliente->setExtra(cursor->value("cidade").toString());
	cliente->setObs(cursor->value("obs").toString());

	cliente->setExtra1(cursor->value("extra1").toString());
	cliente->setExtra2(cursor->value("extra2").toString());
	cliente->setExtra3(cursor->value("extra3").toString());
	cliente->setExtra4(cursor->value("extra4").toString());
	cliente->setExtra5(cursor->value("extra5").toString());
	cliente->setExtra6(cursor->value("extra6").toString());

	cliente->setExtra20(cursor->value("extra20").toString());
	cliente->setExtra21(cursor->value("extra21").toString());
	cliente->setExtra22(cursor->value("extra22").toString());
	cliente->setExtra23(cursor->value("extra23").toString());
	cliente->setExtra24(cursor->value("extra24").toString());
	cliente->setExtra25(cursor->value("extra25").toString());
	cliente->setExtra26(cursor->value("extra26").toString());
	cliente->setExtra27(cursor->value("extra27").toString());
	cliente->setExtra28(cursor->value("extra28").toString());
	cliente->setExtra29(cursor->value("extra29").toString());
}

bool ClientePSO::grvCliente(ClienteModel * modelo, bool grvTelefones)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvCliente(modelo->list.at(index), grvTelefones)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ClientePSO::grvCliente(ClienteVO * cliente, bool grvTelefones, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	QString str = "insert into tb_pesq_cliente (id_cliente, ";
	if (cliente->getIdSegmento() != 0)
		str += "id_segmento, ";
	str += "nm_cliente, id_campanha, site, dt_contato, cnpj, posse_produto, seg_aten, seg_att, pre_pos, tipo_solicitacao, regiao, contato) values (id_cliente.nextval, ";
	if (cliente->getIdSegmento() != 0)
		str += ":idSegmento, ";
	str += ":nome, :campanha, :site, :contato, :posse, :estado, :categoria, :segmento, :prepos, :solicitacao, :regiao, :cont)";

	qry.prepare(str);
	if (cliente->getIdSegmento() != 0)
		qry.bindValue(":idSegmento", cliente->getIdSegmento());
	qry.bindValue(":nome", cliente->getNomeCliente());
	qry.bindValue(":campanha", cliente->getIdCampanha());
	qry.bindValue(":site", cliente->getSite());
	qry.bindValue(":contato", cliente->getDataContato());
	qry.bindValue(":posse", cliente->getAgente());
	qry.bindValue(":estado", cliente->getSupervisor());
	qry.bindValue(":categoria", cliente->getCategoria());
	qry.bindValue(":segmento", cliente->getSegmento());
	qry.bindValue(":prepos", cliente->getPrePos());
	qry.bindValue(":solicitacao", cliente->getSolicitacao());
	qry.bindValue(":regiao", cliente->getRegiao());
	qry.bindValue(":cont", cliente->getEstado());

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_cliente.currval from dual");
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
	cliente->setIdCliente(qry.value(0).toUInt());

	if (grvTelefones) {
		for (uint i=0; i<cliente->listaTel.count(); i++) {
			cliente->listaTel.at(i)->setIdCliente(cliente->getIdCliente());
			if (!telefonePso->grvTelefone(cliente->listaTel.at(i))) {
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

bool ClientePSO::updCliente(ClienteModel * modelo, bool updTelefones)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updCliente(modelo->list.at(index), updTelefones)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ClientePSO::updCliente(ClienteVO * cliente, bool updTelefones, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("id_cliente = " + QString::number(cliente->getIdCliente()))) {
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
//	if (cliente->getIdSegmento() != 0)
//		buffer->setValue("id_segmento", cliente->getIdSegmento());
//	buffer->setValue("nm_cliente", cliente->getNomeCliente());
//	buffer->setValue("id_campanha", cliente->getIdCampanha());
//	buffer->setValue("site", cliente->getSite());
//	buffer->setValue("dt_contato", cliente->getDataContato());
//	buffer->setValue("nm_agente", cliente->getAgente());
//	buffer->setValue("cod_supervisor", cliente->getSupervisor());
//	buffer->setValue("tipo_solicitacao", cliente->getSolicitacao());
//	buffer->setValue("dt_fechamento", cliente->getDataFechamento());
//	buffer->setValue("categoria", cliente->getCategoria());
//	buffer->setValue("pre_pos", cliente->getPrePos());
//	buffer->setValue("segmento", cliente->getSegmento());
	buffer->setValue("obs", cliente->getObs());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (updTelefones) {
		for (uint i=0; i<cliente->listaTel.count(); i++) {
			if (!telefonePso->updTelefone(cliente->listaTel.at(i))) {
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

bool ClientePSO::delCliente(ClienteModel * modelo, bool delTelefones)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delCliente(modelo->list.at(index), delTelefones)) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ClientePSO::delCliente(ClienteVO * cliente, bool delTelefones, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	if (delTelefones) {
		for (uint i=0; i<cliente->listaTel.count(); i++) {
			if (!telefonePso->delTelefone(cliente->listaTel.at(i))) {
				if (sql != NULL)
					sql->rollback();

				return false;
			}
		}
	}

	QSqlCursor cursor("tb_pesq_cliente");
	if (!cursor.select("id_cliente = " + QString::number(cliente->getIdCliente()))) {
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