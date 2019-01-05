#ifndef QUOTAVO_H
#define QUOTAVO_H


#include <qstring.h>
#include <qstringlist.h>


class QuotaVO
{
public:
	QuotaVO (const uint idCampanha=0, const QString site="", const uint quotaMax=0, const uint quotaAtual=0)
	{
		setIdCampanha (idCampanha);
		setSite (site);
		setQuotaMax (quotaMax);
		setQuotaAtual (quotaAtual);
	}

	void setIdCampanha (const uint id) { idCampanha = id; }
	void setSite (const QString str) { site = str; }
	void setQuotaMax (const uint id) { quotaMax = id; }
	void setQuotaAtual (const uint id) { quotaAtual = id; }

	uint getIdCampanha () { return idCampanha; }
	QString getSite () { return site; }
	uint getQuotaMax () { return quotaMax; }
	uint getQuotaAtual () { return quotaAtual; }

private:
	uint idCampanha;
	QString site;
	uint quotaMax;
	uint quotaAtual;
};


class RegiaoQuotaVO
{
public:
	RegiaoQuotaVO (const QString regiao="", const QStringList estados="")
	{
		setRegiao (regiao);
		setEstados (estados);
	}

	void setRegiao (const QString str) { regiao = str; }
	void setEstados (const QStringList lista) { estados = lista; }

	QString getRegiao () { return regiao; }
	QStringList getEstados () { return estados; }

private:
	QString regiao;
	QStringList estados;
};


#endif 	// QUOTAVO_H