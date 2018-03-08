#include <stdio.h>
#include<stdlib.h>

void main() {
	system("color 0F");
	char opcion = 1, matricula1[8], matricula2[8] = ("1234ABCD");//Inicializo una de las matriculas, para tener una plaza llena.
	int plaza1 = 0, plaza2 = 1;
	while (1) {
		system("color 0F");
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
			printf("Introduzca numero de matricula: \n");
			if (plaza1 == 0) {
				printf("La plaza 1 esta libre. \n");
				getchar();
				gets(matricula1);
				plaza1 = 1;
			}
			else if (plaza2 == 0) {
				printf("La plaza 2 esta libre. \n");
				getchar();
				gets(matricula2);
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
			}
			else if (plaza2 == 1) {
				plaza2 = 0;
				getchar();
				strcpy(matricula2, "\0");
				printf("La plaza 2 ya esta libre. Gracias por su visita!\n");
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
