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

#include "main.h"

/**
 * read_manual_matrix
 *
 * Esta función lee de stdin una fila de una matriz completa
 * y la almacena en data_input, que pasamos por referencia
 */
void read_manual_matrix(int type, COFFMAN_DATA* data_input)
{
	int i;
	char* matrix_line;
	int row=0;

	// puesto que necesitamos comprobar el status de la lectura, esta
	// macro nos ahorrar varias tediosas líneas de código
	#define READ_LINE_STATUS read_matrix_line(type, data_input, &row, strlen(matrix_line), -1, matrix_line)

	printf(MANUAL_INPUT_MATRIX, MATRIX_DESCRIPTION, MATRIX_TYPE, data_input->num_proccess, data_input->num_resources);

	for(i=0; i<data_input->num_proccess; i++)
	{
		printf(MANUAL_MATRIX_ROW, i+1);

		matrix_line = read_from_input(stdin);

		int status = READ_LINE_STATUS;

		// mientras que no lectura buena, seguimos leyendo
		while(status != 0)
		{
			printf(MANUAL_MATRIX_KO, ERROR_READ_MATRIX_LINE, i+1);

			matrix_line = read_from_input(stdin);
			status = READ_LINE_STATUS;
		}

		printf(MANUAL_MATRIX_OK);
	}
}

/**
 * manual_entry_read
 *
 * Función principal para pedir datos
 * al usuario y que los introduzca desde
 * stdin. El funcionamiento está explicado
 * en la implementación
 */
COFFMAN_DATA manual_entry_read()
{
	char* vector_re;
	int num_pro=0;

	COFFMAN_DATA data_input;

	// otra macro para ahorrarnos unas líneas de código
	#define READ_LINE_STATUS_RE read_matrix_line(READ_RE, &data_input, NULL, strlen(vector_re), -1, vector_re)

	printf(MANUAL_ENTER_RE);

	// variable donde vamos a leer RE
	vector_re = read_from_input(stdin);

	int status = READ_LINE_STATUS_RE;

	// mientras no sea un número bueno, probamos...
	while(status != 0)
	{
		printf(MANUAL_RE_KO, ERROR_READ_MATRIX_LINE);

		vector_re = read_from_input(stdin);
		status = READ_LINE_STATUS_RE;
	}

	printf(MANUAL_RESOURCE_INFO, data_input.num_resources);

	// pedimos el número de procesos
	num_pro = atoi(read_from_input(stdin));

	// guardar recursos y procesos
	data_input.num_proccess = num_pro;

	// leer matrices
	read_manual_matrix(READ_A, &data_input);
	read_manual_matrix(READ_M, &data_input);

	return data_input;

}

/**
 * manual_entry
 *
 * Procedimiento para pedir al usuario
 * todos los datos, que posteriormente
 * procesaremos e imprimiremos, similar
 * al modo de lectura de un fichero
 */
void manual_entry()
{
	COFFMAN_DATA rtemp;

	rtemp = manual_entry_read();

	printf(INFO_OPTIONFILE);

	char* opt = read_from_input(stdin);

	proccess_options_file(opt, rtemp);
}
