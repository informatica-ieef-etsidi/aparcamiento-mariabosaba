#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define TARIFACOCHE 0.001
#define TARIFAMOTO 0.0005

/*Ahora hay dos plazas, una para moto y otra para coche, se ha inicializado la plaza 1 como de moto, y la plaza 2 de coche.*/
struct plaza {
	int estado; // 0 - Libre / 1 - Ocupada
	char tipo; // M - Moto / C - Coche
	char matricula[8]; // Formato de la matr�cula: NNNNLLL
};
struct usuario {
	char usuario[50];
	char contrasenia[50];
};

void main() {
	struct plaza plaza1 = { 1,'M',"1234ABC" };
	struct plaza plaza2 = { 0,'C' };
	struct usuario uno = { "Maria","123456" };
	char opcion = 1, opcion2 = 1, introducirmatricula[8], introducirusuario[50], introducircontrasenia[50];
	int comparar = 0, comprobar = 1, comprobar1 = 1, i, j, incorrecto = 0;//comparar y comprobar para comparar las cadenas y para comprobar que la matricula esta bien introducida.
	//int incorrecto para que realice los tres intentos de usuario y contrase�a.
	float precio;
	clock_t times = clock();
	//hora
	time_t ahora;
	struct tm *hora;
	time(&ahora);
	hora = localtime(&ahora);
	//usuario
	printf("Introduzca nombre de usuario: \n");
	gets(introducirusuario);
	printf("Introduzca contrasenia: \n");
	gets(introducircontrasenia);

	do {//do while para repetirlo hasta 3 veces si no es correcto.
		i = 0;
		j = 0;
		while (introducirusuario[i] != '\0'&&uno.usuario[i] != '\0'&&introducircontrasenia[i] != '\0'&&uno.contrasenia[i] != '\0') {
			if (introducirusuario[i] == uno.usuario[i] && introducircontrasenia[i] == uno.contrasenia[i]) {
				j++;//se cuenta las veces que entra al if
			}
			i++;
		}
		if (j == i) {//Si ha entrado i veces en el if, las palabras son iguales.         
			printf("Usuario y contrasenia correctas \n");
			getchar();//Para no saltar tan r�pido el system
			system("cls");//Se borra la pantalla
		}
		else {
			incorrecto++;//Cuenta las veces que es incorrecto, si es igual a 3 sale del programa.
			printf("ERROR. EL USUARIO NO EXISTE \nVuelva a introducir contrasenia y usuario: \n");
			printf("Oportunidad %d/3 \n", incorrecto);
			gets(introducirusuario);
			gets(introducircontrasenia);

		}
		if (incorrecto == 3) {
			printf("Usuario incorrecto, por motivos de seguridad, se cerrara el programa.\n");
			system("PAUSE");//Para salir del programa.
		}
	} while (i != j);
	i = 0;//Copiamos introducir usuario en usuario, e introducir contrase�a en contrase�a.
	while (introducirusuario[i] != '\0'&&uno.usuario[i] != '\0'&&introducircontrasenia[i] != '\0'&&uno.contrasenia[i] != '\0') {
		introducirusuario[i] = uno.usuario[i];
		introducircontrasenia[i] = uno.contrasenia[i];
		i++;
	}
	strcpy(introducirusuario, "\0");//Borramos el usuario y la contrase�a de las variables introducir...
	strcpy(introducircontrasenia, "\0");

	printf("Hora de entrada %d:%d:%d\n", hora->tm_hour, hora->tm_min, hora->tm_sec);
    system("color 0B");
	while (1) {//Bucle infinito, si se pulsa S se sale.
		printf("BIENVENIDO AL APARCAMIENTO\n");
		printf("MENU PRINCIPAL: \n");
		printf("Seleccione una de estas opciones: \n");
		printf("R - Reservar plaza. \n");
		printf("A - Abandonar plaza. \n");
		printf("E - Estado del aparcamiento. \n");
		printf("B - Buscar vehiculo por matricula. \n");
		printf("S - Salir del programa. \n");
		scanf_s("%c", &opcion);
		switch (opcion) {
			getchar();
		case'R':
		case'r':
			/*Para poder detectar si es una moto o un coche he usado un swtich case*/
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			getchar();
			scanf_s("%c", &opcion2);
			switch (opcion2) {
			case'm':
			case'M':
				printf("Introduzca matricula:  \n");
				getchar();
				gets(introducirmatricula);
				i = 0;
				while (i < 4) {
					while (introducirmatricula[i] < 48 || introducirmatricula[i]>59) {//si se cumple esto comprobar es cero y no sale del while.
						comprobar = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 48 && introducirmatricula[i] <= 59) {
						comprobar = 1;//si no ha entrado en el primer while comprobar vale 1 para todo i, despu�s de hacer todas las comprobaciones.
					}
					i++;
				}
				while (i >= 4 && i < 7) {//lo mismo solo que a partir de 4 dado que ah� van las letras.�NICAMENTE V�LIDO PARA LETRAS MAY�SCULAS.
					while (introducirmatricula[i] < 65 || introducirmatricula[i]>96) {
						comprobar1 = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 65 && introducirmatricula[i] <= 96) {
						comprobar1 = 1;
					}
					i++;
				}
				j = 0;
				i = 0;
				while (introducirmatricula[j] != '\0'&&plaza1.matricula[j] != '\0') {
					if (introducirmatricula[j] == plaza1.matricula[j]) {
						i++;//Se cuentan las veces que entra en el if, si son 7(hasta el barra cero) es que son iguales.
					}
					j++;
				}
				while (i == 7) {//Si la numeraci�n es correcta,pero la matricula introducida es igual que la que estaba, tambi�n volver� a pedirla.
					printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
					printf("Vuleve a introducir la matricula: \n");
					getchar();
					gets(introducirmatricula);
					i = 0;//Se inicializa i para que no siempre entre al bucle.
				}
				if (plaza1.estado == 0) {
					printf("La plaza 1 de moto esta libre.\n");
					plaza1.estado = 1;//Se ocupa la plaza
					j = 0;
					while (introducirmatricula[j] != '\0'&&plaza1.matricula[j] != '\0') {//Copiamos en plaza1.matricula introducir matricula, para ocupar la plaza.
						plaza1.matricula[j] = introducirmatricula[j];
						j++;
					}
					plaza1.matricula[j] = '\0';//Asegura que la longitud mas uno es el barracero.
				}
				else {
					printf("Las plazas de moto no estan libres.\n");
				}
				getchar();
				getchar();
				break;
				getchar();
			case'c':
			case'C':
				printf("Introduzca matricula:  \n");//Se hace el mismo procedimiento que el realizado en la moto.
				getchar();
				gets(introducirmatricula);
				i = 0;
				while (i < 4) {
					while (introducirmatricula[i] < 48 || introducirmatricula[i]>59) {
						comprobar = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 48 && introducirmatricula[i] <= 59) {
						comprobar = 1;
					}
					i++;
				}
				while (i >= 4 && i < 7) {
					while (introducirmatricula[i] < 65 || introducirmatricula[i]>96) {
						comprobar1 = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 65 && introducirmatricula[i] <= 96) {
						comprobar1 = 1;
					}
					i++;
				}
				j = 0;
				i = 0;
				while (introducirmatricula[j] != '\0'&&plaza2.matricula[j] != '\0') {
					if (introducirmatricula[j] == plaza2.matricula[j]) {
						i++;
					}
					j++;
				}
				while (i == 7) {
					printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
					printf("Vuleve a introducir la matricula: \n");
					getchar();
					gets(introducirmatricula);
					i = 0;
				}
				if (plaza2.estado == 0) {
					printf("La plaza 1 de coche esta libre.\n");
					plaza2.estado = 1;
					j = 0;
					while (introducirmatricula[j] != '\0'&&plaza2.matricula[j] != '\0') {
						plaza2.matricula[j] = introducirmatricula[j];
						j++;
					}
					plaza2.matricula[j] = '\0';
				}
				else {
					printf("Las plazas de coche no estan libres.\n");
				}
				break;
			}
			comprobar = 1;
			comprobar1 = 1;
			strcpy(introducirmatricula, "\0");
			break;
			getchar();
		case'A':
		case'a':
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			getchar();
			scanf_s("%c", &opcion2);
			switch (opcion2) {
			case 'M':
			case'm':
				if (plaza1.estado == 1) {
					getchar();
					plaza1.estado = 0;
					strcpy(plaza1.matricula, "\0");
					printf("La plaza 1 de moto ya esta libre. Gracias por su visita!\n");
					hora = localtime(&ahora);
					printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
					times = (clock() - times) / 1000;
					precio = TARIFAMOTO * times;
					printf("El precio del aparcamiento es de %f EUROS por segundo. \n", TARIFAMOTO);
					printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n", times);
					printf("El importe es de:%.5f euros.\n", precio);
				}
				else {
					printf("Las dos plazas estan libres\n");
				}
				getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
				break;
			case'C':
			case'c':
				if (plaza2.estado == 1) {
					getchar();
					plaza2.estado = 0;
					strcpy(plaza2.matricula, "\0");
					printf("La plaza 1 de coche ya esta libre. Gracias por su visita!\n");
					hora = localtime(&ahora);
					printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
					times = (clock() - times) / 1000;
					precio = TARIFACOCHE * times;
					printf("El precio del aparcamiento es de %f EUROS por segundo. \n", TARIFACOCHE);
					printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n", times);
					printf("El importe es de:%.2f euros.\n", precio);
				}
				else {
					printf("Las dos plazas estan libres\n");
				}
				getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
				break;
			}
			break;
		case'E':
		case'e':

			printf("Estado de las plazas: \n");
			if (plaza2.estado == 0) {
				printf("La plaza 1 de coche esta vacia \n");
			}
			else {
				printf("La plaza 1 de coche esta ocupada-%s\n", plaza2.matricula);
			}
			if (plaza1.estado == 0) {
				printf("La plaza 1 de moto esta vacia \n");
			}
			else {
				printf("La plaza 1 de moto esta ocupada-%s\n", plaza1.matricula);
			}
			getchar();//Para que no repita el menu 3 veces por la tecla enter
			getchar();
			break;
		case 'B'://Para comprobar que la matricula sigue la numeraci�n, se usa el mismo c�digo que en la reserva.
		case'b':
			getchar();
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			scanf_s("%c", &opcion2);
			switch (opcion2) {
			case'M':
			case'm':
				printf("Introduce numero de matricula: \n");
				getchar();
				gets(introducirmatricula);
				i = 0;
				while (i < 4) {
					while (introducirmatricula[i] < 48 || introducirmatricula[i]>59) {
						comprobar = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 48 && introducirmatricula[i] <= 59) {
						comprobar = 1;
					}
					i++;
				}
				while (i >= 4 && i < 7) {
					while (introducirmatricula[i] < 65 || introducirmatricula[i]>96) {
						comprobar1 = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 65 && introducirmatricula[i] <= 96) {
						comprobar1 = 1;
					}
					i++;
				}
				j = 0;
				i = 0;
				while (introducirmatricula[j] != '\0'&&plaza1.matricula[j] != '\0') {
					if (introducirmatricula[j] == plaza1.matricula[j]) {
						i++;//cuenta las veces que son iguales
					}
					j++;

				}
				if (i == 7) {
					printf("La moto esta aparcada. \n");
				}
				else {
					printf("La moto no esta aparcada. \n");
				}
				break;
			case'c':
			case'C':
				printf("Introduce numero de matricula: \n");
				getchar();
				gets(introducirmatricula);
				i = 0;
				while (i < 4) {
					while (introducirmatricula[i] < 48 || introducirmatricula[i]>59) {
						comprobar = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 48 && introducirmatricula[i] <= 59) {
						comprobar = 1;
					}
					i++;
				}
				while (i >= 4 && i < 7) {
					while (introducirmatricula[i] < 65 || introducirmatricula[i]>96) {
						comprobar1 = 0;
						printf("Error. Asegurese de que la matricula siga la numeracion NNNNLLL.\n");
						printf("Introduzca de nuevo la matricula: \n");
						gets(introducirmatricula);
					}

					if (introducirmatricula[i] >= 65 && introducirmatricula[i] <= 96) {
						comprobar1 = 1;
					}
					i++;
				}
				j = 0;
				i = 0;
				while (introducirmatricula[j] != '\0'&&plaza2.matricula[j] != '\0') {
					if (introducirmatricula[j] == plaza2.matricula[j]) {
						i++;
					}
					j++;
				}
				if (i == 7) {
					printf("El coche esta aparcado. \n");
				}
				else {
					printf("El coche no esta aparcado. \n");
				}
				break;
			}
			getchar();
			break;
		case 'S':
		case's':
			printf("GRACIAS POR SU VISITA. ESPERAMOS VOLVER A VERLE. \n");
			system("PAUSE");
		}//llave del switch
		system("cls");
	}//llave while
}