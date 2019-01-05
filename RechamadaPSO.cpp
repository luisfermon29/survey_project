#include "RechamadaPSO.h"


RechamadaPSO::RechamadaPSO(QSqlDatabase * sql)
{
	db = sql;
}


bool RechamadaPSO::lerRechamadaId(RechamadaVO * rechamada, uint idRechamada)
{
	QSqlCursor cursor("tb_pesq_agente_rechamada");
	if (!cursor.select("id_agente_rechamada = " + QString::number(idRechamada)))
		return false;

	if (!cursor.next())
		return false;

	lerRechamada(&cursor, rechamada);

	return true;
}

bool RechamadaPSO::lerRechamadaIdLogin(RechamadaVO * rechamada, uint idLogin)
{
	QSqlQuery qry;
//	qry.prepare("select id_agente_rechamada, id_campanha, id_cliente, id_login, dt_rechama, flg_ligacao from tb_pesq_agente_rechamada where flg_ligacao = 0 and dt_rechama <= :atual and to_char(dt_rechama,'dd/mm/yyyy')=to_char(sysdate,'dd/mm/yyyy') and id_cliente not in (select id_cliente from tb_pesq_cliente where dt_contato < (sysdate-10))");
	qry.prepare("select id_agente_rechamada, id_campanha, id_cliente, id_login, dt_rechama, flg_ligacao from tb_pesq_agente_rechamada where flg_ligacao = 0 and dt_rechama <= :atual");
//	qry.bindValue(":idLogin", idLogin);
	qry.bindValue(":atual", QDateTime::currentDateTime());
	if (!qry.exec())
		return false;

	if (!qry.next())
		return false;

	lerRechamada(&qry, rechamada);

	if (db != NULL)
		db->transaction();
	qry.prepare("update tb_pesq_agente_rechamada set flg_ligacao = 1 where id_agente_rechamada = :rechamada");
	qry.bindValue(":rechamada", rechamada->getIdRechamada());
	if (!qry.exec()) {
		if (db != NULL)
			db->rollback();
		return false;
	}

	if (db != NULL)
		db->commit();
	return true;
}


void RechamadaPSO::lerRechamada(QSqlCursor * cursor, RechamadaVO * rechamada)
{
	rechamada->setIdRechamada(cursor->value("id_agente_rechamada").toUInt());
	rechamada->setIdCampanha(cursor->value("id_campanha").toUInt());
	rechamada->setIdCliente(cursor->value("id_cliente").toUInt());
	rechamada->setIdLogin(cursor->value("id_login").toUInt());
	rechamada->setData(cursor->value("dt_rechama").toDateTime());

	bool flag = true;
	if (cursor->value("flg_ligacao").toUInt() == 0)
		flag = false;
	rechamada->setFlagLig(flag);
}
/*
bool RechamadaPSO::lerRetornoIdCliente(RechamadaVO * rechamada)
{
	QSqlQuery qry;
	QString str;

	str		=	"select b.id_cliente, b.id_campanha from";
	str		+=	" (select y.id_cliente, y.id_excecao, y.id_finalizacao from tb_pesq_chamada y, (select id_cliente, max(dt_chamada) dt_max from tb_pesq_chamada where";
	str		+=	" to_char(dt_chamada,'dd/mm/yyyy')=to_char(sysdate,'dd/mm/yyyy') group by id_cliente) z where y.dt_chamada = z.dt_max and y.id_cliente=z.id_cliente and (sysdate-y.dt_chamada)>1/24) a,";
	str		+=	" tb_pesq_cliente b where a.id_cliente=b.id_cliente and b.id_cliente not in (select id_cliente from tb_pesq_chamada where id_finalizacao=1)";
	str		+=	" and a.id_excecao in (1,2,3,7)";

//	qry.prepare("select id_agente_rechamada, id_campanha, id_cliente, id_login, dt_rechama, flg_ligacao from tb_pesq_agente_rechamada where flg_ligacao = 0 and dt_rechama <= :atual");
//	qry.bindValue(":idLogin", idLogin);
//	qry.bindValue(":atual", QDateTime::currentDateTime());

	qry.prepare(str);

	if (!qry.exec())
		return false;

	if (!qry.next())
		return false;

	lerRetorno(&qry, rechamada);
/*
	if (db != NULL)
		db->transaction();
	qry.prepare("update tb_pesq_agente_rechamada set flg_ligacao = 1 where id_agente_rechamada = :rechamada");
	qry.bindValue(":rechamada", rechamada->getIdRechamada());
	if (!qry.exec()) {
		if (db != NULL)
			db->rollback();
		return false;
	}

	if (db != NULL)
		db->commit();
*//*
	return true;
}

void RechamadaPSO::lerRetorno(QSqlQuery * qry, RechamadaVO * rechamada)
{
	rechamada->setIdRechamada(0);
	rechamada->setIdCampanha(qry->value(1).toUInt());
	rechamada->setIdCliente(qry->value(0).toUInt());
	rechamada->setIdLogin(0);
	rechamada->setData(QDateTime::currentDateTime());

	bool flag = true;
	if (qry->value(5).toUInt() == 0)
		flag = false;
	rechamada->setFlagLig(flag);
}
*/
void RechamadaPSO::lerRechamada(QSqlQuery * qry, RechamadaVO * rechamada)
{
	rechamada->setIdRechamada(qry->value(0).toUInt());
	rechamada->setIdCampanha(qry->value(1).toUInt());
	rechamada->setIdCliente(qry->value(2).toUInt());
	rechamada->setIdLogin(qry->value(3).toUInt());
	rechamada->setData(qry->value(4).toDateTime());

	bool flag = true;
	if (qry->value(5).toUInt() == 0)
		flag = false;
	rechamada->setFlagLig(flag);
}

