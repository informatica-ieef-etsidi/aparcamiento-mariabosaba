#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define TARIFA 0.25

int main() {
	char opcion = 1, matricula1[8], matricula2[8] = ("1234ABCD");//Inicializo una de las matriculas, para tener una plaza llena.
	int plaza1 = 0, plaza2 = 1;
	float precio;
	clock_t times = clock(); 
		//hora
    time_t ahora;
    struct tm *hora;
    time(&ahora);
    hora = localtime(&ahora);
    printf("Hora de entrada %d:%d:%d\n", hora->tm_hour, hora->tm_min, hora->tm_sec);
	while (1) {
		system("color 0B");
		printf("BIENVENIDO AL APARCAMIENTO\n");
		printf("MENU PRINCIPAL: \n");
		printf("Seleccione una de estas opciones: \n");
		printf("R - Reservar plaza. \n");
		printf("A - Abandonar plaza. \n");
		printf("E - Estado del aparcamiento. \n");
		scanf_s("%c", &opcion);
		switch (opcion) {
		case'R':
		case'r':
			getchar();
		    printf("Introduzca numero de matricula:\n ");
			if (plaza1 == 0) {
				gets(matricula1);
				printf("La plaza 1 esta libre. \n");
				getchar();
				plaza1 = 1;
			}
			else if (plaza2 == 0) {
				gets(matricula2);
				printf("La plaza 2 esta libre. \n");
				plaza2 = 1;
			}
			else {
				printf("No hay plazas libres. \n");
			}
			break;
		case'A':
		case'a':
			if (plaza1 == 1) {
				plaza1 = 0;//plazas libres cuando se les asigna el cero.
				getchar();
				strcpy(matricula1, "\0");
				printf("La plaza 1 ya esta libre. Gracias por su visita!\n");
				hora = localtime(&ahora);
                                printf("Hora de salida %d:%d:%d\n", hora->tm_hour, hora->tm_min, hora->tm_sec);
				times = (clock() - times)/1000; 
                                precio=TARIFA*times;
                                printf("El precio del aparcamiento es de 0.25 EUROS por segundo. \n");
                                printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n",times);
                                printf("El importe es de:%.2f euros.\n",precio);
                
			}
			else if (plaza2 == 1) {
				plaza2 = 0;
				getchar();
				strcpy(matricula2, "\0");
				printf("La plaza 2 ya esta libre. Gracias por su visita!\n");
				hora = localtime(&ahora);
                                printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
				times = (clock() - times)/1000; 
                                precio=TARIFA*times;
                                printf("El precio del aparcamiento es de 0.25 EUROS por segundo. \n");
                                printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n",times);
                                printf("El importe es de:%.2f euros.\n",precio);
			        }
			else {
				getchar();
				printf("Las dos plazas estan libres\n");
			}
			getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
			break;
		case'E':
		case'e':
			printf("Estado de las plazas: \n");
			if (plaza1 == 0) {
				printf("La plaza 1 esta vacia \n");
			}
			else {
				printf("La plaza 1 esta ocupada-%s\n", matricula1);
			}
			if (plaza2 == 0) {
				printf("La plaza 2 esta vacia \n");
			}
			else{
				printf("La plaza 2 esta ocupada-%s\n", matricula2);
			}
			getchar();//Para que no repita el menu 3 veces por la tecla enter
			getchar();
			break;
		}//llave del switch
		system("cls");
	}
	system("PAUSE");
}
