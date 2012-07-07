/**
 * TP2-Coffman, programa creado como ejercicio
 * para la asignatura SO de la UNED
 *
 * Copyright (C) 2011 Alberto Fernández
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Alberto Fernández <albertofem@gmail.com>
 * @version	1.0
 */

#include <stdlib.h>

#include "main.h"

/**
 * compare_resource_vector
 *
 * Esta función compara 2 vectores de recursos
 * para determinar si debemos o no marcar el proceso
 * de la matriz
 */
int compare_resource_vector(int left[], int right[], size_t s)
{
	int i;

	// 0, no se marca
	// 1, se marca
	for(i=0; i<s; i++)
	{
		if(right[i] >= left[i])
			continue;
		else
			return 0;
	}

	return 1;
}

/**
 * compare_status
 *
 * Esta función compara 2 vectores de recursos
 * marcados, se usa para comprobar si de una iteración
 * a otra del algoritmo hemos variado en algo el estado
 */
int compare_status(int left[], int right[], size_t s)
{
	int i;

	// hay que comprobar si el vector de la izquierda es igual
	// o no al de la derecha, si son similares, el interbloqueo
	// existe, sino, se puede seguir con el algoritmo
	// 0 -> podemos seguir el algoritmo
	// 1 -> hay interbloqueo
	for(i=0; i<s; i++)
	{
		if(left[i] != right[i])
			return 0;
	}

	return 1;
}

/**
 * all_proccess_marked
 *
 * Esta función comprueba si todos los elementos
 * del vector de elementos marcados están marcados
 */
int all_proccess_marked(int vector[], size_t s)
{
	int i;

	// 1, todos marcados
	// 0, al menos uno sin marcar
	for(i=0; i<s; i++)
	{
		if(vector[i] != 1)
			return 0;
	}

	return 1;
}

/**
 * coffman_algorithm
 *
 * Función principal para calcular el algoritmo de
 * coffman sobre las matrices A y M y el vector RE
 * El funcionamiento está explicando en la implementación
 */
void coffman_algorithm(COFFMAN_DATA* data, FILE* target)
{
	// primero necesitamos calcular RA
	int i,j;

	// shorcuts
	int p = data->num_proccess;
	int r = data->num_resources;

	// vector RA inicial que necesitamos
	int RA[r];

	// vector RD (alias X), que iremos actualizando
	// conforme progrese el algoritmo, necesitamos
	// una copia puesto que sólo tenemos que actualizarlo
	// en una iteración de todos los procesos sin marcar
	// y vamos a usar el vector para comprobar ciertas condiciones
	int RD[r];
	int RD_copy[r];

	// procesos marcados, también necesitamos una copia
	// puesto que necesitamos comprobar a posteriori (una vez marcados)
	// si coincide con el estado anterior, y si es el mismo estamos
	// ante un interbloqueo
	int marked[p];
	int marked_copy[p];

	int previous=-1;

	int all_marked = 0, deadlock = 0;

	// inicializamos los vectores
	init_vector(RA, r);
	init_vector(RD, r);
	init_vector(marked, p);

	// calculamos el vector RA sumando
	// las filas de la matriz A
	for(i=0; i<p; i++)
	{
		for(j=0; j<r; j++)
		{
			RA[j] += data->A[i][j];
		}
	}

	// calculamos RD(X) restando a RE-A
	for(i=0; i<r; i++)
	{
		RD[i] = data->RE[i] - RA[i];
	}

	fprintf(target, COFFMAN_RD);
		print_vector(RD, r, target);
	fprintf(target, EOL);

	fprintf(target, COFFMAN_INIT_X);
		print_vector(RD, r, target);
	fprintf(target, EOL);

	// ver si hay algun proceso para marcar en A
	for(i=0; i<p; i++)
	{
		// recorremos las columnas
		for(j=0; j<r; j++)
		{
			previous = data->A[i][j];

			// si algún elemento no es 0, salimos
			if(data->A[i][j] != 0)
				break;
		}

		// no ha habido elementos distintos de 0
		// el proceso se marca para no procesarlo
		if(previous == 0)
		{
			marked[i] = 1;
			fprintf(target, COFFMAN_INIT_MARK, i+1);
		}
	}

	// hacemos un bucle infinito, hasta que encontremos
	// un interbloqueo o todos los procesos se marquen
	for(;;)
	{
		// comprobamos si ya están todos marcados
		if(all_proccess_marked(marked, p))
		{
			all_marked = 1;
			break;
		}

		fprintf(target, COFFMAN_WITHOUT_MARK);
			without_mark(marked, p, target);
		fprintf(target, EOL); fprintf(target, EOL);

		// hacemos las copias de marked y RD, puesto que
		// usaremos esto para comprobar el estado interno
		copy_vector(marked_copy, marked, p);
		copy_vector(RD_copy, RD, p);

		// un bloque por procesos, solo cogiendo aquellos sin marcar
		for(i=0; i<p; i++)
		{
			// proceso no marcado, comprobamos ciertas cosas
			if(!marked[i])
			{
				// si la comparación es 0, necesitamos marcar el proceso
				// y actualizar el vector RD, pero usamos RD_copy para los
				// otros procesos de esta interación
				if(compare_resource_vector(data->M[i], RD_copy, r))
				{
					fprintf(target, COFFMAN_PROCCESS_AGAIN, i+1);

					// se marca el proceso
					marked[i] = 1;

					// actualizamos los recoursos en RD
					for(j=0; j<r; j++)
					{
						RD[j] += data->A[i][j];
					}

					fprintf(target, COFFMAN_X); print_vector(RD, r, target); fprintf(target, EOL);
				}
			}
		}

		// si despues del algoritmo los procesos marcados
		// son iguales a los de la fase anterior, deadlock
		if(compare_status(marked, marked_copy, p) == 1)
		{
			deadlock = 1;
			break;
		}
	}

	fprintf(target, EOL);

	// todos los procesos marcados
	if(all_marked)
		fprintf(target, COFFMAN_NOT_DEADLOCK);

	// hemos llegado a un interbloqueo
	if(deadlock)
	{
		fprintf(target, COFFMAN_DEADLOCK);
			without_mark(marked, p, target);
	}
}
