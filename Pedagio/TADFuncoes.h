#define TF 10

void DesenharQuadro() {
    int largura = 124;
    int altura = 40;

    gotoxy(1, 1);
    printf("+");
    for (int j = 2; j < largura - 1; j++) {
        printf("-");
    }
    printf("+");
    
    gotoxy(43, 2);
    printf("*** SIMULACAO DE PRACA DE PEDAGIO ***");

    gotoxy(1, altura - 1);
    printf("+");
    for (int j = 2; j < largura - 1; j++) {
        printf("-");
    }
    printf("+");

    for (int i = 2; i < altura - 1; i++) {
        gotoxy(1, i);
        printf("|");
        gotoxy(largura - 1, i);
        printf("|");
    }
    
    gotoxy(1, 3);
    printf("+");
    for (int j = 2; j < largura - 1; j++) {
        printf("-");
    }
    printf("+");
    
    gotoxy(1, 6);
    printf("+");
    for (int j = 2; j < largura - 1; j++) {
        printf("-");
    }
    printf("+");
}

void DesenharCabine(TpfilaC &f, int i){
    if(f.status == 0)
        textcolor(RED);
    else if(f.status == 1)
        textcolor(GREEN);
    else
        textcolor(CYAN);

    gotoxy(f.eixoX, 7);
	printf("+---------+");
	gotoxy(f.eixoX, 8);
	printf("|    %d    |", i);
	gotoxy(f.eixoX, 9);
	printf("+---------+");

    textcolor(WHITE);
}

void MudaStatus(TpfilaC cabine[TF]){
	char opc;
	do{
		gotoxy(3, 4);
    	printf("Deseja alterar o status de ativo/inativo de qual cabine? (Tecle ESC para SAIR)");
    	opc = getch();
    	
    	if(opc>=48 && opc<=56){ //0 a 8 (9 é sem parar)
    		if(cabine[opc-48].status==0){
    			cabine[opc-48].status=1;
    			gotoxy(3, 5);
    			printf("Cabine ativada!");
			} else {
				cabine[opc-48].status=0;
    			gotoxy(3, 5);
    			printf("Cabine desativada!");
			}
						
			DesenharCabine(cabine[opc-48], opc-48);
			Sleep(1000);
		} else if(opc!=27){
			gotoxy(3, 5);
    		printf("Opcao invalida!");
    		
    		Sleep(1000);
		}
		
		gotoxy(3, 5);
    	printf("               	  ");
				
	}while(opc != 27); 
	
	gotoxy(3, 4);
    printf("Pressione ESC para sair ou qualquer outra tecla para alterar status de cabine ");
}

int EncontrarFila(TpfilaC cabine[TF]) {
    int j = -1, qtde = MAXFILA + 1; 

    for (int i = 0; i < TF-1; i++) {
        if (cabine[i].status != 0 && cabine[i].qtde < qtde) {
            qtde = cabine[i].qtde;
            j = i;
        }
    }

    return j;
}

void ExecutarAtendimento(TpfilaC cabine[TF], int &totalTempoEspera, int &totalTempoAtendimento, int &veiculosPorHora, int &veiculosSemPararPorHora){
    for (int i = 0; i < TF; i++) {
        if (!Vazia(cabine[i])) {
        	if (i != TF-1){
        		cabine[i].fila[cabine[i].inicio].tempoCabine++;
        		cabine[i].fila[cabine[i].inicio].tempoAtend--;
			}
            else
            	cabine[i].fila[cabine[i].inicio].tempoAtend=0;
            
            if (cabine[i].fila[cabine[i].inicio].tempoAtend == 0) {
            	totalTempoEspera += cabine[i].fila[cabine[i].inicio].tempoEspera;
    			totalTempoAtendimento += cabine[i].fila[cabine[i].inicio].tempoCabine;
			    veiculosPorHora++;
			    if(cabine[i].status == 2) {
			        veiculosSemPararPorHora++;
			    }
                Retirar(cabine[i]);
            }
        }
    }
}

void LimparExibicao(TpfilaC fp){
    int eixoY = 11;
    for (int i = 0; i < MAXFILA; i++) {
        gotoxy(fp.eixoX, eixoY);
        printf("            "); 
        eixoY += 3;
        if(eixoY >= 30) 
            break;
    }
}

void AjustarTamanhoConsole(int largura, int altura) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD bufferSize = {largura, altura};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = {0, 0, largura-1, altura-1};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

char FimExecucao(TpfilaC cabine[TF]){
    for (int i = 0; i < TF; i++) {
        if (!Vazia(cabine[i])) {
            return false;
        }
    }
    return true;
}
