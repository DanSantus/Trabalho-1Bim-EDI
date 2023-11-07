#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include "TADFilaCircular.h"
#include "TADFuncoes.h"

int main(void){	
	AjustarTamanhoConsole(124, 40);
		
	int i, j, m=15, n, ut= 0, totalVeiculos = 0, totalVeiculosSemParar = 0, totalTempoEspera = 0, totalTempoAtendimento = 0, veiculosPorHora = 0, veiculosSemPararPorHora = 0, tempoLeitura;
	int totalPorCategoria[3] = {0}; 
	int totalPorCategoriaSemPararPorHora[3] = {0}; 
	const char* categorias[] = {"Caminhao", "Carro", "Moto"};

	TpfilaC cabine[TF];	
	TpVeiculo aux;
	
	DesenharQuadro();
							
	FILE *arq = fopen("Veiculos.txt", "r"); 
	if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    for(i=0; i<TF; i++){
		Inicializar(cabine[i], 3+12*i);
		if(i==TF-1)
			cabine[i].status=2;
		
		DesenharCabine(cabine[i], i);
	}
	
	gotoxy(3, 4);
	printf("Informe o tempo necessario para a leitura do carro (em unidades de tempo): ");
	scanf("%d", &tempoLeitura);
	MudaStatus(cabine);
    
	while (!feof(arq) || !FimExecucao(cabine)) {
		if (ut % (tempoLeitura * 60) == 0 && ut != 0) {
			n=31;
		    gotoxy(3, n++);
    		printf("Na hora %d:", ut / 120);
		    for (int i = 0; i < 3; i++) {
		        gotoxy(3, n++);
        		printf("Categoria %s na cabine 'Via Facil ou Sem Parar': %d veiculo(s)", categorias[i], totalPorCategoriaSemPararPorHora[i]);
		        totalPorCategoriaSemPararPorHora[i] = 0; 
		    }
		    gotoxy(3, n++);
		    printf("Total de veiculos na cabine 'Via Facil ou Sem Parar' nessa hora: %d", veiculosSemPararPorHora);
		    gotoxy(3, n++);
		    printf("Total de veiculos que passaram por todas as cabines nessa hora: %d", veiculosPorHora);
		    veiculosSemPararPorHora = 0; 
		    veiculosPorHora = 0; 
		}

	    if (!feof(arq) && ut % tempoLeitura == 0) {
	        if (fscanf(arq, " %[^;]; %[^;]; %[^;]; %d; %[^;]; %d; %d; ", aux.placa, aux.cor, aux.fabricante, &aux.numEixos, aux.categoria, &aux.prioridade, &aux.tempoAtend) == 7) {
		        aux.tempoEspera = 0;
		        aux.tempoCabine = 0;
				
				if(aux.prioridade == 0)
		       		j = EncontrarFila(cabine);
		       	else
		       		j = TF-1;	       		
		        
		        if (j!=-1 && !Cheia(cabine[j])) {
				    totalVeiculos++;
				    
				    if (strcmp(aux.categoria, "Caminhao") == 0)
				        totalPorCategoria[0]++;
				    else if (strcmp(aux.categoria, "Carro") == 0)
				        totalPorCategoria[1]++;
				    else if (strcmp(aux.categoria, "Moto") == 0)
				        totalPorCategoria[2]++;
				     
				    if(cabine[j].status == 2) {
				    	totalVeiculosSemParar++;
				    	if (strcmp(aux.categoria, "Caminhao") == 0)
					        totalPorCategoriaSemPararPorHora[0]++;
					    else if (strcmp(aux.categoria, "Carro") == 0)
					        totalPorCategoriaSemPararPorHora[1]++;
					    else if (strcmp(aux.categoria, "Moto") == 0)
					        totalPorCategoriaSemPararPorHora[2]++;
					}
					    
				    Inserir(cabine[j], aux);
				}
			}
	    }
	    
	    for (int i = 0; i < TF; i++) {
		    LimparExibicao(cabine[i]);
		    Exibir(cabine[i]);
		}
		
	    Sleep(500);
	    
	    for(int k = 0; k < TF; k++){
		    for(int l = 0; l < cabine[k].qtde; l++) {
		    	if (cabine[k].status != 2){
		    		int pos = (cabine[k].inicio + l) % MAXFILA;
			        cabine[k].fila[pos].tempoEspera++;
				}
		    }
		}
	    
	    ExecutarAtendimento(cabine, totalTempoEspera, totalTempoAtendimento, veiculosPorHora, veiculosSemPararPorHora);
	    
	    if (kbhit()) {
	    	if(getch() != 27)
	        	MudaStatus(cabine);
	        else
	        	break;
	    }
	    
	    ut++;
	}
	
	gotoxy(3, m++);
	printf("Tempo medio de espera para saida: %f UTs", (float)totalTempoEspera / totalVeiculos);
	gotoxy(3, m++);
	printf("Tempo medio de atendimento: %f UTs", (float)totalTempoAtendimento / totalVeiculos);
	
	m++;
	gotoxy(3, m++);
	printf("Total de veiculos por categoria:");
	for (int i = 0; i < 3; i++) {
	    gotoxy(3, m++);
	    printf("Categoria %s: %d veiculo(s)", categorias[i], totalPorCategoria[i]);
	}
	
	n=31;
	gotoxy(3, n++);
    printf("Na hora %d:", ut / 120);
    for (int i = 0; i < 3; i++) {
        gotoxy(3, n++);
        printf("Categoria %s na cabine 'Via Facil ou Sem Parar': %d veiculo(s)", categorias[i], totalPorCategoriaSemPararPorHora[i]);
    }
    gotoxy(3, n++);
    printf("Total de veiculos na cabine 'Via Facil ou Sem Parar' nessa hora: %d", veiculosSemPararPorHora);
    gotoxy(3, n++);
    printf("Total de veiculos que passaram por todas as cabines nessa hora: %d", veiculosPorHora);
	
	getch();
	
	fclose(arq);
	gotoxy(3, 28);
    return 0;
}