bool RechamadaPSO::grvRechamada(RechamadaVO * rechamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("select id_agente_rechamada from tb_pesq_agente_rechamada where id_cliente = :cliente");
	qry.bindValue(":cliente", rechamada->getIdCliente());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	bool insert = true;
	if (qry.next()) {
		insert = false;
		uint id = qry.value(0).toUInt();
		qry.prepare("update tb_pesq_agente_rechamada set id_campanha = :campanha, id_login = :idLogin, dt_rechama = :dataRech, flg_ligacao = :flagLig where id_agente_rechamada = :idRech");
		qry.bindValue(":idRech", id);
	} else {
		qry.prepare("insert into tb_pesq_agente_rechamada (id_agente_rechamada, id_campanha, id_cliente, id_login, dt_rechama, flg_ligacao) values (id_rechamada.nextval, :campanha, :cliente, :idLogin, :dataRech, :flagLig)");
		qry.bindValue(":cliente", rechamada->getIdCliente());
	}

	qry.bindValue(":campanha", rechamada->getIdCampanha());
	qry.bindValue(":idLogin", rechamada->getIdLogin());
	qry.bindValue(":dataRech", rechamada->getData());
	uint flag = 0;
	if (rechamada->getFlagLig())
		flag = 1;
	qry.bindValue(":flagLig", flag);

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (insert) {
		qry.prepare("select id_rechamada.currval from dual");
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
		rechamada->setIdRechamada(qry.value(0).toUInt());
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool RechamadaPSO::updRechamada(RechamadaVO * rechamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_agente_rechamada");
	if (!cursor.select("id_agente_rechamada = " + QString::number(rechamada->getIdRechamada()))) {
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
	buffer->setValue("id_campanha", rechamada->getIdCampanha());
	buffer->setValue("id_cliente", rechamada->getIdCliente());
	buffer->setValue("id_login", rechamada->getIdLogin());
	buffer->setValue("dt_rechama", rechamada->getData());

	uint flag = 0;
	if (rechamada->getFlagLig())
		flag = 1;
	buffer->setValue("flg_ligacao", flag);

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool RechamadaPSO::delRechamada(RechamadaVO * rechamada, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_agente_rechamada");
	if (!cursor.select("id_agente_rechamada = " + QString::number(rechamada->getIdRechamada()))) {
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

bool RechamadaPSO::updRechamadaIdClienteOn(uint idCliente, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("update tb_pesq_agente_rechamada set flg_ligacao=1 where id_cliente = :cliente");
	qry.bindValue(":cliente",idCliente);

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	
	if (sql != NULL)
		sql->commit();
	return true;
}