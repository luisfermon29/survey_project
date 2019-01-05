#include "TipoCampanhaPSO.h"


TipoCampanhaPSO::TipoCampanhaPSO(QSqlDatabase * sql)
{
	db = sql;
}

bool TipoCampanhaPSO::lerTipoCampanha(TipoCampanhaModel * modelo)
{
	QSqlCursor cursor("tb_pesq_tipo_campanha");
	if (!cursor.select())
		return false;

	while (cursor.next()) {
		modelo->insereTipoCampanha();
		modelo->list.last()->setIdTipoCampanha(cursor.value("id_tipo_campanha").toUInt());
		modelo->list.last()->setDescricao(cursor.value("nm_tipo_campanha").toString());
		modelo->list.last()->setDescricao(cursor.value("ds_tipo_campanha").toString());
	}
	return true;
}