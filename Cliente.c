#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

struct propietario{
	int id_pro;
	char nombre[30];
	char apellido[30];
	char ape_mat [30];
	char direc [50];
	char rfc [13];
	int edad;
	char sexo [1];
}propietario;

struct telefono{
    char tipo[8];
    char no_telefono[10];
    int id_pro;
}telefono;

struct autos
{
	char placa[10];
	int id_pro;
	char color[30];
	int modelo;
	char marca[30];

}autos;

struct accidente
{
	int numero_acc;
	char placa[10];
	int day, month, year;
	char lugar[30];
	char hora[50];

	
}accidente;

void altapropietario(){
	int fd1, fd2;
	char consulta[300], consulta_2[300], last_id[50];

	printf("\t\t---- Alta de propietario ----\n");
	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	printf("Ingrese el nombre: ");
	scanf(" %s",propietario.nombre);
	printf("Ingrese el apellido paterno: ");
	scanf(" %s",propietario.apellido);
	printf("Ingrese el apellido materno: ");
	scanf(" %s",propietario.ape_mat);
	printf("Ingrese la direccion: ");
	scanf("%*c%[^\n]",propietario.direc);
	printf("Ingrese el RFC ejem* MELM900323HO1: ");
	scanf(" %s",propietario.rfc);
	printf("Ingrese la edad: ");
	scanf(" %d",&propietario.edad);
	printf("Ingrese el sexo [m = Masculino, f = Femenino]: ");
	scanf(" %s",propietario.sexo);
	printf("Tipo de telefono:  *ejem[celular] [casa] [oficina] [Ninguno]: ");
	scanf(" %s",telefono.tipo);
	printf("Ingrese el No. Telefono: *ejem[0123456789]: ");
	scanf(" %s",telefono.no_telefono);
	snprintf(consulta, sizeof(consulta),"INSERT INTO propietario(nombre,ape_pat,ape_mat,rfc,direc,edad,sexo) VALUES ('%s','%s','%s','%s','%s',%d,'%s') RETURNING id_pro",propietario.nombre,propietario.apellido,propietario.ape_mat,propietario.rfc,propietario.direc,propietario.edad,propietario.sexo);
	write(fd1,consulta, sizeof(consulta));

	
	read(fd2, last_id, sizeof(last_id));
	telefono.id_pro = atoi(last_id);
	printf("%d\n ", telefono.id_pro);					
	
	write(fd1, "\n", 1);

	snprintf(consulta_2, sizeof(consulta_2),"INSERT INTO telefono(tipo_telefono,no_telefono,id_pro) VALUES ('%s','%s',%d)",telefono.tipo,telefono.no_telefono,telefono.id_pro);					
	write(fd1,consulta_2, sizeof(consulta_2));

	close(fd1);
}

void bajapropietario(){
	int fd1, fd2;
	char consulta[300], consulta_2[300], mensaje[1024];

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);

	printf("\t\t---- Baja de propietario ----\n");
	
	printf("Ingrese el nombre del propietario: ");
	scanf("%s",propietario.nombre);
				   			
	snprintf(consulta, sizeof(consulta),"DELETE FROM telefono WHERE id_pro = (select id_pro FROM propietario WHERE nombre ILIKE '%s')",propietario.nombre);
	write(fd1,consulta, sizeof(consulta));

	write(fd1, "\n", 1);

	snprintf(consulta_2, sizeof(consulta_2),"DELETE FROM propietario WHERE nombre ILIKE '%s'",propietario.nombre);
	write(fd1,consulta_2, sizeof(consulta_2));					
	
	read(fd2, mensaje, sizeof(mensaje));
	printf("Mensaje: %s \n", mensaje);
	
	
	close(fd1);
	close(fd2);
}

