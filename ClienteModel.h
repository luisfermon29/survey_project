#ifndef CLIENTEMODEL_H
#define CLIENTEMODEL_H


#include "ClienteVO.h"

#include <qsqldatabase.h>


class ClienteModel
{
public:
    ClienteModel(QSqlDatabase *sql=NULL);
    ~ClienteModel();

	void insereCliente(const uint idCliente=0, const uint idSegmento=0, const QString nomeCliente="", const uint idCampanha=0, const QString site="", const QDate dataContato=QDate::QDate(), const QString agente="", const QString supervisor="", const QString solicitacao="", const QDate dataFechamento=QDate::QDate(), const QString categoria="", const QString prePos="", const QString segmento="", const QString regiao="", const QString estado="", const QString obs="", const QString extra1="", const QString extra2="", const QString extra3="", const QString extra4="", const QString extra5="", const QString extra6="", const QString extra="", const QString extra20="", const QString extra21="", const QString extra22="", const QString extra23="", const QString extra24="", const QString extra25="", const QString extra26="", const QString extra27="", const QString extra28="", const QString extra29="");

	QSqlDatabase *db;
	QPtrList<ClienteVO> list;
	QPtrList<EstadoVO> listEstado;
};

#endif 	// CLIENTEMODEL_H