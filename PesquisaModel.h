#ifndef PESQUISAMODEL_H
#define PESQUISAMODEL_H


#include "LoginVO.h"
#include "LoginPSO.h"
#include "CampanhaPSO.h"
#include "EmpregadoPSO.h"
#include "ClientePSO.h"
#include "TelefonePSO.h"
#include "ChamadaPSO.h"
#include "RechamadaPSO.h"
#include "ListaPSO.h"
#include "BlocoPSO.h"
#include "RespostaPSO.h"
#include "QuotaPSO.h"


class QuestionarioVO;


class PesquisaModel
{
public:
	PesquisaModel(LoginVO * login, CampanhaVO * campanha, QSqlDatabase * sql=NULL);
	~PesquisaModel();

	void insereProximo (const uint indexBloco=0, const uint indexPergunta=0, const uint indexTela=0);
	void removeUltimo ();

	QSqlDatabase * db;

	LoginVO * loginVO;
	LoginPSO * loginPSO;
	CampanhaVO * campanhaVO;
	CampanhaModel * campanhaModel;
	CampanhaPSO * campanhaPSO;
	EmpregadoVO * empregadoVO;
	EmpregadoPSO * empregadoPSO;
	ClienteVO * clienteVO;
	ClienteModel * clienteModel;
	ClientePSO * clientePSO;
	TelefoneVO * telefoneVO;
	TelefonePSO * telefonePSO;
	ChamadaVO * chamadaVO;
	FinalizacaoChamadaModel * finalizacaoChamadaModel;
	ExcecaoChamadaModel * excecaoChamadaModel;
	ChamadaPSO * chamadaPSO;
	RechamadaVO * rechamadaVO;
	RechamadaPSO * rechamadaPSO;
	ListaVO * listaVO;
	ListaPSO * listaPSO;
	BlocoModel * blocoModel;
	BlocoPSO * blocoPSO;
	RespostaModel * respostaModel;
	RespostaPSO * respostaPSO;
	QuotaVO * quotaVO;
	QuotaPSO * quotaPSO;
	RegiaoQuotaModel * regiaoQuotaModel;

	uint tipoSolicitacao, tipo2;

	QPtrList<QuestionarioVO> questionario;
};


class QuestionarioVO
{
public:
	QuestionarioVO(const uint indexBloco=0, const uint indexPergunta=0, const uint indexTela=0)
	{
		bloco = indexBloco;
		pergunta = indexPergunta;
		tela = indexTela;
	}

	void setBloco (const uint index) { bloco = index; }
	void setPergunta (const uint index) { pergunta = index; }
	void setTela (const uint index) { tela = index; }

	uint getBloco () { return bloco; }
	uint getPergunta () { return pergunta; }
	uint getTela () { return tela; }

private:
	uint bloco;
	uint pergunta;
	uint tela;
};

#endif 	// PESQUISAMODEL_H