#include "CampanhaPSO.h"


CampanhaPSO::CampanhaPSO(QSqlDatabase * sql)
{
	db = sql;
}

bool CampanhaPSO::lerCampanha(CampanhaModel * modelo)
{
	QSqlCursor cursor("tb_pesq_campanha");
	if (!cursor.select())
		return false;

	while (cursor.next()) {
		modelo->insereCampanha();
		lerCampanha(&cursor, modelo->list.last());
	}

	return true;
}

bool CampanhaPSO::lerCampanhaId(CampanhaVO * campanha, uint idCampanha)
{
	QSqlCursor cursor("tb_pesq_campanha");
	if (!cursor.select("id_campanha = " + QString::number(idCampanha)))
		return false;

	if (!cursor.next())
		return false;

	lerCampanha(&cursor, campanha);

	return true;
}

void CampanhaPSO::lerCampanha(QSqlCursor * cursor, CampanhaVO * campanha)
{
	campanha->setIdCampanha(cursor->value("id_campanha").toUInt());
	campanha->setIdTipoCampanha(cursor->value("id_tipo_campanha").toUInt());
	campanha->setDescricao(cursor->value("ds_campanha").toString());
	campanha->setCaminhoScript(cursor->value("ds_caminho_script").toString());
	campanha->setDataInicio(cursor->value("dt_inicio_campanha").toDate());
	campanha->setDataTermino(cursor->value("dt_termino_campanha").toDate());
}

bool CampanhaPSO::grvCampanha(CampanhaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvCampanha(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CampanhaPSO::grvCampanha(CampanhaVO * campanha, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_campanha (id_campanha, id_tipo_campanha, ds_campanha, ds_caminho_script, dt_inicio_campanha, dt_termino_campanha) values (id_campanha.nextval, :tipo, :descricao, :caminho, :inicio, :termino)");
	qry.bindValue(":tipo", campanha->getIdTipoCampanha());
	qry.bindValue(":descricao", campanha->getDescricao());
	qry.bindValue(":caminho", campanha->getCaminhoScript());
	qry.bindValue(":inicio", campanha->getDataInicio());
	qry.bindValue(":termino", campanha->getDataTermino());
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	qry.prepare("select id_campanha.currval from dual");
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
	campanha->setIdCampanha(qry.value(0).toUInt());

	if (sql != NULL)
		sql->commit();
	return true;
}

bool CampanhaPSO::updCampanha(CampanhaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updCampanha(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CampanhaPSO::updCampanha(CampanhaVO * campanha, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_campanha");
	if (!cursor.select("id_campanha = " + QString::number(campanha->getIdCampanha()))) {
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
	buffer->setValue("id_tipo_campanha", campanha->getIdTipoCampanha());
	buffer->setValue("ds_campanha", campanha->getDescricao());
	buffer->setValue("ds_caminho_script", campanha->getCaminhoScript());
	buffer->setValue("dt_inicio_campanha", campanha->getDataInicio());
	buffer->setValue("dt_termino_campanha", campanha->getDataTermino());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool CampanhaPSO::delCampanha(CampanhaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delCampanha(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool CampanhaPSO::delCampanha(CampanhaVO * campanha, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_campanha");
	if (!cursor.select("id_campanha = " + QString::number(campanha->getIdCampanha()))) {
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