void actualizarpropietario(){
	int Opcion, fd1;
	char * consulta[30], opcMenu[2];
	do{
		printf("\t\tActualizar los datos del propietario\n");
		printf("1.- Actualizar su nombre del propietario\n");
		printf("2.- Actualizar su apellido paterno del propietario\n");
		printf("3.- Actualizar su apellido materno del propietario\n");
		printf("4.- Actualizar su RFC del propietario\n");
		printf("5.- Actualizar su direccion del propietario\n");
		printf("6.- Actualizar su edad del propietario\n");
		printf("7.- Actualizar su sexo del propietario\n");
		printf("8.- Actualizar su tipo de telefono del propietario\n");
		printf("9.- Actualizar su numero telefonico del propietario\n");
		printf("10.- Salir\n");
		printf("Elige una opcion: ");
		scanf("%d",&Opcion);
		sprintf(opcMenu,"%d",Opcion);
		fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
		write(fd1,opcMenu,sizeof(opcMenu));
		close(fd1);
		switch (Opcion){
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar El Nombre Del Propietario\n");
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo nombre del propietario: ");
				scanf("%s",propietario.nombre);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET nombre = '%s' WHERE id_pro = %d",propietario.nombre, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 2:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo apellido paterno del propietario: ");
				scanf("%s",propietario.apellido);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET ape_pat = '%s' WHERE id_pro = %d",propietario.apellido, propietario.id_pro);
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 3:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo apellido materno del propietario: ");
				scanf("%s",propietario.ape_mat);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET ape_mat = '%s' WHERE id_pro = %d",propietario.ape_mat, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 4:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo RFC del propietario: ");
				scanf("%s",propietario.rfc);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET rfc = '%s' WHERE id_pro = %d",propietario.rfc, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 5:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);	
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo direccion del propietario: ");
				scanf("%*c%[^\n]",propietario.direc);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET direc = '%s' WHERE id_pro = %d",propietario.direc, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 6:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);	
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese su nueva edad del propietario: ");
				scanf("%d",&propietario.edad);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET edad = %d WHERE id_pro = %d",propietario.edad, propietario.id_pro);
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");

			break;
			case 7:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);				
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese su nueva sexo del propietario [m = Masculino, f = Femenino]: ");
				scanf("%s",propietario.sexo);
				snprintf(consulta, sizeof(consulta),"UPDATE propietario SET sexo = '%s' WHERE id_pro = %d",propietario.sexo, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");

			break;
			case 8:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo tipo de telefono del propietario : ");
				scanf("%s",telefono.tipo);
				snprintf(consulta, sizeof(consulta),"UPDATE telefono SET tipo_telefono = '%s' FROM propietario WHERE telefono.id_pro = propietario.id_pro AND propietario.id_pro = %d",telefono.tipo, propietario.id_pro);	
				close(fd1);
				system("sleep 1.2");

			break;
			case 9:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);
				printf("Ingrese el nuevo numero de telefono del propietario : ");
				scanf("%s",telefono.no_telefono);
				snprintf(consulta, sizeof(consulta),"UPDATE telefono SET no_telefono = '%s' FROM propietario WHERE telefono.id_pro = propietario.id_pro AND propietario.id_pro = %d",telefono.no_telefono, propietario.id_pro);
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");

			break;
			default:
				if (Opcion >= 11 || Opcion == 0){
                    system("clear");
					printf("\t\t----------------ERROR------------------\n");
					printf("Mensaje: No existe la opcion [ %d ], Intentalo de nuevo\n", Opcion);
					system("sleep 2.0");
				}
			break;
		}
	}while(Opcion != 10);
}

void consultapropietario(){
	int fd2;
	char buf[200], filas[130], columnas[130], cadena[200];
	char* campos[] = {"Folio", "Nombre", "Apellido Paterno", "Apellido Materno","RFC","Direccion", "Edad", "Sexo", "Telefono", "Numero"};

	printf("\t\t\t ---------- PROPIETARIOS DISPONIBLES -----------\n");
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);

	read(fd2,filas,sizeof(filas));
	read(fd2,columnas,sizeof(columnas));
	int tuples = atoi(filas);
	int fields = atoi(columnas);
	for(int i=0;i<tuples; i++){
		for(int j=0;j<fields;j++){
			printf("%s: \n", campos[j]);
			read(fd2,cadena,sizeof(cadena));
			printf("%s\n",cadena);
		}
		printf("\n");
	}
	close(fd2);
}

