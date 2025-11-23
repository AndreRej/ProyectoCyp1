/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include <ctype.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
    FILE* fp;
    errno_t err = fopen_s(&fp, szNombre, "rt");
    if (err != 0 || fp == NULL)
    {
        iNumElementos = 0;
        return;
    }

    iNumElementos = 0;
    char palabra[TAMTOKEN];
    int idx = 0;
    int c;

    while ((c = fgetc(fp)) != EOF)
    {
        int Separar = 0;

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
            c == ',' || c == ';' || c == '(' || c == ')' || c == '.')
        {
            Separar = 1;
        }

        if (Separar == 0)
        {
            if (idx < TAMTOKEN - 1)
            {
                palabra[idx] = (char)c;
                idx++;
            }
        }
        else
        {
            if (idx > 0)
            {
                palabra[idx] = '\0';
                idx = 0;
                int j;
                for (j = 0; palabra[j]; j++)
                    palabra[j] = tolower(palabra[j]);

                int pos = -1;
                int i = 0;
                while (i < iNumElementos && pos == -1)
                {
                    if (strcmp(palabra, szPalabras[i]) == 0)
                    {
                        pos = i;
                    }
                    i++;
                }

                if (pos != -1)
                {
                    iEstadisticas[pos]++;
                }
                else
                {
                    if (iNumElementos < NUMPALABRAS)
                    {
                        strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabra);
                        iEstadisticas[iNumElementos] = 1;
                        iNumElementos++;
                    }
                }
            }
        }
    }

    if (idx > 0)
    {
        palabra[idx] = '\0';

        int j;
        for (j = 0; palabra[j]; j++)
        {
            palabra[j] = tolower(palabra[j]);
        }
        int pos = -1;
        int i = 0;
        while (i < iNumElementos && pos == -1)
        {
            if (strcmp(palabra, szPalabras[i]) == 0)
            {
                pos = i;
            }
            i++;
        }

        if (pos != -1) {
            iEstadisticas[pos]++;
        }
        else {
            if (iNumElementos < NUMPALABRAS) {
                strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabra);
                iEstadisticas[iNumElementos] = 1;
                iNumElementos++;
            }
        }
    }

    fclose(fp);

    int i, k;
    for (i = 0; i < iNumElementos - 1; i++)
    {
        for (k = i + 1; k < iNumElementos; k++)
        {
            if (strcmp(szPalabras[i], szPalabras[k]) > 0)
            {
                char temp[TAMTOKEN];
                strcpy_s(temp, TAMTOKEN, szPalabras[i]);
                strcpy_s(szPalabras[i], TAMTOKEN, szPalabras[k]);
                strcpy_s(szPalabras[k], TAMTOKEN, temp);

                int aux = iEstadisticas[i];
                iEstadisticas[i] = iEstadisticas[k];
                iEstadisticas[k] = aux;
            }
        }
    }
}



/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
