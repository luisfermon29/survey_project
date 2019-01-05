#ifndef QUOTAMODEL_H
#define QUOTAMODEL_H


#include "QuotaVO.h"

#include <qsqldatabase.h>


class QuotaModel
{
public:
    QuotaModel(QSqlDatabase *sql=NULL);
    ~QuotaModel();

	void insereQuota(const uint idCampanha=0, const QString site="", const uint quotaMax=0, const uint quotaAtual=0);

	QSqlDatabase *db;
	QPtrList<QuotaVO> list;
};

class RegiaoQuotaModel
{
public:
	RegiaoQuotaModel()
	{
		list.setAutoDelete(true);

		QStringList estados;
		estados << "RJ";
		list.append (new RegiaoQuotaVO("RJ", estados));

		estados.clear();
		estados << "MG" << "ES";
		list.append (new RegiaoQuotaVO("MG", estados));

		estados.clear();
		estados << "BA" << "SE";
		list.append (new RegiaoQuotaVO("BA", estados));

		estados.clear();
		estados << "PE" << "RN" << "AL";
		list.append (new RegiaoQuotaVO("PE", estados));

		estados.clear();
		estados << "CE" << "PI" << "PA" << "AM" << "AP" << "MA" << "RR" << "PB" << "AC" << "RO" << "GO" << "DF" << "MT" << "MS" << "TO" << "SP" << "PR" << "SC" << "RS";
		list.append (new RegiaoQuotaVO("CE", estados));
	}

    ~RegiaoQuotaModel()
	{
		list.clear();
	}

	QPtrList<RegiaoQuotaVO> list;
};

#endif 	// QUOTAMODEL_H