void altaAutos(){
	int fd1, fd2;
	char consulta[300], consulta_2[300];
	char filas[130], columnas[130], cadena[200];
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);

	read(fd2,filas,sizeof(filas));
	read(fd2,columnas,sizeof(columnas));
	int tuples = atoi(filas);
	int fields = atoi(columnas);
	for(int i=0;i<tuples; i++){
		for(int j=0;j<fields;j++){

			read(fd2,cadena,sizeof(cadena));
			printf("%s\t",cadena);
		}
		printf("\n");
	}
	close(fd2);

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	

	printf("\t\t---- Alta de Autos ----\n");
	printf("Ingrese La Placa Del Auto *[XXX-123-X1]: ");
	scanf("%s",autos.placa);
	printf("Ingrese El Modelo Del Auto: *[Año]");
	scanf("%d",&autos.modelo);
	printf("Ingrese El Color Del Auto: ");
	scanf("%s",autos.color);
	printf("Ingrese La Marca Del Auto: ");
	scanf("%s",autos.marca);
	printf("Ingrese El Folio del Propietario: ");
	scanf("%d",&autos.id_pro);


	snprintf(consulta, sizeof(consulta),"INSERT INTO autos(placa,id_pro,modelo,color,marca) VALUES ('%s',%d,%d,'%s','%s')",autos.placa,autos.id_pro,autos.modelo,autos.color,autos.marca);
	write(fd1,consulta, sizeof(consulta));
	
	close(fd1);
}

void bajaAutos(){
	int fd1, fd2;
	char consulta[300], mensaje[1024];

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);
	printf("\t\t---- Baja de Autos ----\n");
	printf("Ingrese La Matricula del Auto: ");
	scanf("%s",autos.placa);

	snprintf(consulta, sizeof(consulta), "DELETE FROM autos WHERE placa ILIKE '%s'", autos.placa);
	write(fd1, consulta, sizeof(consulta));

	read(fd2, mensaje, sizeof(mensaje));
	printf("Mensaje: %s \n", mensaje);
	close(fd1);
	close(fd2);
}

void actualizarAutos(){
	int Opcion, fd1;
	char * consulta[30], opcMenu[2];
	do
	{
		printf("\t\tActualizar los datos del Auto\n");
		printf("1.- Actualizar La Placa del Auto\n");
		printf("2.- Actualizar El Modelo del Auto\n");
		printf("3.- Actualizar El Color del Auto\n");
		printf("4.- Actualizar La Marca del Auto\n");
		printf("5.- Salir\n");
		printf("Elige una opcion: ");
		scanf("%d",&Opcion);
		sprintf(opcMenu,"%d",Opcion);
		fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
		write(fd1,opcMenu,sizeof(opcMenu));
		close(fd1);
		switch (Opcion){
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar La Placa del Auto\n");
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);

				printf("Ingrese La Nueva Placa del Auto *[XXX-123-X1]: ");
				scanf("%s",autos.placa);
				snprintf(consulta, sizeof(consulta),"UPDATE autos SET placa = '%s' WHERE id_pro = %d",autos.placa, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 2:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar El Modelo del Auto\n");
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);

				printf("Ingrese El Nuevo Modelo Del Auto *[Año]: ");
				scanf("%d",&autos.modelo);
				snprintf(consulta, sizeof(consulta),"UPDATE autos SET modelo = %d WHERE id_pro = %d",autos.modelo, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 3:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar El Color del Auto\n");
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);

				printf("Ingrese El Nueva Color del Auto : ");
				scanf("%s",autos.color);
				snprintf(consulta, sizeof(consulta),"UPDATE autos SET color = '%s' WHERE id_pro = %d",autos.color, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			case 4:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar El Nombre Del Propietario\n");
				printf("Ingrese su Folio del propietario: ");
				scanf("%d",&propietario.id_pro);

				printf("Ingrese La Nueva Marca del Auto: ");
				scanf("%*c%[^\n]",autos.marca);
				snprintf(consulta, sizeof(consulta),"UPDATE autos SET marca = '%s' WHERE id_pro = %d",autos.marca, propietario.id_pro);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			default:
				if (Opcion >= 6 || Opcion == 0){
					system("clear");
					printf("\t\t----------------ERROR------------------\n");
					printf("Mensaje: No existe la opcion [ %d ], Intentalo de nuevo\n", Opcion);
					system("sleep 2.0");
				}
			break;
		}
	} while (Opcion != 5);
	
}

