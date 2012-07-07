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

#include <stdio.h>

#ifndef _MAIN_H_
#define _MAIN_H_

/**
 * Constantes numéricas
 *
 * Edita esto para cambiar los límites
 * del programa
 */
#define MAX_PROCESS 10
#define MAX_RESOURCE 10
#define MAX_RESOURCE_UNIT 10

/**
 * Constantes de texto y macros
 *
 * Constantes y macros que se usan
 * por todo el programa
 */

#define EOL "\n"

// alias para los tipos de lectura
#define READ_RE		0
#define READ_A		1
#define READ_M		2
#define READ_FIRST 	1
#define READ_NEXT	0

#define MANUAL		1
#define AUTO		0

// ternary operator muy usado
#define MATRIX_TYPE type == 1 ? "A" : "M"
#define MATRIX_DESCRIPTION type == 1 ? "recursos asignados" : "recursos necesitados"

// mensajes de información, menús, ayuda, etc.
#define INFO_HELP "TP2-Coffman - 1.0 - Alberto Fernández Martínez\nAsignatura Sistemas Operativos (UNED) - Curso 2011-2012\n\nusage: TP2-Coffman [arguments]\n\nArguments:\n\t-gui\t\tLoad up graphical user interface\n\t-h\t\tShows this help\n"
#define INFO_START "******************************************************\n* Bienvenido al segundo trabajo de Sistemas Operativos\n******************************************************\n* Introduce una de las siguientes opciones:\n*\t- Cargar datos desde un archivo de texto (a)\n*\t- Introducir datos manualmente (m)\n*\t- Salir del programa (e)\n******************************************************\n* Opción: "
#define INFO_FILENAME "* Introduzca el nombre del archivo: "
#define INFO_SAVEFILE "\n* Introduce el nombre del archivo a guardar: "
#define INFO_PARSINGFILE "* Cargando datos desde el fichero de texto...\n*\n"
#define INFO_PARSINGTEXT "* Procesando línea %d: '%s'...\n"
#define INFO_OPTIONFILE "*\n******************************************************\n* Gracias, sus datos han sido cargados correctamente:\n*\t- Ver por pantalla 'v'\n*\t- Escribir en fichero de texto 'w'\n*\t- Ver, escribir y salir 'c'\n******************************************************\n* Opción: "
#define INFO_SUCCESS_WRITE "******************************************************\n* Gracias, los datos se han guardado correctamente en el fichero '%s'\n******************************************************\n"
#define INFO_SUCCESS "\n\n******************************************************\n* Secuencia de autodestrucción iniciada... Ahora sé porque lloráis, \n* pero es algo que yo nunca podrá hacer...\n******************************************************\n"

// mensajes de error
#define ERROR_ARG "TP2-Coffman: invalid option -- '%s'\nUsage: TP2-Coffman [-gui] [-h]\n"
#define ERROR_OPTION "* Opción inválida, vuelve a introducirla ('e' para salir): "
#define ERROR_FILEOPEN "* El archivo especificado '%s' no se pudo abrir.\n"
#define ERROR_LINEDIGIT "*\n* ¡ERROR! En línea %d: se encontró un carácter no permitido. \n* Corriga la entrada y vuelva a intentarlo\n*\n* Saliendo del programa...\n******************************************************\n"
#define ERROR_NUM_RESOURCES "*\n* ¡ERROR! El número de recursos definido en la matrix %s: \n*\n*\t\tLínea %d\n*\t\t'%s'\n*\n* no coincide con el número de recursos (%d) definido en RE\n*\n* Saliendo del programa...\n******************************************************\n"
#define ERROR_NUM_PROCCESS "*\n* ¡ERROR! El número de procesos definidos en la matrix M\n*\tsobrepasa el límite (%d) definido por la matriz A\n*\n* Saliendo del programa...\n******************************************************\n"
#define ERROR_NUM_PROCCESS_MAX "*\n* ¡ERROR! El número de procesos definidos en la matrix M (%d)\n*\tno coincide con los definidos en A (%d)\n*\n* Saliendo del programa...\n******************************************************\n"
#define ERROR_SAVEFILE "* No se pudo acceder al fichero para su escritura, especifique otro\n"
#define ERROR_MAX_RESOURCE_UNIT "*\n* ¡ERROR! El máximo de unidades de cada tipo de recurso (%d), se\n* ha superado (%d) en línea %d, '%s'\n*\n* Saliendo del programa...\n******************************************************\n"
#define ERROR_READ_MATRIX_LINE status == 1 ? "algún número es incorrecto" : (status == 2) ? "máximo de unidades de recursos superado" : "número de recursos inválido"
#define ERROR_MAX_PROCCESS "*\n* ¡ERROR! El máximo de procesos (%d) se ha superado (%d)\n*\n* Saliendo del programa...\n******************************************************\n"

