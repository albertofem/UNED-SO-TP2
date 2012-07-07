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

#include "main.h"

int main(int argc, char* argv[])
{
	// esto es para cargar la interfaz gráfica
	if(proccess_arguments(argc, argv))
	{
		// do something
	}
	else
	{
		// procesamos las opciones hasta que haya una correcta
		int options = proccess_options(READ_FIRST);

		while(options == -1)
		{
			options = proccess_options(READ_NEXT);
		}

		// este switch controla la opción que lanzamos
		switch(options)
		{
		case 0:
			// leer desde un fichero
			readfile_input();
			break;

		case 1:
			// introducir los datos a mano
			manual_entry();
			break;
		}
	}

	return 0x0;
}
