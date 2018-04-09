#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define TARIFACOCHE 0.001
#define TARIFAMOTO 0.0005
#define N 10//Número de plazas. Se supone que 5 son para moto y otras 5 para coche.
#define NUSUARIOS 5

struct plaza {
	int estado; // 0 - Libre / 1 - Ocupada
	char tipo; // M - Moto / C - Coche
	char matricula[8]; // Formato de la matrícula: NNNNLLL
};
struct usuario {
	char usuario[50];
	char contrasenia[50];
};

void main() {
	struct plaza plazas[N] = { { 1,'M',"1234ABC" }, { 0,'C' } };
	struct usuario usuarios[NUSUARIOS] = { { "Maria","123456" },{"Pedro","34789"} };
	char opcion = 1, opcion2 = 1, introducirmatricula[8], introducirusuario[50], introducircontrasenia[50];
	//Introducir matrícula para comparar las matrículas introducidas por el usuario con las del programa, y si siguen la numeración NNNNLLL.
	//Introeducir contraseña e introducir usuario para comparar si la contraseña y el usuario existen en el programa.
	//Opción 1 y opción para los switch-case.
	int i, j, k, libres = 0, incorrecto = 0;
   //int incorrecto para que realice los tres intentos de usuario y contraseña.
	//libres para comprobar si todas las plazas en opción de reservar no están libres.
	//i,j,k son contadores, i y j para cadenas, y k para el vector de struct plazas.
	double precio;//Tarifa del aparcamiento según el tiempo permanecido en el programa.
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
		for (k = 0;k < NUSUARIOS;k++) {
			i = 0;
			j = 0;
			//Bucle para comparar que el usuario y contraseña introducidos por el usuario son iguales a las variables inicializadas.
		while (introducirusuario[i] != '\0'&&usuarios[k].usuario[i] != '\0'&&introducircontrasenia[i] != '\0'&&usuarios[k].contrasenia[i] != '\0') {
			if (introducirusuario[i] == usuarios[k].usuario[i] && introducircontrasenia[i] == usuarios[k].contrasenia[i]) {
				j++;//se cuenta las veces que entra al if
			}
			i++;
		}
		if (j == i&&j!=0&&i!=0) {//Distintos de cero porque se tienen que inicializar a cero si el usuario y la contraseña son incorrectas para volver a comprobar.
			break;//sale del for, porque si ya ha encontrado al usuario del vector de usuarios, ya ha encontrado el usuario con la k que corresponde, y no tiene que buscar más. 
		}
	}
		if (j == i && j != 0 && i != 0) {//Si ha entrado i veces en el if, las palabras son iguales.         
			printf("Usuario y contrasenia correctas \n");
			getchar();//Para no saltar tan rápido el system
			system("cls");//Se borra la pantalla
			break;//sale del bucle infinito, porque no tiene que volver a comprobar.
		}
		else {
			incorrecto++;//Cuenta las veces que es incorrecto, si es igual a 4 (3 oportunidades) sale del programa.
			printf("ERROR. EL USUARIO NO EXISTE \nVuelva a introducir contrasenia y usuario: \n");
			printf("Oportunidad %d/3 \n", incorrecto);
			gets(introducirusuario);
			gets(introducircontrasenia);

		}
		if (incorrecto == 4) {
			printf("Usuario incorrecto, por motivos de seguridad, se cerrara el programa.\n");
			return;
			break;//Para salir del programa.
		}
	} while (1);//bucle infinito
	strcpy(introducirusuario, "\0");//Borramos el usuario y la contraseña de las variables introducir...
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
		scanf("%c", &opcion);
		switch (opcion) {
			getchar();
		case'R':
		case'r':
			/*Para poder detectar si es una moto o un coche he usado un switch case*/
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			getchar();
			scanf("%c", &opcion2);
			switch (opcion2) {
			case'm':
			case'M':
				printf("Introduzca matricula:  \n");
				getchar();
				gets(introducirmatricula);
				//Se tiene que comprobar que la matrícula no esta inicializada, que siga la numeración NNNNLLL y que no sea mas de ocho caracteres.
				while (1) {
					j = 0;//j contador que correspone a la posición de los caracteres
					while (j < 4) {//primer bucle para que los cuatro primeros caracteres sean números.
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros caracteres son numeros.\n");//En cuanto no sea un número da error, y vuelve a pedir la matrícula.
							printf("Vuelva a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;//Para que vuelva a contar desde cero.
							while (introducirmatricula[7] != '\0') {//Si la vuelve a escribir pero tiene más de ocho caracteres, la vuleve a pedir, comprueba las letras, luego si esta ya introducida, y finalmente los números.
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;//ha comprobado que están todos los números bien y sale del primer bucle.
						}
					}//Si los números están correctos, j vale 4.
					while (j >= 4 && j <= 7) {//Segundo bucle para comprobar las letras, únicamente válido para mayúsculas. Funciona igual que el anterior, pero con intervalo diferente para j.
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelva a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					j = 0;//Inicializamos j para comprobar que la matrícula introducida no pertenece ya al programa.
					i = 0;

					for (k = 0;k < N / 2;k++) {//Vector de structs para cada plaza.
						while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
							if (introducirmatricula[j] == plazas[k].matricula[j]) {
								i++;//Se cuentan las veces que entra en el if, si son 7(hasta el barra cero) es que son iguales.
							}
							else {
								i = 0;//Para que no sume si alguna coincide, y pueda volver a contar 7.
							}
							j++;
						}
					}
					if (i != 7) {
						break;//Si no son iguales, la matrícula está bien, y sale del bucle infinito while.
					}
					while (i == 7) {//Si la numeración es correcta,pero la matricula introducida es igual que la que estaba, también volverá a pedirla.
						printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
						printf("Vuleve a introducir la matricula: \n");
						gets(introducirmatricula);
						while (introducirmatricula[7] != '\0') {
							printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
							gets(introducirmatricula);
						}
						i = 0;
					}
				}

				//Si todas están ocupadas
				for (k = 0;k < N / 2;k++) {//Pra comprobar si están todas las plazas ocupadas.
					if (plazas[k].estado != 0) {
						libres++;
					}
				}
				if (libres == N / 2) {
					printf("No hay plazas libres de moto.\n");
					getchar();
					getchar();
				}
				for (k = 0;k < N / 2;k++) {//Se busca la primera plaza libre.
					if (plazas[k].estado == 0) {
						printf("La plaza %d de moto esta libre.\n", k + 1);
						plazas[k].estado = 1;//Se ocupa la plaza
						plazas[k].tipo = 'M';//Se guarda el tipo.
						break;
					}
				}
				while (introducirmatricula[j] != '\0') {//Copiamos en plazas[k].matricula introducir matricula, para ocupar la plaza.
					plazas[k].matricula[j] = introducirmatricula[j];
					j++;
				}
				plazas[k].matricula[j] = '\0';//Asegura que la longitud mas uno es el barracero.
				break;//En cuanto se guarde se tiene que salir del bucle.
				strcpy(introducirmatricula, "\0");
				getchar();
				getchar();
				break;
				getchar();
			case'c':
			case'C':
				printf("Introduzca matricula:  \n");//Se hace el mismo procedimiento que el realizado en la moto.
				getchar();
				gets(introducirmatricula);
				while (1) {
					j = 0;
					while (j < 4) {
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros carcateres son numeros.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;
						}
					}
					while (j >= 4 && j <= 7) {
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					j = 0;
					i = 0;

					for (k = N / 2;k < N;k++) {//Se comprueba si la matricula introducida ya pertenece al programa.
						while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
							if (introducirmatricula[j] == plazas[k].matricula[j]) {
								i++;//Se cuentan las veces que entra en el if, si son 7(hasta el barra cero) es que son iguales.
							}
							else {
								i = 0;
							}
							j++;
						}
					}
					if (i != 7) {
						break;
					}
					while (i == 7) {//Si la numeración es correcta,pero la matricula introducida es igual que la que estaba, también volverá a pedirla.
						printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
						printf("Vuleve a introducir la matricula: \n");
						gets(introducirmatricula);
						while (introducirmatricula[7] != '\0') {
							printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
							gets(introducirmatricula);
						}
						i = 0;
					}
				}
				for (k = N / 2;k < N;k++) {
					if (plazas[k].estado != 0) {
						libres++;
					}
				}
				if (libres == N) {
					printf("No hay plazas libres de coche.\n");
				}
				for (k = N / 2;k < N;k++) {
					if (plazas[k].estado == 0) {
						printf("La plaza %d de coche esta libre.\n", k + 1);
						plazas[k].estado = 1;
						plazas[k].tipo = 'C';
						break;
					}
				}
				j = 0;
				while (introducirmatricula[j] != '\0') {
					plazas[k].matricula[j] = introducirmatricula[j];
					j++;
				}
				plazas[k].matricula[j] = '\0';
				getchar();
				break;
			}
			strcpy(introducirmatricula, "\0");
			break;
			getchar();
		case'A':
		case'a':
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			getchar();
			scanf("%c", &opcion2);
			switch (opcion2) {
			case 'M':
			case'm':
				printf("Introduzca numero de matricula de la moto que quiere abandonar: \n");
				getchar();
				gets(introducirmatricula);
				while (1) {
					j = 0;
					while (j < 4) {
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros carcateres son numeros.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;
						}
					}
					while (j >= 4 && j <= 7) {
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					break;//Si sale de los dos while es que es correcta y sale del bucle infinito.
				}
				i = 0;//cuenta las veces que son iguales.
				for (k = 0;k < N / 2;k++) {
					j = 0;//Contador de cada caracter.
					while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
						if (introducirmatricula[j] == plazas[k].matricula[j]) {
							i++;
						}
						else {
							i = 0;//Para que si coincide algun caracter,pero no todos, la i vuleva a ser cero y cuente bien cuando son todos iguales.
						}
						j++;
					}
					if (i == j) {
						break;//Para que guarde la posición de la plaza ocupada
					}
				}
				if (i == 0) {
					printf("La matricula introducida no se encuentra en ninguna plaza.\n");
				}
				if (i == j && i != 0) {
					printf("Su plaza de moto se abandonara.\n");
					plazas[k].estado = 0;
					plazas[k].tipo = '\0';
					strcpy(plazas[k].matricula, "\0");
					printf("La plaza %d de moto ya esta libre. Gracias por su visita!\n", k + 1);
					hora = localtime(&ahora);
					printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
					times = (clock() - times) / 1000;
					precio = TARIFAMOTO * times;
					printf("El precio del aparcamiento es de %f EUROS por segundo. \n", TARIFAMOTO);
					printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n", times);
					printf("El importe es de:%.5f euros.\n", precio);
				}
				strcpy(introducirmatricula, "\0");//
				getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
				break;
			case'C':
			case'c':
				printf("Introduzca numero de matricula del coche que quiere abandonar: \n");
				getchar();
				gets(introducirmatricula);
				while (1) {
					j = 0;
					while (j < 4) {
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros carcateres son numeros.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;
						}
					}
					while (j >= 4 && j <= 7) {
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					break;
				}


				i = 0;//cuenta las veces que son iguales.
				for (k = N / 2;k < N;k++) {
					j = 0;
					while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
						if (introducirmatricula[j] == plazas[k].matricula[j]) {
							i++;
						}
						else {
							i = 0;//Para que si coincide algun caracter,pero no todos, la i vuleva a ser cero y cuente bien cuando son todos iguales.
						}
						j++;
					}
					if (j == i) {
						break;
					}
				}
				if (i == 0) {
					printf("La matricula no se encuentra en ninguna plaza.\n");
				}
				if (i == j && i != 0) {
					printf("Su plaza de coche se abandonara.\n");
					plazas[k].estado = 0;
					plazas[k].tipo = '\0';
					strcpy(plazas[k].matricula, "\0");
					printf("La plaza %d de coche ya esta libre. Gracias por su visita!\n", k + 1);
					hora = localtime(&ahora);
					printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
					times = (clock() - times) / 1000;
					precio = TARIFACOCHE * times;
					printf("El precio del aparcamiento es de %f EUROS por segundo. \n", TARIFACOCHE);
					printf("Su vehiculo a permanecido en nuestro establecimiento %d segundos.\n", times);
					printf("El importe es de:%.5f euros.\n", precio);
				}
				getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
				strcpy(introducirmatricula, "\0");
				break;
			}
			break;
		case'E':
		case'e':

			printf("Estado de las plazas de moto: \n");
			for (k = 0;k < N / 2;k++) {
				if (plazas[k].estado == 0) {
					printf("La plaza %d de moto esta vacia \n", k + 1);
				}
				else {
					printf("La plaza %d de coche esta ocupada-%s\n", k + 1, plazas[k].matricula);
				}
			}
			getchar();
			getchar();
			system("cls");
			printf("Estado de las plazas de coche: \n");
			for (k = N / 2;k < N;k++) {
				if (plazas[k].estado == 0) {
					printf("La plaza %d de coche esta vacia \n", k + 1);
				}
				else {
					printf("La plaza %d de coche esta ocupada-%s\n", k + 1, plazas[k].matricula);
				}
			}
			getchar();//Para que no repita el menu 3 veces por la tecla enter
			getchar();
			break;
		case 'B'://Para comprobar que la matricula sigue la numeración, se usa el mismo código que en la reserva.
		case'b':
			getchar();
			printf("Pulse la tecla M si su vehiculo es una moto \n");
			printf("Pulse la tecla C si su vehiculo es un coche \n");
			scanf("%c", &opcion2);
			switch (opcion2) {
			case'M':
			case'm':
				printf("Introduce numero de matricula: \n");
				getchar();
				gets(introducirmatricula);
				while (1) {
					j = 0;
					while (j < 4) {
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros carcateres son numeros.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;
						}
					}
					while (j >= 4 && j <= 7) {
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					break;
				}
				j = 0;
				i = 0;
				for (k = 0;k < N / 2;k++) {
					while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
						if (introducirmatricula[j] == plazas[k].matricula[j]) {
							i++;//cuenta las veces que son iguales
						}
						else {
							i = 0;
						}
						j++;
					}
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
				while (1) {
					j = 0;
					while (j < 4) {
						if (introducirmatricula[j] < 48 || introducirmatricula[j]>57) {
							printf("Error, asegurese de que los cuatro primeros carcateres son numeros.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 0;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 4) {
							break;
						}
					}
					while (j >= 4 && j <= 7) {
						if (introducirmatricula[j] < 65 || introducirmatricula[j]>90) {
							printf("Error, asegurese de que los tres ultimos carcateres son letras.\n");
							printf("Vuelve a introducir la matricula: \n");
							gets(introducirmatricula);
							j = 4;
							while (introducirmatricula[7] != '\0') {
								printf("Error, asegurese que la matricula tiene ocho caracteres.\n");
								gets(introducirmatricula);
							}
						}
						else {
							j++;
						}
						if (j == 7) {
							break;
						}
					}
					break;
				}
				j = 0;
				i = 0;
				for (k = N / 2;k < N;k++) {
					while (introducirmatricula[j] != '\0'&&plazas[k].matricula[j] != '\0') {
						if (introducirmatricula[j] == plazas[k].matricula[j]) {
							i++;
						}
						else {
							i = 0;
						}
						j++;
					}
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
			return;
		}//llave del switch
		system("cls");
	}//llave while
}