void consultaAutos(){
	int fd2;
	char buf[200], filas[130], columnas[130], cadena[200];
	char* campos[] = {"Placa","Modelo", "Color","Marca","Folio","Nombre", "Apellido Paterno", "Apellido Materno", "RFC", "Direccion", "Edad", "Sexo"};

	printf("\t\t\t ---------- PROPIETARIOS DISPONIBLES -----------\n");
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);

	read(fd2,filas,sizeof(filas));
	read(fd2,columnas,sizeof(columnas));
	int tuples = atoi(filas);
	int fields = atoi(columnas);
	for(int i=0;i<tuples; i++){
		for(int j=0;j<fields;j++){
			printf("%s: ", campos[j]);
			read(fd2,cadena,sizeof(cadena));
			printf("%s\n",cadena);
		}
		printf("\n");
	}
	close(fd2);
}

void altaAccidente(){
	
	int fd1, fd2;
	time_t tiempo_actual;
  	struct tm *estructura_tiempo;
	char consulta[300], consulta_2[300];
	char filas[130], columnas[130], cadena[200];
	
	tiempo_actual = time(NULL);
	char* campos[] = {"Placa", "Modelo", "Marca", "Color","Folio del Propietario"};
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);
	
	for (int i = 0; i < 5; i++)
	{
		printf("%s\t\t",campos[i]);
	}
	printf("\n");
	read(fd2,filas,sizeof(filas));
	read(fd2,columnas,sizeof(columnas));
	int tuples = atoi(filas);
	int fields = atoi(columnas);
	for(int i=0;i<tuples; i++){
		for(int j=0;j<fields;j++){
			read(fd2,cadena,sizeof(cadena));
			printf("%s\t\t\b",cadena);
		}
		printf("\n");
	}
	close(fd2);

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);

	printf("\t\t---- Alta de Accidente ----\n");

	printf("Numero de Accidente: ");
	scanf("%d",&accidente.numero_acc);
	printf("Introduzca El No. De La Placa: ");
	scanf("%s",accidente.placa);
	printf("Introduce la fecha en formato dd-mm-yyyy: ");
    scanf("%d-%d-%d", &accidente.day, &accidente.month, &accidente.year);
	printf("Introduce el lugar del accidente: ");
	scanf("%*c%[^\n]",accidente.lugar);
   	// Convertir el tiempo a estructura de tiempo local
	estructura_tiempo = localtime(&tiempo_actual);
	// Formatear la hora y guardarla en una cadena
    strftime(accidente.hora, 50, "%H:%M:%S", estructura_tiempo);

	printf("Hora registrada del accidente %s\n", accidente.hora);

	snprintf(consulta, sizeof(consulta),"INSERT INTO accidente(num_acc,placa,fecha,lugar,hora) VALUES (%d,'%s','%d-%d-%d','%s','%s')",accidente.numero_acc,accidente.placa,accidente.year,accidente.month,accidente.day,accidente.lugar,accidente.hora);
	write(fd1,consulta, sizeof(consulta));
	
	close(fd1);
}

