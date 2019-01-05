#include "ListaPSO.h"

#include <stdlib.h>
#include <qdatetime.h>
#include <time.h>


ListaPSO::ListaPSO(QSqlDatabase * sql)
{
	db = sql;
}


bool ListaPSO::lerListaId(ListaVO * lista, uint idLista)
{
	QSqlCursor cursor("tb_pesq_lista_raw");
	if (!cursor.select("id_lista_raw = " + QString::number(idLista)))
		return false;

	if (!cursor.next())
		return false;

	lerLista(&cursor, lista);

	return true;
}

bool ListaPSO::lerListaIdCliente(ListaVO * lista, uint idCliente)
{
	QSqlCursor cursor("tb_pesq_lista_raw");
	if (!cursor.select("id_cliente = " + QString::number(idCliente)))
		return false;

	if (!cursor.next())
		return false;

	lerLista(&cursor, lista);

	if (db != NULL)
		db->transaction();

	QSqlRecord * buffer = cursor.primeUpdate();
	buffer->setValue("flg_ligacao", 1);
	if (cursor.update() < 1) {
		if (db != NULL)
			db->rollback();
		return false;
	}

	if (db != NULL)
		db->commit();

	return true;
}

bool ListaPSO::lerListaIdCampanha(ListaVO * lista, uint idCampanha, QString uf, uint tp)
{
	QString str;
	QString diaSemana = QDate::currentDate().toString("ddd"), data = QDate::currentDate().toString("dd/MM/yyyy");

	uint nrdias=7;

	if (uf == "A")
		uf = "'A'";
	else if (uf == "RJ")
		uf = "'RJ','MG'";
	else if (uf == "PE")
		uf = "'PE','RJ'";
	else if (uf == "MG")
		uf = "'MG','PE'";

	if (tp == 100)
		str = " <> 0";
	else if (tp == 3)
		str = " = 2";
	else if (tp == 2)
		str = " = 1";
	else if (tp == 1)
		str = " = 3";


	QSqlCursor cursor("tb_pesq_lista_raw");
/*
	if (diaSemana == "qua"){
		if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('QUA','QUI','WED','THU'))"))
			return false;
	}else if (diaSemana == "qui"){
		if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('QUI','SEX','THU','FRI'))"))
			return false;
	}else if (diaSemana == "sex"){
		if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('SEX','SAB','FRI','SAT'))"))
			return false;
	}else if ((diaSemana == "sab") || (diaSemana == "sáb")){
		if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('SAB','DOM','SAT','SUN'))"))
			return false;
	}

	for (uint i=1; i<=7; i++){
		if (diaSemana == "seg"){
			if (cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where (to_date(to_char(dt_contato+" + QString::number(nrdias) + ",'dd/mm/yyyy'),'dd/mm/yyyy')=to_date('" + data +"','dd/mm/yyyy') or to_date(to_char(dt_contato+" + QString::number(nrdias+1) + ",'dd/mm/yyyy'),'dd/mm/yyyy')=to_date('" + data +"','dd/mm/yyyy')))"))
				if (cursor.first())
					break;
//					return false;
		}else{
	//		if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where (to_char(dt_contato+7,'dd/mm/yyyy')='" + data +"'))"))
			if (cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where (to_date(to_char(dt_contato+" + QString::number(nrdias) + ",'dd/mm/yyyy'),'dd/mm/yyyy')=to_date('" + data +"','dd/mm/yyyy')))"))
				if (cursor.first())
					break;
//					return false;
		}
		nrdias--;
	}
*/
	if (!cursor.select("id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0"))
		return false;

	if (!cursor.first())
		return false;

//	int size = cursor.size();
	int size;

	QSqlQuery qry;
/*	
	if (diaSemana == "qua"){
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + ") and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('QUA','QUI','WED','THU'))");
	}else if (diaSemana == "qui"){
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + ") and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('QUI','SEX','THU','FRI'))");
	}else if (diaSemana == "sex"){
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + ") and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('SEX','SAB','FRI','SAT'))");
	}else if ((diaSemana == "sab") || (diaSemana == "sáb")){
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + ") and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where to_date(seg_aten,'dd/mm/yyyy')<sysdate and to_date(seg_aten,'dd/mm/yyyy')>(sysdate-8) and to_char(to_date(seg_aten,'dd/mm/yyyy'),'DY') in ('SAB','DOM','SAT','SUN'))");
	}
*/

/*	if (diaSemana == "seg"){
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where (to_date(to_char(dt_contato+10,'dd/mm/yyyy'),'dd/mm/yyyy')>=to_date('" + data +"','dd/mm/yyyy') or to_date(to_char(dt_contato+11,'dd/mm/yyyy'),'dd/mm/yyyy')>=to_date('" + data +"','dd/mm/yyyy')))");
	}else{
		qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0 and id_cliente in (select id_cliente from tb_pesq_cliente where (to_date(to_char(dt_contato+10,'dd/mm/yyyy'),'dd/mm/yyyy')>=to_date('" + data +"','dd/mm/yyyy')))");
	}
*/
	qry.prepare("select count(*) from tb_pesq_lista_raw where id_campanha = " + QString::number(idCampanha) + " and flg_ligacao = 0");

	if (!qry.exec()) {
		size = -1;
	}
	if (!qry.next()) {
		size = -1;
	}else{
		size = qry.value(0).toInt();
	}
	
	uint count=0;

	do {
		int pos;
//		QTime hora = QTime::currentTime();
//		srand(hora.second() + hora.msec());
		srand(time(NULL));
		if (size == -1) {
			switch (count) {
			case 0:
				pos = rand() % 1000;
				break;

			case 1:
				pos = rand() % 500;
				break;

			case 2:
				pos = rand() % 100;
				break;

			case 3:
				pos = rand() % 10;
				break;

			default:
				pos = 0;
			}
		} else
			pos = rand() % size;

		if (cursor.seek(pos)) {
			lerLista(&cursor, lista);

			if (db != NULL)
				db->transaction();

			QSqlRecord * buffer = cursor.primeUpdate();
			buffer->setValue("flg_ligacao", 1);
			if (cursor.update() < 1) {
				if (db != NULL)
					db->rollback();
				return false;
			}

			if (db != NULL)
				db->commit();
			return true;
		}

		count++;
	} while (count <= 4);

	return false;
}

