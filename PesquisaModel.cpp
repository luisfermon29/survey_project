#include "PesquisaModel.h"


PesquisaModel::PesquisaModel(LoginVO * login, CampanhaVO * campanha, QSqlDatabase * sql)
{
	questionario.clear();
	questionario.setAutoDelete(TRUE);

	db = sql;

	loginVO = login;
	campanhaVO = campanha;

	campanhaModel = new CampanhaModel(db);
	campanhaPSO = new CampanhaPSO(db);
	empregadoVO = new EmpregadoVO;
	empregadoPSO = new EmpregadoPSO(db);
	clienteVO = new ClienteVO;
	clienteModel = new ClienteModel(db);
	clientePSO = new ClientePSO(db);
	telefoneVO = new TelefoneVO;
	telefonePSO = new TelefonePSO(db);
	chamadaVO = new ChamadaVO;
	finalizacaoChamadaModel = new FinalizacaoChamadaModel(db);
	excecaoChamadaModel = new ExcecaoChamadaModel(db);
	chamadaPSO = new ChamadaPSO(db);
	rechamadaVO = new RechamadaVO;
	rechamadaPSO = new RechamadaPSO(db);
	listaVO = new ListaVO;
	listaPSO = new ListaPSO(db);
	blocoModel = new BlocoModel(db);
	blocoPSO = new BlocoPSO(db);
	respostaModel = new RespostaModel(db);
	respostaPSO = new RespostaPSO(db);
	quotaVO = new QuotaVO;
	quotaPSO = new QuotaPSO(db);
	regiaoQuotaModel = new RegiaoQuotaModel;
}

PesquisaModel::~PesquisaModel()
{
	questionario.clear();

	loginVO = NULL;
	campanhaVO = NULL;

	delete campanhaModel;
	delete campanhaPSO;
	delete empregadoVO;
	delete empregadoPSO;
	delete clienteVO;
	delete clienteModel;
	delete clientePSO;
	delete telefoneVO;
	delete telefonePSO;
	delete chamadaVO;
	delete finalizacaoChamadaModel;
	delete excecaoChamadaModel;
	delete chamadaPSO;
	delete rechamadaVO;
	delete rechamadaPSO;
	delete listaVO;
	delete listaPSO;
	delete blocoModel;
	delete blocoPSO;
	delete respostaModel;
	delete respostaPSO;
	delete quotaVO;
	delete quotaPSO;
	delete regiaoQuotaModel;
}

void PesquisaModel::insereProximo (const uint indexBloco, const uint indexPergunta, const uint indexTela)
{
	questionario.append(new QuestionarioVO(indexBloco, indexPergunta, indexTela));
}

void PesquisaModel::removeUltimo ()
{
	questionario.removeLast();
}