#include "QuotaPSO.h"


QuotaPSO::QuotaPSO(QSqlDatabase * sql)
{
	db = sql;
}

bool QuotaPSO::lerQuotaIdCampanha(QuotaModel * modelo, uint idCampanha)
{
	QSqlCursor cursor("tb_pesq_quota");
	if (!cursor.select("id_campanha = " + QString::number(idCampanha)))
		return false;

	while (cursor.next()) {
		modelo->insereQuota();
		lerQuota(&cursor, modelo->list.last());
	}

	return true;
}

bool QuotaPSO::lerQuotaIdCampanhaSite(QuotaVO * quota, uint idCampanha, QString site)
{
	QSqlCursor cursor("tb_pesq_quota");
	if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and site = '" + site + "'"))
		return false;

	if (!cursor.next())
		return false;

	lerQuota(&cursor, quota);

	return true;
}

void QuotaPSO::lerQuota(QSqlCursor * cursor, QuotaVO * quota)
{
	quota->setIdCampanha(cursor->value("id_campanha").toUInt());
	quota->setSite(cursor->value("site").toString());
	quota->setQuotaMax(cursor->value("quota_max").toUInt());
	quota->setQuotaAtual(cursor->value("quota_atual").toUInt());
}

bool QuotaPSO::grvQuota(QuotaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvQuota(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool QuotaPSO::grvQuota(QuotaVO * quota, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_quota (id_campanha, site, quota_max, quota_atual) values (:campanha, :site, :qmax, :qatual)");
	qry.bindValue(":campanha", quota->getIdCampanha());
	qry.bindValue(":site", quota->getSite());
	qry.bindValue(":qmax", quota->getQuotaMax());
	qry.bindValue(":qatual", quota->getQuotaAtual());

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool QuotaPSO::updQuota(QuotaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updQuota(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool QuotaPSO::updQuota(QuotaVO * quota, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_quota");
	if (!cursor.select("id_campanha = " + QString::number(quota->getIdCampanha()) + " and site = '"+ quota->getSite() + "'")) {
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
	buffer->setValue("id_campanha", quota->getIdCampanha());
	buffer->setValue("site", quota->getSite());
	buffer->setValue("quota_max", quota->getQuotaMax());
	buffer->setValue("quota_atual", quota->getQuotaAtual());

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool QuotaPSO::incrementaQuotaAtual(QuotaVO * quota, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_quota");
	if (!cursor.select("id_campanha = " + QString::number(quota->getIdCampanha()) + " and site = '"+ quota->getSite() + "'")) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}
	if (!cursor.next()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	quota->setQuotaMax(cursor.value("quota_max").toUInt());
	uint atual = cursor.value("quota_atual").toUInt();
	atual++;
	QSqlRecord * buffer = cursor.primeUpdate();
	buffer->setValue("quota_atual", atual);

	if (cursor.update() < 1) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();

	quota->setQuotaAtual(atual);
	return true;
}

bool QuotaPSO::delQuota(QuotaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delQuota(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool QuotaPSO::delQuota(QuotaVO * quota, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_quota");
	if (!cursor.select("id_campanha = " + QString::number(quota->getIdCampanha()) + " and site = '" + quota->getSite() + "'")) {
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