#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "metodos.c"

int main(int argc, char*argv[]){
	
	char *palabra = (char*)malloc(2100);// donde guardamos la lista de los ingredientes

	if(argc < 2){
		printf(stderr,"you must specify a filepath\n");
		return EXIT_FAILURE;
	}

	FILE* fp = fopen(argv[1], "r");

	if(!fp){
		printf("Error opening the file $s\n", argv[1]);
		return EXIT_FAILURE;
	}

	char line[1024];
	int linecount = 0;
	int termscount = 0;
	int quantities[4]; //Guardamos la primer linea del archivo
	int numingredients = 0;
	int numOfDifferentIngredients = 0; //Cantidad de ingresientes
	char *nullchar = '\0';
	while(fgets(line, 1024, fp)){
		char * word;
		char *rest = line;
		if(linecount == 0){
			while(word = strtok_r(rest, " ", &rest)){
				quantities[termscount] = atoi(word);
				termscount++;
			}
			linecount++;
		}else{
			word = strtok_r(rest, " ", &rest);
			numingredients = atoi(word);
			for (int i = 0; i < numingredients; i++) {
				word = strtok_r(rest, " ", &rest);
				if(i==numingredients -1){
					char *s = word;
					while(*s != '\n'){
						++s;
					}
					*s = '\0';
				}
				int comparisonSomeIsEqual = -1;
				for(int j=0; j<numOfDifferentIngredients; j++){
					if (strcmp((palabra+(j*21)), word)==0){
						comparisonSomeIsEqual = 0;
						break;
					}
				}
				if(comparisonSomeIsEqual == -1){
					strcpy((palabra+(numOfDifferentIngredients*21)), word);
					numOfDifferentIngredients++;
				}
			}
			
		}
	}
	fclose(fp);

	FILE *fp2 = fopen(argv[1], "r");
	linecount--;
	int pp[quantities[0]][numOfDifferentIngredients]; //matriz de platos por pedido
	for (int i = 0; i < quantities[0]; i++)
	{
		for (int j = 0; j < numOfDifferentIngredients; j++)
		{
			pp[i][j]=0;
		}
		
	}
	
	while (fgets(line, 1024, fp2))
	{
		char *word2;
        char *rest = line;
        if (linecount == 0)
        {
            linecount++;
        }else{
			word2 = strtok_r(rest, " ", &rest);
			numingredients = atoi(word2);
			for (int i = 0; i < numingredients;i++){
				word2 = strtok_r(rest, " ", &rest);
				for (int i = 0; i < numOfDifferentIngredients; i++)
				{
					if (strcmp(palabra + (21*i),word2)==0)
					{
						pp[linecount-1][i]=1;
						break;
					}
					
				}
				
			}
			linecount++;

		}
	}
	fclose(fp2);

	int ap[quantities[0]]; //Vector respuesta que buscamos optimizar
    for (int i = 0; i < quantities[0]; i++)
    {
        ap[i] = i;
    }
	
	int cuantityPermutation = factorial(quantities[0]);
    int currentPermutation[quantities[0]];
    int nextPermutation[quantities[0]];
    duplicar(ap, currentPermutation, quantities[0]);
    nextiter(currentPermutation, nextPermutation, quantities[0]);
    int maximizadoPermact = 0;
    int maximizadopersig = 0;
    int maxima = 0;
	bool aux = false;

    for (int i = 1; i <= cuantityPermutation; i++)
    {
        maximizadoPermact = maximizar(aux, currentPermutation, quantities, palabra, numOfDifferentIngredients, pp, NULL);
        maximizadopersig = maximizar(aux, nextPermutation, quantities, palabra, numOfDifferentIngredients, pp, NULL);
        if (maximizadoPermact < maximizadopersig)
        {
            duplicar(nextPermutation, currentPermutation, quantities[0]);
            nextiter(currentPermutation, nextPermutation, quantities[0]);
            maxima = maximizadopersig;
        }
        else
        {
            maxima = maximizadoPermact;
            nextiter(nextPermutation, nextPermutation, quantities[0]);
        }
    }

	aux = true;

	FILE *fp3;
	fp3 = fopen("output.txt", "wt");

	fputs("Matriz de los platos: \n", fp3);
	for(int i = 0;i < quantities[0]; i++){
		for(int j=0;j< numOfDifferentIngredients; j++){
			fprintf(fp3, (j != quantities[0]-1) ? "%d" : "%d", pp[i][j]);
		}
		fputs("\n", fp3);
	}
	fputs("\n", fp3);

	fputs("Vector solución: ", fp3);
	for(int i=0; i<quantities[0]; i++){
		fprintf(fp3, (i != quantities[0] - 1) ? "%d" : "%d", currentPermutation[i]);
	}
	fputs(", \ncon un total de: ", fp3);
	fprintf(fp3, "%d", maxima);
	fputs(" ingredientes diferentes.\n", fp3);
	maximizar(aux, currentPermutation, quantities, palabra, numOfDifferentIngredients,  pp, fp3);
	fclose(fp3);

}