#ifndef CAMPANHAVO_H
#define CAMPANHAVO_H


#include <qstring.h>
#include <qdatetime.h>


class CampanhaVO
{
public:
	CampanhaVO (const uint idCampanha=0, const uint idTipoCampanha=0, const QString descricao="", const QString caminhoScript="", const QDate dataInicio=QDate::QDate(), const QDate dataTermino=QDate::QDate())
	{
		setIdCampanha (idCampanha);
		setIdTipoCampanha (idTipoCampanha);
		setDescricao (descricao);
		setCaminhoScript (caminhoScript);
		setDataInicio (dataInicio);
		setDataTermino (dataTermino);
	}

	void setIdCampanha (uint id) { idCampanha = id; }
	void setIdTipoCampanha (uint id) { idTipoCampanha = id; }
	void setDescricao (QString str) { descricao = str; }
	void setCaminhoScript (QString str) { caminhoScript = str; }
	void setDataInicio (QDate data) { dataInicio = data; }
	void setDataTermino (QDate data) { dataTermino = data; }

	uint getIdCampanha () { return idCampanha; }
	uint getIdTipoCampanha () { return idTipoCampanha; }
	QString getDescricao () { return descricao; }
	QString getCaminhoScript () { return caminhoScript; }
	QDate getDataInicio () { return dataInicio; }
	QDate getDataTermino () { return dataTermino; }

private:
	uint idCampanha;
	uint idTipoCampanha;
	QString descricao;
	QString caminhoScript;
	QDate dataInicio;
	QDate dataTermino;
};

#endif 	// CAMPANHAVO_H