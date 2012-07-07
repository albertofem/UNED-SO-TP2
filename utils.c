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
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

/**
 * Esta función se ha extraido de internet.
 * Elimina caracteres selectos de un C-string
 */
char* trim(char *s, const char *trimChars)
{
	char *start = s;

	while(*start && strpbrk((const char*)start, trimChars) == start)
		++start;

	char *i = start;
	char *end = start;

	while(*i)
	{
		if(strpbrk(i++, trimChars) != i-1)
		end = i;
	}

	*end = 0;

	return start;
}


/**
 * is_number
 *
 * Esta función comprueba si todos los
 * caracteres de un C-string son digitos
 */
int is_number(char string[])
{
	int i;

	for(i=0; i<strlen(string); i++)
	{
		if(!isdigit(string[i]))
		{
			// si este carácter no es un dígito
			// devolvemos false
			return 0;
		}
	}

	return 1;
}

/**
 * is_number_t
 *
 * Nos dice si un C-string es un número
 */
int is_number_t(char* s)
{
	if(is_number(trim(s, " \t\n\r")))
		return 1;

	return 0;
}

/**
 * read_from_input
 *
 * Esta función se encarga de leer desde un buffer
 * de datos y almacenar en un C-string la línea que
 * acaba de leer. Se usa tanto para leer de 'stdin'
 * que no es más que un buffer de 1 línea, y para leer
 * desde ficheros de texto. En el caso de los ficheros
 * de texto, puesto que esta función opera sobre la
 * dirección de memoria del buffer directamente, al ser
 * llamada seguidamente, leerá una línea tras otra
 */
char* read_from_input(FILE* input)
{
	// reservamos en memoria una cantidad suficiente
	// para las operaciones de este programa
	char* line = malloc(256), *linep = line;
	size_t lenmax = 256, len = lenmax;
	int c;

	// buffer de datos terminado
	if(line == NULL)
		return NULL;

	// bucle ciego
	for(;;)
	{
		// obtener uns carácter
		c = fgetc(input);

		// si el carácter es EOF, hemos terminado
		// con este buffer
		if(c == EOF)
			return NULL;

		// si nos hemos pasado del buffer inicial
		// ampliamos la memoria disponible al doble
		// para poder seguir leyendo
		if(--len == 0)
		{
			// nuevo bloque de memoria
			char* linen = realloc(linep, lenmax *= 2);

			// actualizamos el máximo
			len = lenmax;

			// si no podemos reservar más memoria, liberamos
			// lo reservado e interrumpimos la lectura
			if(linen == NULL)
			{
				free(linep);
				free(linen);

				return NULL;
			}

			// ahora la linea actual contiene
			// el nuevo bloque de memoria redimensionado
			line = linen + (line-linep);
			linep = linen;
		}

		// si la dirección de memoria siguiente
		// a este carácter es \n, terminamos de leer
		if((*line++ = c) == '\n')
			break;
	}

	// almacenamos EOL al final
	*line = '\0';

	// devolvemos la cadena sin retornos de carro, ni tabuladores, etc.
	return trim(linep, " \t\r\n");


}

/**
 * get_int_from_line
 *
 * Función para obtener un 'int' desde un C-string
 * especificando además el rango de posiciones
 */
int get_int_from_line(char* line, int s, int e)
{
	int length = e-s;
	char i_temp[length+1];
	int i;

	// si no vamos a empezar desde el principio
	// movemos el buffer 'line' 's' posiciones
	if(s != 0)
	{
		for(i=0; i<=s; i++)
			line++;
	}

	// hacemos una copia del carácter
	strncpy(i_temp, line, length);

	// añadimos EOL
	i_temp[length] = '\0';

	// si no es un número, esto no tiene sentido.
	// devolvemos el estado -1
	if(!is_number(trim(i_temp, " \t\n\r")))
		return -1;

	// puesto que es un número, lo convertimos
	// usando atoi()
	return atoi(i_temp);
}

/**
 * init_vector
 *
 * Inicializa un vector a 0
 */
void init_vector(int* ra, int size)
{
	int i;

	for(i=0; i<size; i++)
	{
		ra[i] = 0;
	}
}

/**
 * print_vector
 *
 * Imprime un vector en un determinado stream
 */
void print_vector(int vector[], size_t s, FILE* target)
{
	int i;

	fprintf(target, "( ");

	for(i=0; i<s; i++)
	{
		fprintf(target, "%d ", vector[i]);
	}

	fprintf(target, ")");
}

/**
 * without_mark
 *
 * Comprueba que procesos están sin marca
 * y los imprime por pantalla
 */
void without_mark(int marked[], size_t s, FILE* target)
{
	int i;

	for(i=0; i<s; i++)
	{
		if(marked[i] == 0)
		{
			fprintf(target, "p%d ", i+1);
		}
	}
}

/**
 * print_matrix
 *
 * Imprime una de matriz determinada
 */
void print_matrix(int matrix[MAX_RESOURCE][MAX_PROCESS], int r, int c,  FILE* target)
{
	int i,j;

	for(i=0; i<r; i++)
	{

		for(j=0; j<c; j++)
		{
			fprintf(target, "%d\t", matrix[i][j]);
		}

		fprintf(target, "\n\t");
	}
}

/**
 * print_coffman_data
 *
 * Imprime por pantalla los datos (RE, A, M)
 * de un COFFMAN_DATA
 */
void print_coffman_data(COFFMAN_DATA* data, FILE* target)
{

	fprintf(target, COFFMAN_DATA_RE, data->num_resources, data->num_proccess);
		print_vector(data->RE, data->num_resources, target);

	fprintf(target, COFFMAN_DATA_A);
	print_matrix(data->A, data->num_proccess, data->num_resources, target);

	fprintf(target, COFFMAN_DATA_M);
	print_matrix(data->M, data->num_proccess, data->num_resources, target);

	fprintf(target, "\n");
}

/**
 * copy_vector
 *
 * Esta función copia un vector, determinar en el segundo
 * parámetro, al vector en el primero, es decir, reemplaza
 * sus valores por el de left[] ya que lo pasamos por referencia
 */
void copy_vector(int *right, int left[], size_t s)
{
	int i;

	for(i=0; i<s; i++)
	{
		right[i] = left[i];
	}
}
