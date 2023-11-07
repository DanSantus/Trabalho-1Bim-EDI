/*
Daniel dos Santos RA: 262216957
Mateus Cunha Sepulveda RA: 262215969
*/

#define MAXFILA 100

struct TpVeiculo{
    int numEixos, prioridade, tempoAtend, tempoEspera, tempoCabine;
    char placa[8], cor[10], fabricante[15], categoria[8];
};

struct TpfilaC{
	int inicio, fim, qtde, eixoX, status;
	TpVeiculo fila[MAXFILA];
};

void Inicializar(TpfilaC &fp, int eixoX){
	fp.inicio = 0;
	fp.fim = -1;
	fp.qtde = 0;
	fp.eixoX = eixoX;
	fp.status = 1;
}

char Cheia(TpfilaC fp){
	return fp.qtde == MAXFILA;
}

char Vazia(TpfilaC fp){
	return fp.qtde == 0;
}

void Inserir(TpfilaC &fp, TpVeiculo elem){
	if(fp.fim == MAXFILA - 1){
		fp.fim = -1;
	}
	fp.fila[++fp.fim] = elem;
	fp.qtde++;
}

TpVeiculo Retirar(TpfilaC &fp){
	TpVeiculo aux = fp.fila[fp.inicio];
	fp.inicio = (fp.inicio + 1) % MAXFILA;
	fp.qtde--;
	return aux;
}

void Exibir(TpfilaC fp){
    int eixoY = 11;
    int pos = fp.inicio;
    
    for (int i = 0; i < fp.qtde; i++) {
        gotoxy(fp.eixoX, eixoY);
        printf("%s (%d)", fp.fila[pos].placa, fp.fila[pos].tempoAtend);
        eixoY += 3;
        pos = (pos + 1) % MAXFILA;
    }
}

TpVeiculo ElementoinicioC(TpfilaC fp){
	return fp.fila[fp.inicio];
}

TpVeiculo ElementofimC(TpfilaC fp){
	return fp.fila[fp.fim];
}
