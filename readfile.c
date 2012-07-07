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
 * input_file
 *
 * Función principal para operar sobre el fichero de texto
 *
 * Primero intentamos leer el fichero, a continuación
 * lo procesamos y pedimos las opciones correspondientes
 * al usuario
 */
int input_file(char* filename)
{
	FILE *ifile;
	ifile = fopen(filename, "r");

	COFFMAN_DATA data_input;

	// fichero inaccesible
	if(ifile == NULL)
	{
		printf(ERROR_FILEOPEN, filename);
		return -1;
	}

	// fichero abierto, podemos proseguir
	data_input = process_file(ifile);

	printf(INFO_OPTIONFILE);

	char* opt = read_from_input(stdin);

	proccess_options_file(opt, data_input);

	return 0;
}

/**
 * save_to_file
 *
 * Función para guardar en un fichero
 * el resultado de aplicar los algoritmos
 * a un COFFMAN_DATA
 */
void save_to_file(COFFMAN_DATA* input)
{
	printf(INFO_SAVEFILE);
	char* file_name = read_from_input(stdin);

	// tratamos de abrir el fichero
	FILE* target_file = fopen(file_name, "w");

	// mientras no podamos abrirlo vamos a seguir
	// solicitando el fichero
	while(target_file == NULL)
	{
		printf(ERROR_SAVEFILE);
		printf(INFO_SAVEFILE);

		file_name = read_from_input(stdin);
		target_file = fopen(file_name, "w");
	}

	// guardamos el resultado en el 'target_file'
	output_coffman(input, target_file);
	fclose(target_file);

	printf(INFO_SUCCESS_WRITE, file_name);
}

/**
 * output_coffman
 *
 * Sirve para imprimir en un stream el resultado
 * del algoritmo de coffman, que también se
 * calcula dentro de esta función
 */
void output_coffman(COFFMAN_DATA* data, FILE* target)
{
	fprintf(target, COFFMAN_TITLE);

	print_coffman_data(data, target);
	coffman_algorithm(data, target);
}

/**
 * readfile_input
 *
 * Esta función es el nexo de entrada para las
 * opciones a la hora de leer un fichero
 */
void readfile_input()
{
	int status = -1;

	while(status == -1)
	{
		printf(INFO_FILENAME);

		char* fname;
		fname = read_from_input(stdin);

		// comprobación de seguridad
		if(fname != NULL)
		{
			// para salir del bucle
			if(strcmp(fname, "e") == 0)
			{
				return;
			}

			// leemos el fichero, si el status devuelto
			// es != -1, el bucle terminará y el programa
			// acabará
			status = input_file(fname);
		}
		else
		{
			// fatal error
			exit(FATAL_ERROR);
		}
	}
}

/**
 * read_matrix_line
 *
 * Esta función genérica nos sirve
 * para leer una línea de una matriz/vector
 * cualquiera, y almacenar los datos en un
 * COFFMAN_DATA. Funciona a varios niveles:
 *
 * Se presupone como entrada una línea ya sin caracteres
 * 'basura' (sin RE=, A=, etc.) y trimeada, y obtendrá
 * los números definidos, sea cual sea sus longitudes
 *
 * Si line_length = -1, la función devuelve estados
 * que se usan en la lectura manual (para indicar error)
 *
 * Por otro lado, se modifica directamente la estructura
 * COFFMAN_DATA que se pasa por referencia, por lo que
 * sólo devuelves estados de operaciones
 */
int read_matrix_line(int type, COFFMAN_DATA* data_input, int* row, int line_length, int num_linea, char* line)
{
	int i;
	int num_get;

	// first nos indica si estamos leyendo el
	// primer número, look_next hasta que carácter
	// hay que leer en la siguiente iteración
	int first=1, look_next=0;

	// aquí almacenamos qué columna estamos procesando
	int col=0;

	// pasamos ahora a analizar la línea carácter por carácter
	for(i=0; i<line_length; i++)
	{
		// primeros extraemos, si estamos en la línea primera, los recursos
		if(line[i] == ' ' || i == line_length-1)
		{
			// buscamos hasta la proxima aparición de espacio
			if(first)
			{
				// leer primer número
				num_get = get_int_from_line(line, 0, i);
				first = 0;
			}
			else
				num_get = get_int_from_line(line, look_next, i);

			look_next = i;

			/**
			 * comprobamos los distintos errores posibles
			 * en el caso de lectura de fichero, si hay un
			 * error paramos el programa, si es lectura
			 * manual devolvemos un estado para que el usuario
			 * siga probando a introducir el dato bueno
			 */
			if(num_get == -1)
			{
				// numero incorrecto
				if(num_linea == -1)
					return 1;

				printf(ERROR_LINEDIGIT, num_linea);
				exit(FATAL_ERROR);
			}
			else if(num_get > MAX_RESOURCE_UNIT)
			{
				if(type == READ_RE)
					data_input->num_resources = 0;

				// máximo de recursos alcanzado
				if(num_linea == -1)
					return 2;

				printf(ERROR_MAX_RESOURCE_UNIT, MAX_RESOURCE_UNIT, num_get, num_linea, line);
				exit(FATAL_ERROR);
			}
			else
			{
				// almacenamos el número...
				// para cada tipo de lectura:
				//	0 -> RE
				//	1 -> A
				//	2 -> M
				if(type == READ_RE)
				{
					// si hemos sobrepasado el maximo número
					// de recursos, damos un aviso, e ignoramos
					// el resto de datos
					if(col+1 > MAX_RESOURCE)
					{
						printf(WARNING_MAX_RESOURCES, MAX_RESOURCE);
						break;
					}

					data_input->RE[col] = num_get;
				}
				else if(type == READ_A)
				{
					data_input->A[*row][col] = num_get;
				}
				else
				{
					data_input->M[*row][col] = num_get;
				}

				col++;
			}
		}
	}

	// si estamos leyendo matrices, hacemos
	// unas comprobaciones extra
	if(type == READ_M || type == READ_A)
	{
		if(data_input->num_resources != col)
		{
			// no coinciden las columnas con los recursos
			if(num_linea == -1)
				return 3;

			printf(ERROR_NUM_RESOURCES, MATRIX_TYPE, num_linea, line, data_input->num_resources);
			exit(FATAL_ERROR);
		}

		// puesto que esta función necesita saber que
		// columna está leyendo, si todo ha ido bien
		// aumentamos esta variable, que previamente se ha
		// pasado por referencia
		(*row)++;
	}

	if(type == READ_RE)
		data_input->num_resources = col;

	return 0;
}

