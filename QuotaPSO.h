#ifndef QUOTAPSO_H
#define QUOTAPSO_H

#include "QuotaModel.h"

#include <qsqlcursor.h>
#include <qsqlcursor.h>


class QuotaPSO
{
public:
	QuotaPSO(QSqlDatabase * sql=NULL);

	bool lerQuotaIdCampanha(QuotaModel * modelo, uint idCampanha);
	bool lerQuotaIdCampanhaSite(QuotaVO * quota, uint idCampanha, QString site);
	void lerQuota(QSqlCursor * cursor, QuotaVO * quota);

	bool grvQuota(QuotaModel * modelo);
	bool grvQuota(QuotaVO * quota, QSqlDatabase * sql=NULL);

	bool updQuota(QuotaModel * modelo);
	bool updQuota(QuotaVO * quota, QSqlDatabase * sql=NULL);

	bool incrementaQuotaAtual(QuotaVO * quota, QSqlDatabase * sql);

	bool delQuota(QuotaModel * modelo);
	bool delQuota(QuotaVO * quota, QSqlDatabase * sql=NULL);

	QSqlDatabase * db;
};

#endif 	// QUOTAPSO_H