void bajaAccidente(){

	int fd1, fd2;
	char consulta[300], mensaje[1024];

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);
	printf("\t\t---- Baja de Accidente ----\n");
	printf("Introduzca El Folio/No Accidente: ");
	scanf("%d",&accidente.numero_acc);

	snprintf(consulta, sizeof(consulta), "DELETE FROM accidente WHERE num_acc = %d", accidente.numero_acc);
	write(fd1, consulta, sizeof(consulta));

	read(fd2, mensaje, sizeof(mensaje));
	printf("Mensaje: %s \n", mensaje);
	close(fd1);
	close(fd2);
}

void actualizarAccidente(){
	int Opcion, fd1;
	char * consulta[30], opcMenu[2];
	do
	{
		printf("\t\tActualizar los datos del Accidente\n");
		printf("1.- Actualizar El Lugar del Accidente\n");
		printf("2.- Salir\n");
		printf("Elige una opcion: ");
		scanf("%d",&Opcion);
		sprintf(opcMenu,"%d",Opcion);
		fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
		write(fd1,opcMenu,sizeof(opcMenu));
		close(fd1);
		switch (Opcion){
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
				printf("Actualizar El Lugar del Accidente\n");
				printf("Introduzca El Folio/No Accidente: ");
				scanf("%d",&accidente.numero_acc);
				printf("Ingrese El Lugar Del Accidente: ");
				scanf("%*c%[^\n]",accidente.lugar);
				snprintf(consulta, sizeof(consulta),"UPDATE accidente SET lugar = '%s' WHERE num_acc = %d",accidente.lugar,accidente.numero_acc);	
				write(fd1,consulta, sizeof(consulta));
				close(fd1);
				system("sleep 1.2");
			break;
			
			default:
				if (Opcion >= 3 || Opcion == 0){
					system("clear");
					printf("\t\t----------------ERROR------------------\n");
					printf("Mensaje: No existe la opcion [ %d ], Intentalo de nuevo\n", Opcion);
					system("sleep 2.0");
				}
			break;
		}
	} while (Opcion != 2);
	
}

void consultaAccidente(){
	int fd2;
	char buf[200], filas[130], columnas[130], cadena[200];
	char* campos[] = {"No. Accidente","Placa", "Fecha ","Lugar","Hora"};

	printf("\t\t\t ---------- PROPIETARIOS DISPONIBLES -----------\n");
	fd2 = open("/tmp/servidor_a_cliente", O_RDONLY);

	read(fd2,filas,sizeof(filas));
	read(fd2,columnas,sizeof(columnas));
	int tuples = atoi(filas);
	int fields = atoi(columnas);
	for(int i=0;i<tuples; i++){
		for(int j=0;j<fields;j++){
			printf("%s: ", campos[j]);
			read(fd2,cadena,sizeof(cadena));
			printf("%s\n",cadena);
		}
		printf("\n");
	}
	close(fd2);
}


