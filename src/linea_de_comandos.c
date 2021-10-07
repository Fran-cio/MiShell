#include "../include/echo.h"
#include "../include/cd.h"
#include "../include/programa_externo.h"
#include "../include/segundo_plano.h"
#include "../include/colorines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void help(void);

void comandos(char* comando)
{   
    comando[strcspn(comando, "\n")] = '\000';

    comando=strtok(comando," ");
    
    if(comando!=NULL)
    {
        if(!strcmp(comando,"quit")||!strcmp(comando,"q"))
        {
            exit(0);
        }

        else if(!strcmp(comando,"cd"))
        {
            cd(comando);
        }

        else if(!strcmp(comando,"clr"))
        {
            printf("\033c");
        }
        //Aviso: Si pones echo hola$PWD no va a parsear el $, la salida sera hola$PWD 
        else if (!strcmp(comando,"echo"))
        {
            echo(comando); 
        }
        else if (!strcmp(comando,"help"))
        {
            help(); 
        }
        else 
        {
            programa_externo(comando);
        }
    }   
}

char* linea()
{   
    char hostname[20];
    gethostname(hostname, 20);
    char *comando;
    comando= (char*) malloc(sizeof(char)*1024);

    printf( ANSI_COLOR_YELLOW "%s@%s" ANSI_COLOR_RESET ":" 
            ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
            getlogin(),hostname,getenv("PWD"));

    fgets(comando,1024,stdin);
    
    return comando;
}

void setear_entorno()
{
    char actual_path[1024];

    strcpy(actual_path,"/home/");
    strcpy(actual_path, strcat(actual_path,getlogin()));

    setenv("PWD",  actual_path, 1);

    chdir(getenv("PWD"));
    setenv("OLDPWD", getenv("PWD"), 1);

    return;
}

void help(void)
{
    printf("Por favor ingrese uno de los siguiente comandos:\n\tclr: Limpia la consola\n\techo <comando|env path>: imprime por pantalla el argumento\n\tcd <path>: Coloca el directorio de trabajo en el path asignado\n\tquit: cierra la consola\nPuede ingresar el path de un programa para ejecutarlo\nPuede ejecutar My_Shell con el path de un script de la manera ./myshell <script>\n");
}