void ListaPSO::lerLista(QSqlCursor * cursor, ListaVO * lista)
{
	lista->setIdLista(cursor->value("id_lista_raw").toUInt());
	lista->setIdCampanha(cursor->value("id_campanha").toUInt());
	lista->setIdCliente(cursor->value("id_cliente").toUInt());
	lista->setTp(cursor->value("tp").toUInt());

	bool flag = true;
	if (cursor->value("flg_ligacao").toUInt() == 0)
		flag = false;
	lista->setFlagLig(flag);
}

bool ListaPSO::grvLista(ListaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!grvLista(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ListaPSO::grvLista(ListaVO * lista, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("insert into tb_pesq_lista_raw (id_lista_raw, id_cliente, id_campanha, flg_ligacao) values (id_lista_raw.nextval, :cliente, :campanha, :flagLig)");
	qry.bindValue(":cliente", lista->getIdCliente());
	qry.bindValue(":campanha", lista->getIdCampanha());

	uint flag = 0;
	if (lista->getFlagLig())
		flag = 1;
	qry.bindValue(":flagLig", flag);

	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool ListaPSO::updLista(ListaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!updLista(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ListaPSO::updLista(ListaVO * lista, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_lista_raw");
	if (!cursor.select("id_lista_raw = " + QString::number(lista->getIdLista()))) {
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
	buffer->setValue("id_campanha", lista->getIdCampanha());
	buffer->setValue("id_cliente", lista->getIdCliente());

	uint flag = 0;
	if (lista->getFlagLig())
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

bool ListaPSO::delLista(ListaModel * modelo)
{
	uint index;

	if (db != NULL)
		db->transaction();

	for (index=0; index<modelo->list.count(); index++) {
		if (!delLista(modelo->list.at(index))) {
			if (db != NULL)
				db->rollback();

			return false;
		}
	}
	if (db != NULL)
		db->commit();

	return true;
}

bool ListaPSO::delLista(ListaVO * lista, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlCursor cursor("tb_pesq_lista_raw");
	if (!cursor.select("id_lista_raw = " + QString::number(lista->getIdLista()))) {
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

bool ListaPSO::delListaIdCliente(uint idCliente, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("delete tb_pesq_lista_raw where id_cliente = :cliente");
	qry.bindValue(":cliente", idCliente);
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool ListaPSO::delListaIdCampanha(uint idCampanha, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	qry.prepare("delete tb_pesq_lista_raw where id_campanha = :campanha");
	qry.bindValue(":campanha", idCampanha);
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}

bool ListaPSO::delListaIdCampanhaSite(uint idCampanha, QString site, QSqlDatabase * sql)
{
	if (sql != NULL)
		sql->transaction();

	QSqlQuery qry;
	//qry.prepare("delete tb_pesq_lista_raw where id_campanha = :campanha");
	qry.prepare("delete tb_pesq_lista_raw where id_cliente in (select id_cliente from tb_pesq_cliente where id_campanha = :campanha and site = :strSite)");
	qry.bindValue(":campanha", idCampanha);
	qry.bindValue(":strSite", site);
	if (!qry.exec()) {
		if (sql != NULL)
			sql->rollback();
		return false;
	}

	if (sql != NULL)
		sql->commit();
	return true;
}