int main(){
	int Opcion, fd1;
	char * consulta[30], opcMenu[2];
	do{
		system("clear");
		printf("\n\t\t AGENCIA DE ACCIDENTES - EL AGUILA\n");
		printf("\t\t ----------------------------------\n\n");
		printf("1. Propietario\n");
		printf("2. Autos\n");
		printf("3. Accidente\n");
		printf("4. Salir\n");
		printf("Elige una opcion: ");
		scanf("%d",&Opcion);

		sprintf(opcMenu,"%d",Opcion);
		fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
		write(fd1,opcMenu,sizeof(opcMenu));
		close(fd1);
		switch (Opcion){
			case 1:
				do
				{
					system("clear");
					memset(opcMenu, '\0', sizeof(opcMenu));

					printf("\n\t\t Control de Propietario\n");
					printf("\t\t -------------------------\n");
					printf("1. Alta de propietario\n");
					printf("2. Baja de propietario\n");
					printf("3. Actualizacion de propietario\n");
					printf("4. Consulta de todo los propietario\n");
					printf("5. Salir\n");
					printf("Elige una opcion: ");
					scanf("%d",&Opcion);
					sprintf(opcMenu,"%d",Opcion);

					fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
					write(fd1,opcMenu,sizeof(opcMenu));
					close(fd1);

					switch (Opcion)
					{
						case 1:
							system("clear");
							altapropietario();
							system("sleep 1.2");

						break;
						case 2:
							system("clear");
							bajapropietario();
							system("sleep 1.2");

						break;
						case 3:
							system("clear");
							actualizarpropietario();
							system("sleep 1.2");
							
						break;
						case 4:
							system("clear");
							consultapropietario();
							system("sleep 5.0");
						break;
						default:
							if (Opcion >= 6 || Opcion == 0){
							system("clear");
								printf("\t\t----------------ERROR------------------\n");
								printf("Mensaje: Opcion Incorrecta, Intentalo de nuevo\n");
								system("sleep 1.8");
							}
						break;
					}
				} while (Opcion != 5);
			break;
			case 2:
				do{
					system("clear");
					memset(opcMenu, '\0', sizeof(opcMenu));
					printf("\n\t\t Control de Autos\n");
					printf("\t\t -------------------------\n");
					printf("1. Alta de Autos\n");
					printf("2. Baja de Autos\n");
					printf("3. Actualizar los datos del auto\n");
					printf("4. Mostrar los datos del auto\n");
					printf("5. Salir\n");
					printf("Elige una opcion: ");
					scanf("%d",&Opcion);
					sprintf(opcMenu,"%d",Opcion);
					fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
					write(fd1,opcMenu,sizeof(opcMenu));
					close(fd1);
					switch (Opcion)
					{
						case 1:
							system("clear");
							altaAutos();
							system("sleep 1.2");

						break;
						case 2:
							system("clear");
							bajaAutos();
							system("sleep 1.2");

						break;
						case 3:
							system("clear");
							actualizarAutos();
							system("sleep 1.2");
							
						break;
						case 4:
							system("clear");
							consultaAutos();
							system("sleep 5.0");
						break;
						default:
							if (Opcion >= 6 || Opcion == 0){
							system("clear");
								printf("\t\t----------------ERROR------------------\n");
								printf("Mensaje: Opcion Incorrecta, Intentalo de nuevo\n");
								system("sleep 1.8");
							}
						break;
					}

				}while (Opcion != 5);
				break;
			case 3:
				do{
					system("clear");
					memset(opcMenu, '\0', sizeof(opcMenu));
					printf("\n\t\t\t Control de Accidente\n");
					printf("\t\t -------------------------\n");
					printf("1. Alta de Accidente\n");
					printf("2. Baja de Accidente\n");
					printf("3. Actualizar los datos del Accidente\n");
					printf("4. Mostrar Todos Los Datos Del Accidente\n");
					printf("5. Salir\n");
					printf("Elige una opcion: ");
					scanf("%d",&Opcion);
					sprintf(opcMenu,"%d",Opcion);
					fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
					write(fd1,opcMenu,sizeof(opcMenu));
					close(fd1);
					switch (Opcion)
					{
						case 1:
							system("clear");
							altaAccidente();
							system("sleep 1.2");

						break;
						case 2:
							system("clear");
							bajaAccidente();
							system("sleep 1.2");

						break;
						case 3:
							system("clear");
							actualizarAccidente();
							system("sleep 1.2");
							
						break;
						case 4:
							system("clear");
							consultaAccidente();
							system("sleep 5.0");
						break;
						default:
							if (Opcion >= 6 || Opcion == 0){
							system("clear");
								printf("\t\t----------------ERROR------------------\n");
								printf("Mensaje: Opcion Incorrecta, Intentalo de nuevo\n");
								system("sleep 1.8");
							}
						break;
					}

				}while (Opcion != 5);
				
			break;
			default:
				if (Opcion >= 5 || Opcion == 0){
                    system("clear");
					printf("\t\t----------------ERROR------------------\n");
					printf("Mensaje: No existe la opcion [ %d ], Intentalo de nuevo\n", Opcion);
					system("sleep 2.0");
				}
			break;
		}
	}while(Opcion != 4);
	return 0;
}