// mensajes de aviso
#define WARNING_MAX_RESOURCES "*\t ¡AVISO! El máximo de recursos es de %d, ignorando el resto...\n*\n"

// mensajes para entrada manual de datos
#define MANUAL_INPUT_MATRIX "*\n* Introduzca la matriz de %s %s (%dx%d) por filas,\n* separando los elementos de cada columna con espacios y terminando\n* cada fila con un intro (entre paréntesis, número de fila):\n"
#define MANUAL_RESOURCE_INFO "*\n* Existen %d recursos, introduzca el número de procesos:\n*\n* Nº de procesos: "
#define MANUAL_RE_KO "*\t -> KO! (%s)\n*\n* RE= "
#define MANUAL_ENTER_RE "* Introduzca el vector de recursos existes de cada tipo\n* Valores separados por espacios, intro para terminar:\n*\n* RE= "
#define MANUAL_MATRIX_OK "*\t -> OK!\n"
#define MANUAL_MATRIX_ROW "* (%d) "
#define MANUAL_MATRIX_KO "*\t -> KO! (%s)\n* (%d) "

// mensajes para resultado del algoritmo
#define COFFMAN_TITLE "RESULTADOS DEL ALGORITMO DE COFFMAN\nDATOS Y MATRICES INICIALES:\n\n"
#define COFFMAN_RD "Rd= "
#define COFFMAN_INIT_X "El estado inicial es X= "
#define COFFMAN_INIT_MARK "Marcado el proceso p%d puesto que no se usa\n"
#define COFFMAN_WITHOUT_MARK "Los procesos sin marcar son: "
#define COFFMAN_PROCCESS_AGAIN "El proceso %d puede ejecutarse, el nuevo estado es:\n"
#define COFFMAN_X "X= "
#define COFFMAN_NOT_DEADLOCK "No hay procesos sin marcar --> ¡NO HAY INTERBLOQUEO!\n"
#define COFFMAN_DEADLOCK "Ningún proceso sin marcar puede ejecutarse --> ¡HAY INTERBLOQUEO!\nLos procesos que se bloquean mutuamente son: "

#define COFFMAN_DATA_RE "Número de recursos: %d\nNúmero de procesos: %d\n\nRE= "
#define COFFMAN_DATA_A "\n\nA=\n\t"
#define COFFMAN_DATA_M "\n\nM=\n\t"

// errores de salida
#define FATAL_ERROR 0x255

/**
 * Estructuras de datos
 *
 * Estas son las estructuras de datos que
 * usaremos a lo largo del programa
 */

/**
 * FILE_STATUS
 *
 * Esta estructura se usa para cuando queremos
 * abrir un archivo, podemos devolver el estado
 * y el nombre del fichero
 */
struct FILE_STATUS_s
{
	int status;
	char* filename;
};

typedef struct FILE_STATUS_s FILE_STATUS;

/**
 * COFFMAN_DATA
 *
 * Se usa para almacenar los datos que necesita
 * el algoritmo de coffman para funcionar
 */
struct COFFMAN_DATA_s
{
	int RE[MAX_RESOURCE];
	int A[MAX_RESOURCE][MAX_PROCESS];
	int M[MAX_RESOURCE][MAX_PROCESS];

	int num_resources;
	int num_proccess;
};

typedef struct COFFMAN_DATA_s COFFMAN_DATA;

// forward declaration
char* read_from_input(FILE* input);
int proccess_arguments(int argc, char* argv[]);
int proccess_options(int show_info);
void proccess_options_file(char* opt, COFFMAN_DATA data_input);
int input_file(char* filename);
void save_to_file(COFFMAN_DATA* input);
void output_coffman(COFFMAN_DATA* data, FILE* target);
void readfile_input();
int read_matrix_line(int type, COFFMAN_DATA* data_input, int* row, int line_length, int num_linea, char* line);
COFFMAN_DATA process_file(FILE* file);
char* trim(char *s, const char *trimChars);
int is_number(char string[]);
int is_number_t(char* s);
char* read_from_input(FILE* input);
int get_int_from_line(char* line, int s, int e);
void init_vector(int* ra, int size);
void print_vector(int vector[], size_t s, FILE* target);
void without_mark(int marked[], size_t s, FILE* target);
void print_matrix(int matrix[MAX_RESOURCE][MAX_PROCESS], int r, int c,  FILE* target);
void print_coffman_data(COFFMAN_DATA* data, FILE* target);
void copy_vector(int *right, int left[], size_t s);
int compare_resource_vector(int left[], int right[], size_t s);
int compare_status(int left[], int right[], size_t s);
int all_proccess_marked(int vector[], size_t s);
void coffman_algorithm(COFFMAN_DATA* data, FILE* target);
void read_manual_matrix(int type, COFFMAN_DATA* data_input);
COFFMAN_DATA manual_entry_read();
void manual_entry();

#endif
