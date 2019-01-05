#include "QuotaModel.h"


QuotaModel::QuotaModel(QSqlDatabase *sql)
{
	list.clear();
	list.setAutoDelete(TRUE);

	db = sql;
}

QuotaModel::~QuotaModel()
{
	list.clear();
}

void QuotaModel::insereQuota(const uint idCampanha, const QString site, const uint quotaMax, const uint quotaAtual)
{
	list.append(new QuotaVO(idCampanha, site, quotaMax, quotaAtual));
}