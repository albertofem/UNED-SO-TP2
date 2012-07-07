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
 * process_arguments
 *
 * Esta función procesa los argumentos por línea
 * de comandos y devuelve estados asociados a cada
 * opción, para ser gestionada externamente
 */
int proccess_arguments(int argc, char* argv[])
{
	if(argc > 1)
	{
		if(strcmp(argv[1], "-h") == 0)
		{
			printf(INFO_HELP);
			return 0;
		}
		else
		{
			printf(ERROR_ARG, argv[1]);
			exit(FATAL_ERROR);
		}
	}

	return 0;
}

/**
 * process_options
 *
 * Esta función procesa las opciones introducidas
 * en 'stdin', y devuelve estados para ser gestionados
 * externamente
 */
int proccess_options(int show_info)
{
	if(show_info)
		printf(INFO_START);

	char* opt = read_from_input(stdin);

	if(opt != NULL)
	{
		// check options
		if(strcmp(opt, "a") == 0)
		{
			// leer desde fichero, estado 0
			return 0;
		}
		else if(strcmp(opt, "m") == 0)
		{
			// entrar datos a mano, estado 1
			return 1;
		}
		else if(strcmp(opt, "e") == 0)
		{
			// salir
			exit(0x0);
		}
		else
		{
			// opción incorrecta, estado -1
			printf(ERROR_OPTION);
			return -1;
		}
	}

	return -1;
}

/**
 * process_options_file
 *
 * Procesa las opciones de cuando vamos
 * a mostrar el resultado del algoritmo
 * por pantalla, escribirlo, etc.
 */
void proccess_options_file(char* opt, COFFMAN_DATA data_input)
{
	// tanto si es 'v' como 'c', imprimimos la información
	int write = strcmp(opt, "c");

	if(strcmp(opt, "v") == 0 || write == 0)
	{
		// imprimir en 'stdout'
		printf(EOL);
		output_coffman(&data_input, stdout);

		if(write)
			printf(INFO_SUCCESS);
	}

	// si es 'w' o 'c', escribimos la información en un fichero
	if(strcmp(opt, "w") == 0 || strcmp(opt, "c") == 0)
	{
		save_to_file(&data_input);
	}
}