/**
 * proccess_file
 *
 * Función para procesar el archivo de texto
 * que leerá por líneas, hará comprobaciones
 * y obtendrá gracias a la función anterior, todos
 * los datos que necesitamos, para almacenarlos
 * en un COFFMAN_DATA que luego se le pasará al
 * algoritmo
 */
COFFMAN_DATA process_file(FILE* file)
{
	// leemos la primera línea
	char* line = read_from_input(file);

	// variables auxiliares
	int num_linea=1;

	// por defecto tenemos -1 procesos
	// para compensar el offset de los contadores
	// de arrays
	int num_proccess=-1;

	// token para la segunda fase
	int second_phase=0;

	// filas que estamos leyendo, tanto en A
	// como en M
	int row_a=0, row_m=0;

	COFFMAN_DATA data_input;

	printf(INFO_PARSINGFILE);

	// bucle por líneas
	while(line != NULL)
	{
		printf(INFO_PARSINGTEXT, num_linea, line);

		// si estamos en la primera línea, comprobamos
		// que estén bien los primeros caracteres
		if(num_linea == 1)
		{
			if(line[0] != 'R' || line[1] != 'E' || line[2] != '=')
			{
				printf(ERROR_LINEDIGIT, num_linea);
				exit(FATAL_ERROR);
			}

			// todo bien, limpiamos la línea y procesamos
			line = trim(line, "\t\n\rRE= ");

			// obtener los datos en RE
			read_matrix_line(READ_RE, &data_input, NULL, strlen(line), num_linea, line);
		}
		else if(num_linea == 2)
		{
			// procedemos cono en RE=
			if(line[0] != 'A' || line[1] != '=')
			{
				printf(ERROR_LINEDIGIT, num_linea);
				exit(FATAL_ERROR);
			}

			line = trim(line, "\t\n\r=A ");

			// obtener datos de A (primera linea)
			read_matrix_line(READ_A, &data_input, &row_a, strlen(line), num_linea, line);

		}
		else
		{
			// no nos queda más remedio que ir buscando por la línea
			// hasta encontrar el M=
			if(line[0] == 'M')
			{
				// encontramos M y comprobamos su formato
				if(line[1] != '=')
				{
					printf(ERROR_LINEDIGIT, num_linea);
					exit(FATAL_ERROR);
				}
				else
				{
					// estamos ya en la matriz M, sabemos ya cuantos procesos hay
					data_input.num_proccess = num_proccess;

					// ya estamos en la segunda fase, en donde
					// solo leeremos elementos de M
					second_phase=1;

					// limpiamos y procesamos...
					line = trim(line, "\t\n\r=M ");

					// leemos la primera línea de M
					read_matrix_line(READ_M, &data_input, &row_m, strlen(line), num_linea, line);
				}
			}
			else
			{
				// si hemos alcanzado el límite de procesos, mal vamos, tiramos
				// error porque no coinciden en ambas matrices el número de procesos
				if(row_m+1 > row_a)
				{
					printf(ERROR_NUM_PROCCESS, row_a);
					exit(FATAL_ERROR);
				}

				// si estamos en segunda fase, ya hemos encontrado M, leemos procesos
				// de M, sino, leemos procesos de A
				read_matrix_line((second_phase ? READ_M : READ_A), &data_input, (second_phase ? &row_m : &row_a), strlen(line), num_linea, line);
			}
		}

		// leemos una nueva línea
		line = read_from_input(file);

		num_linea++;

		// si aun no estamos en segunda fase, es que seguimos
		// leyendo procesos de A, por lo que hay que contar
		// cuantos procesos llevamos
		if(!second_phase)
			num_proccess++;
	}

	// hemos terminado ya, veamos si M tiene las mismas columnas que A
	if(row_m != row_a)
	{
		printf(ERROR_NUM_PROCCESS_MAX, row_m, row_a);
		exit(FATAL_ERROR);
	}

	data_input.num_proccess = num_proccess;

	// finalmente, si hemos sobrepasado el numero de procesos
	// permitido, no podemos continuar...
	if(num_proccess > MAX_PROCESS)
	{
		printf(ERROR_MAX_PROCCESS, MAX_PROCESS, num_proccess);
		exit(FATAL_ERROR);
	}

	return data_input;
}
