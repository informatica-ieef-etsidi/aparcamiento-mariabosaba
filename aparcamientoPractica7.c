#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define TARIFA 0.0005
#define N 50//Número de plazas. Se supone que 5 son para moto y otras 5 para coche.
//#define NUSUARIOS 5
/*En esta última práctica se va a trabajar con la persistencia de los datos en ficheros, de modo que se guarde la información del programa y se pueda arrancar/cerrar el mismo sin afectar a los datos.

Los datos del aparcamiento se van a almacenar en un fichero con un formato que podría ser el siguiente:

1 M 9999KKK
0 M -------
1 C 1234BBB
0 C -------
0 M -------
0 C -------
0 C -------

void salvarFichero(char nombreFichero[], struct plaza aparcamiento[], int dim);
donde cada una de las funciones recibe el nombre del fichero del que tiene que leer o escribir los datos. En cada una de las funciones se tiene que abrir el fichero, trabajar con él y cerrar el fichero:
La función salvarFichero() abre el fichero en modo escritura y salva los datos del vector aparcamiento en el fichero. El parámetro dim es el número total de plazas.

7.1. Avanzado
Añade en el menú una opción para generar un ticket de pago. Esto generará un fichero que tenga como nombre la hora de salida (para ello el alumno debe utilizar la librería time.h. El ticket generado tendrá los datos de la empresa, la matrícula del vehículo, la hora de entrada y de salida y el importe total con el desglose del precio (precio base e IVA). Impleméntalo con una función.*/
char menu();
int esDigitoValido(char caracter);
int esLetraValida(char caracter);
int esMatriculaValida(char matricula[]);
int existeUsuario(struct usuario usuarioValido, char username[], char password[]);
void recuento(struct plaza aparcamiento[], int dim, int *nLibresCoches, int *nLibresMotos);
void inicializar(struct plaza aparcamiento[], int dim);
int buscarPlazaLibre(struct plaza aparcamiento[], int dim, char tipo);
int buscarVehiculo(struct plaza aparcamiento[], int dim, char matricula[]);
void ordenarmatriculas(struct plaza aparcamiento[], int dim);
void leerFichero(char nombreFichero[], struct plaza aparcamiento[], int * dim);
void salvarFichero(char nombreFichero[], struct plaza aparcamiento[], int dim);
void ticket(struct plaza nplaza,time_t ahora1);
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
	struct plaza plazas[N];
	struct usuario usuarios = {"Maria","123456A" };
	char opcion = 1, opcion2 = 1, introducirmatricula[8], introducirusuario[50], introducircontrasenia[50];
	int j,libres = 0, incorrecto = 0, ncoches, nmotos, nplazas;
	FILE *entrada;
	leerFichero(&entrada, plazas, &nplazas);
	clock_t times = clock();
	//hora
	time_t ahora1;
	struct tm *hora1;
	time(&ahora1);
	hora1 = localtime(&ahora1);
	//usuario
	printf("Introduzca nombre de usuario: \n");
	gets(introducirusuario);
	printf("Introduzca contrasenia: \n");
	gets(introducircontrasenia);
	while (1) {

		if (existeUsuario(usuarios, introducirusuario, introducircontrasenia) == 1) {
			printf("Contrasenia y usuario correctos.\n");
			break;
		}
		else if (existeUsuario(usuarios, introducirusuario, introducircontrasenia) == 0) {
			printf("ERROR. Vuelva a introducir usuario y contrasenia:\n");
			gets(introducirusuario);
			gets(introducircontrasenia);
		}
	}
	strcpy(introducirusuario, "\0");//Borramos el usuario y la contraseña de las variables introducir...
	strcpy(introducircontrasenia, "\0");
	getchar();
	getchar();
	system("cls");
	printf("Hora de entrada %d:%d:%d\n", hora1->tm_hour, hora1->tm_min, hora1->tm_sec);
	//inicializar(plazas, nplazas); Si tenemos las plazas en un fichero esta función ya no es necesaria.
	while (1) {
		system("color 79");
		opcion = menu();
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
				libres = buscarPlazaLibre(plazas, nplazas, opcion2);
				if (libres != -1) {
					printf("La plaza %d esta libre:\n", libres + 1);
					printf("Introduzca matricula:  \n");
					getchar();
					gets(introducirmatricula);
					//Se tiene que comprobar que la matrícula no esta inicializada, que siga la numeración NNNNLLL y que no sea mas de ocho caracteres
					while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
						printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
						gets(introducirmatricula);
					}
					while (buscarVehiculo(plazas, nplazas, introducirmatricula) != -1) {//Si la numeración es correcta,pero la matricula introducida es igual que la que estaba, también volverá a pedirla.
						printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
						printf("Vuleve a introducir la matricula: \n");
						gets(introducirmatricula);
						while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
							printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
							gets(introducirmatricula);
						}
					}
					printf("Matricula correcta! Se ha reservado la plaza %d para usted.\n", libres + 1);
					j = 0;
					while (introducirmatricula[j] != '\0') {//Copiamos en plazas[libres].matricula introducir matricula, para ocupar la plaza.
						plazas[libres].matricula[j] = introducirmatricula[j];
						j++;
					}
					plazas[libres].matricula[j] = '\0';//Asegura que la longitud mas uno es el barracero.
					plazas[libres].tipo = 'M';
					plazas[libres].estado = 1;
					salvarFichero(&entrada, plazas, nplazas);
					strcpy(introducirmatricula, "\0");
				}
				else {
					printf("No hay plazas libres de moto. Lo sentimos.\n");
				}
				getchar();
				break;
				getchar();
			case'c':
			case'C':
				libres = buscarPlazaLibre(plazas, nplazas, opcion2);
				if (libres != -1) {
					printf("La plaza %d esta libre.\n", libres);
					printf("Introduzca matricula:  \n");//Se hace el mismo procedimiento que el realizado en la moto.
					getchar();
					gets(introducirmatricula);
					while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
						printf("Error, recuerde que la amtricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
						gets(introducirmatricula);
					}
					while (buscarVehiculo(plazas, nplazas, introducirmatricula) != -1) {//Si la numeración es correcta,pero la matricula introducida es igual que la que estaba, también volverá a pedirla.
						printf("ERROR. La matricula introducida ya se encuentra en el sistema.\n");
						printf("Vuleve a introducir la matricula: \n");
						gets(introducirmatricula);
						while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
							printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
							gets(introducirmatricula);
						}
					}
					printf("Matricula correcta! Se ha reservado la plaza %d para usted.\n", libres + 1);
					plazas[libres].estado = 1;
					plazas[libres].tipo = 'C';
					j = 0;
					while (introducirmatricula[j] != '\0') {
						plazas[libres].matricula[j] = introducirmatricula[j];
						j++;
					}
					salvarFichero(&entrada, plazas, nplazas);
					plazas[libres].matricula[j] = '\0';
					strcpy(introducirmatricula, "\0");
				}
				else {
					printf("No hay plazas de coche libres. Lo sentimos.\n");
				}
				break;
			}
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
				while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
					printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
					gets(introducirmatricula);
				}
				libres = buscarVehiculo(plazas, nplazas, introducirmatricula);
				if (libres == -1) {
					printf("La matricula introducida no se encuentra en ninguna plaza.\n");
				}
				else {
					printf("Su plaza de moto se abandonara.\n");
					plazas[libres].estado = 0;
					strcpy(plazas[libres].matricula, "-------");
					salvarFichero(&entrada, plazas, nplazas);
					printf("La plaza %d de moto ya esta libre. Gracias por su visita!\n", libres + 1);
					printf("En breves momentos se imprimira el ticket de pago.\n");
					ticket(plazas[libres],ahora1);
				}
				strcpy(introducirmatricula, "\0");//
				getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
				break;
			case'C':
			case'c':
				printf("Introduzca numero de matricula del coche que quiere abandonar: \n");
				getchar();
				gets(introducirmatricula);
				while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
					printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
					gets(introducirmatricula);
				}
				libres = buscarVehiculo(plazas, nplazas, introducirmatricula);
				if (libres == -1) {
					printf("La matricula no se encuentra en ninguna plaza.\n");
				}
				else {
					printf("Su plaza de coche se abandonara.\n");
					plazas[libres].estado = 0;
					strcpy(plazas[libres].matricula, "-------");
					salvarFichero(&entrada, plazas, nplazas);
					printf("La plaza %d de coche ya esta libre. Gracias por su visita!\n", libres + 1);
					printf("En breves momentos se imprimira el ticket de pago.\n");
					ticket(plazas[libres],ahora1);
				}
			}
			getchar();//Para que el usuario pueda ver la accion que se ha llevado a cabo antes del "cls"
			strcpy(introducirmatricula, "\0");
			break;
			break;
		case'E':
		case'e':
			recuento(plazas, nplazas, &ncoches, &nmotos);
			printf("Estado de las plazas de moto: \n");
			printf("Numero de plazas de moto: %d\n", nmotos);
			getchar();
			printf("Estado de las plazas de coche: \n");
			printf("Numero de plazas de coche: %d\n", ncoches);
			getchar();
			printf("Matriculas ocupadas por orden alfabetico:\n");
			ordenarmatriculas(plazas, nplazas);
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
				while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
					printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
					gets(introducirmatricula);
				}
				libres = buscarVehiculo(plazas, nplazas, introducirmatricula);
				if (libres != -1) {
					printf("La moto esta aparcada en la plaza %d \n", libres);
				}
				else {
					printf("La moto no esta aparcada. \n");
				}
				break;
			case'c':
			case'C':
				printf("Introduce numero de matricula: \n");
				gets(introducirmatricula);
				while (introducirmatricula[7] != '\0' || esMatriculaValida(introducirmatricula) == 0) {
					printf("Error, recuerde que la matricula no puede contener mas de ocho carcteres y que sigue la numeracion NNNNLLL.\n");
					gets(introducirmatricula);
				}
				libres = buscarVehiculo(plazas, nplazas, introducirmatricula);
				if (libres != -1) {
					printf("El coche esta aparcado en la plaza %d \n", libres);
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
	}//while
}
char menu(){
	char letra;
		printf("BIENVENIDO AL APARCAMIENTO\n");
		printf("MENU PRINCIPAL: \n");
		printf("Seleccione una de estas opciones: \n");
		printf("R - Reservar plaza. \n");
		printf("A - Abandonar plaza. \n");
		printf("E - Estado del aparcamiento. \n");
		printf("B - Buscar vehiculo por matricula. \n");
		printf("S - Salir del programa. \n");
		scanf("%c", &letra);
	return letra;
}
int esDigitoValido(char caracter) {
	int digitovalido;
	if (caracter <48||caracter>57 ){
		digitovalido = 0;
	}
	else if (caracter >= 48 && caracter <= 57) {
		digitovalido = 1;
	}
	return digitovalido;
}
int esLetraValida(char caracter) {
	int letravalida;
	if (caracter < 65 || caracter>90||caracter=='A'||caracter=='E'||caracter=='I'||caracter=='O'||caracter=='U') {
		letravalida = 0;
	}
	else if (caracter >= 65 && caracter <= 90) {
		letravalida = 1;
	}
	return letravalida;
}
int esMatriculaValida(char matricula[]) {
	int valida, i;
	i = 0;
	valida = 0;
	while (matricula[i] != '\0') {
		if(i < 4) {
			if (esDigitoValido(matricula[i]) == 1) {
				valida = 1;
			}
			else {
				valida = 0;
				break;
			}
		}
		else if (i >= 4 && i < 7) {
			if (esLetraValida(matricula[i]) == 1) {
				valida = 1;
			}
			else {
				valida = 0;
				break;
			}
		}
		i++;
	}
		return valida;
}
int existeUsuario(struct usuario usuarioValido, char usuario[], char contrasenia[]) {
	int validousuario, validacontrasenia, valido;
	validousuario = strcmp(usuarioValido.usuario, usuario);
	validacontrasenia = strcmp(usuarioValido.contrasenia, contrasenia);
	if (validousuario == 0 && validacontrasenia == 0) {
		valido = 1;
	}
	else {
		valido = 0;
	}
	return valido;
}
void recuento(struct plaza aparcamiento[], int dim, int *nLibresCoches, int *nLibresMotos) {
	int i;
	*nLibresCoches = 0;
	*nLibresMotos = 0;
	for (i = 0;i < dim ;i++) {
		if (aparcamiento[i].estado == 0&&aparcamiento[i].tipo=='M') {
			*nLibresMotos = *nLibresMotos + 1;
		}
		else if (aparcamiento[i].estado == 0 && aparcamiento[i].tipo == 'C') {
			*nLibresCoches = *nLibresCoches + 1;
		}
	}
}
void inicializar(struct plaza aparcamiento[], int dim) {//Como se sacan datos de un fichero de texto, no es necesario nombrar esta función.
	int i;
	for (i = 0;i < dim / 2;i++) {
		aparcamiento[i].estado = 0;
		aparcamiento[i].tipo = 'M';
	}
	for (i = dim / 2;i < dim;i++) {
		aparcamiento[i].estado = 0;
		aparcamiento[i].tipo = 'C';
	}
}
int buscarPlazaLibre(struct plaza aparcamiento[], int dim, char tipo) {
	int i;
	for (i = 0;i < dim;i++) {
	      
		if (tipo == 'M'||tipo=='m') {

			if (aparcamiento[i].estado == 0) {
				return i;
				break;
			}
			if (aparcamiento[i].estado == 1 && i == dim - 1) {
				return -1;
			}
		}
	    else if (tipo == 'C'||tipo=='c') {
			if (aparcamiento[i].estado == 0) {
				return i;
				break;
			}
			if (i == dim - 1 && aparcamiento[i].estado == 1) {
				return -1;
			}
		}
	}
}
/*/*La función buscarVehiculo() permite buscar un vehículo por número de matrícula. La función devuelve el número de plaza donde se encuentra aparcado el vehículo cuya matrícula es la que se le pasa como parámetro. Si no encuentra ningún vehículo con dicha matrícula, la función devuelve -1. Esta función debe ser utilizada en la opción ’B’ para buscar el vehículo según la matrícula.*/
int buscarVehiculo(struct plaza aparcamiento[], int dim, char matricula[]) {
	int i, j, nveces;
	for (i = 0;i < dim;i++) {
		j = 0;
		nveces = 0;
		while (matricula[j] != '\0') {
			if (matricula[j] == aparcamiento[i].matricula[j]) {
				nveces++;
			}
			j++;
		}
		if (nveces == j ) {
			return i;
		}//No se pone ninguna condición más ya que si no ha entrado en el otro if no lo cumple, y por tanto llega a la última plaza sin coincidir.
		if (i == dim  - 1) {
			return -1;
		}
	}
}
void ordenarmatriculas(struct plaza aparcamiento[], int dim) {
	int i, j, k=0;
	struct plaza aux;
	for (i = 0;i < dim;i++) {
		if (aparcamiento[i].estado == 1) {
			for (j = i + 1;j < dim&&k != 7;j++) {
				if (aparcamiento[j].estado == 1) {
					k = 4;
					if (aparcamiento[i].matricula[k] > aparcamiento[j].matricula[k]) {
						aux = aparcamiento[i];
						aparcamiento[i] = aparcamiento[j];
						aparcamiento[j] = aux;
					}
					while (aparcamiento[i].matricula[k] == aparcamiento[j].matricula[k]) {
						if (aparcamiento[i].matricula[k] > aparcamiento[j].matricula[k]) {
							aux = aparcamiento[i];
							aparcamiento[i] = aparcamiento[j];
							aparcamiento[j] = aux;
							break;
						}
						else if (aparcamiento[i].matricula[k] < aparcamiento[j].matricula[k]) {
							k++;
						}
					}
				}

			}
		}
	}
		for (i = 0;i < dim;i++) {
			if (aparcamiento[i].estado == 1) {
			printf("plaza %d - %s\n", i + 1, aparcamiento[i].matricula);
		}
	}
}
void leerFichero(char nombreFichero[], struct plaza aparcamiento[], int * dim) {
	int i;
	i = 0;
	nombreFichero = fopen("vehiculos.txt", "r");
	while (fscanf(nombreFichero, "%d %c %s", &aparcamiento[i].estado, &aparcamiento[i].tipo, aparcamiento[i].matricula) != EOF) {
		i++;
	}
	*dim = i;
	fclose(nombreFichero);
	
}
void salvarFichero(char nombreFichero[], struct plaza aparcamiento[], int dim) {
	int i;
	nombreFichero = fopen("vehiculos.txt", "w");
	for (i = 0;i < dim;i++) {
			fprintf(nombreFichero,"%d %c %s\n",aparcamiento[i].estado,aparcamiento[i].tipo, aparcamiento[i].matricula);
	}
	fclose(nombreFichero);

}
void ticket(struct plaza nplaza,time_t ahora1){//Se pasa por valor la hora de entrada
	FILE *pago;
	clock_t times = clock();
	struct tm *hora;
	time_t ahora;
	time(&ahora);
	double precio;
	FILE *vehiculos;
	pago = fopen("ticket.txt", "w");
	int i;
	hora = localtime(&ahora);
	printf("Hora de salida %d:%d:%d", hora->tm_hour, hora->tm_min, hora->tm_sec);
	times = (ahora-ahora1);// se restan las horas
	precio = TARIFA* times;
		fprintf(pago, "\t\t\tPARKING MB\t\t\t\n\n\n\n");
		fprintf(pago, "\t\tFecha: %d/%d/%d\n", hora->tm_mday, (hora->tm_mon)+1, (hora->tm_year)+1900);
		fprintf(pago, "\t\thora: %d:%d:%d\n", hora->tm_hour, hora->tm_min, hora->tm_sec);
		fprintf(pago, "\t\tDuracion:%d segundos \n", times);
		fprintf(pago, "\t\tPrecio:%f\n", precio);
	fclose(pago);
}