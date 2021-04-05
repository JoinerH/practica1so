#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Funcion con el modelo matematico donde estan las sumatorias
int maximizar(bool auxi, int ap[], int quantities[], char ingr[], int numOfDifferentIngredients, int pp[][numOfDifferentIngredients], FILE *fp3)
{
    
    int suma = 0;
    int op3 = 2 * quantities[1];
    int op4 = op3 + 3 * quantities[2];
    int b = 0;
    int c = 0;
    bool prueba = auxi;

    for (int i = 0; i < quantities[1]; i++)
    {
           
        if (prueba == 1)
        {
            
            fputs("\nEl pedido ", fp3);
            fprintf(fp3, "%d", i);
            fputs(" contiene: ", fp3);  
        }
        
        
        for (int j = 0; j < numOfDifferentIngredients; j++)
        {
            
            if ((pp[ap[2 * i]][j] || pp[ap[(2 * i) + 1]][j]) == 1){
                if(prueba == 1){
                    fputs(ingr+(21*j), fp3);
                    fputs(", ", fp3);
                }
                suma++;
            }
        }
        b++;
    }

    for (int i = 0; i < quantities[2]; i++)
    {
        if (prueba == 1)
        {
            fputs("\nEl pedido ", fp3);
            fprintf(fp3, "%d", i + b);
            fputs(" contiene: ", fp3);
        }
        for (int j = 0; j < numOfDifferentIngredients; j++)
        {
            if ((pp[ap[op3 + (3 * i)]][j] ||
                 pp[ap[op3 + (3 * i) + 1]][j] ||
                 pp[ap[op3 + (3 * i) + 2]][j]) == 1)
            {
                if (prueba == 1)
                {
                    fputs(ingr + (21*j), fp3);
                    fputs(", ", fp3);
                }
                suma++;
            }
        }
        c++;
    }

    for (int i = 0; i < quantities[3]; i++)
    {
        if (prueba == 1)
        {
            fputs("\nEl pedido ", fp3);
            fprintf(fp3, "%d", i + b + c);
            fputs(" contiene: ", fp3);
        }
        for (int j = 0; j < numOfDifferentIngredients; j++)
        {
            
            if ((pp[ap[op4 + (4 * i)]][j] ||
                 pp[ap[op4 + (4 * i) + 1]][j] ||
                 pp[ap[op4 + (4 * i) + 2]][j] ||
                 pp[ap[op4 + (4 * i) + 3]][j]) == 1)
            {
                if (prueba == 1)
                {
                    fputs(ingr + (21*j), fp3);
                    fputs(", ", fp3);
                }
                suma++;
            }
        }
    }
    return suma;
}

int factorial(int factorial)
{
    int resultado = 1;
    while (factorial > 1)
    {
        resultado *= factorial;
        factorial--;
    }
    return resultado;
}

void nextiter(int array[], int arrPermutado[], int x)
{
    int i = x - 1;
    duplicar(array, arrPermutado, x);

    while (i > 0 && arrPermutado[i - 1] >= arrPermutado[i])
    {
        i--;
    }
    if (i <= 0)
    {
        return;
    }
    int j = x - 1;
    while (arrPermutado[j] <= arrPermutado[i - 1])
    {
        j--;
    }

    int temp = arrPermutado[i - 1];
    arrPermutado[i - 1] = arrPermutado[j];
    arrPermutado[j] = temp;

    j = x - 1;

    while (i < j)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
}

void duplicar(int ex[], int re[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        re[i] = ex[i];
    }
}