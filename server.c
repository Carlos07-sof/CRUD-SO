#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libpq-fe.h>
#include <time.h>
#include <string.h>

PGconn *conn;
PGresult * res;
PGresult * respuesta;


void altapropietario(){
	int fd1,fd2;
	char consulta[1024], consulta_2[1024], last_id[50], mensaje[200];

	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
	
	read(fd1, consulta, sizeof(consulta));
	res = PQexec(conn, consulta);	
	
	int id = atoi(PQgetvalue(res, 0, 0));
	sprintf(last_id, "%d", id);

	write(fd2, last_id, sizeof(last_id));
	
	read(fd1, consulta_2, sizeof(consulta_2));

	respuesta = PQexec(conn, consulta_2);

	
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar: %s\n", PQresultErrorMessage(res));
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
	PQclear(res);

	if (PQresultStatus(respuesta) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar la consulta: %s\n", PQresultErrorMessage(respuesta));
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(respuesta);
		PQfinish(conn);
		exit(1);
	}
	close(fd1);
	close(fd2);
	PQclear(respuesta);
}

void bajapropietario(){
	int fd1,fd2;
	char consulta[1024], consulta_2[1024], mensaje[200];

	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
								
	read(fd1, consulta, sizeof(consulta));
	res = PQexec(conn, consulta);
	
	read(fd1, consulta_2, sizeof(consulta_2));
	respuesta = PQexec(conn, consulta_2);	
	
	//printf("%s", consulta);
	
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar ");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
	PQclear(res);
	if (PQresultStatus(respuesta) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(respuesta);
		PQfinish(conn);
		exit(1);
	}
	
	close(fd1);
	close(fd2);
}

void actualizarpropietario(){
	char opcionMenu[2];
	int fd1,fd2, Opcion;
	char consulta[1024];
	
	do{
		fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
		read(fd1,opcionMenu,sizeof(opcionMenu));
		close(fd1);
		Opcion = atoi(opcionMenu);	
		switch (Opcion)
		{
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}				
				printf("Se ha actualizado el nombre del propietario\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");					
			break;
			case 2:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado el apellido paterno del propietario\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");	
			break;
			case 3:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);	
				}
				printf("Se ha actualizado el apellido materno del propietario\n");			
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
			break;
			case 4:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado el rfc del propietario\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
				
			break;
			case 5:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado la direccion del propietario\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
			break;
			case 6:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado la edad del propietario\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");			
			break;
			case 7:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);

				}
				printf("Se ha actualizado el sexo del propietario\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
				
			break;
			case 8:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado el tipo de telefono del propietario\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
										
			break;
			case 9:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
				
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado el numero de telefono del propietario\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
				
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
		
	} while (Opcion != 10);
	
}

void consultapropietario(){
	int fd2, i, j;
	char filas[130], columnas[130];
	char buf[200];
	
	
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);

	res = PQexec(conn, "SELECT propi.id_pro, propi.nombre, propi.ape_pat,propi.ape_mat, propi.rfc,propi.direc,propi.edad,propi.sexo, tel.tipo_telefono,tel.no_telefono FROM propietario propi INNER JOIN telefono tel ON tel.id_pro = propi.id_pro");
	
	int tuples = PQntuples(res);
	int fields = PQnfields(res);

	sprintf(filas,"%d",tuples);
	sprintf(columnas,"%d",fields);

	write(fd2,filas,sizeof(filas));
	write(fd2,columnas,sizeof(columnas));

	if(res != NULL){
		printf("Imprimiendo Todos Los Datos Del Propietario\n");
		for(i = 0; i < tuples; i++){
			for(j = 0; j < fields; j++){
				char *value = PQgetvalue(res, i, j);

				sprintf(buf, value, sizeof(buf));
				
				write(fd2,buf,sizeof(buf));
			}
			printf("\n");
		}
		PQclear(res);
		close(fd2);
	}
	else{
		printf("-- No hay propietarios disponibles --\n");
		
		close(fd2);
		PQclear(res);
	}
}


void altaAutos(){
	int fd1,fd2, i, j;
	char filas[130], columnas[130], consulta[1024], mensaje[200];
	char buf[200];
	
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);

	res = PQexec(conn, "SELECT propi.id_pro, propi.nombre, propi.ape_pat,propi.ape_mat, propi.rfc,propi.direc,propi.edad,propi.sexo, tel.tipo_telefono,tel.no_telefono FROM propietario propi INNER JOIN telefono tel ON tel.id_pro = propi.id_pro");
	
	int tuples = PQntuples(res);
	int fields = PQnfields(res);

	sprintf(filas,"%d",tuples);
	sprintf(columnas,"%d",fields);

	write(fd2,filas,sizeof(filas));
	write(fd2,columnas,sizeof(columnas));

	if(res != NULL){
		printf("Imprimiendo Todos Los Datos Del Propietario\n");
		for(i = 0; i < tuples; i++){
			for(j = 0; j < fields; j++){
				char *value = PQgetvalue(res, i, j);

				sprintf(buf, value, sizeof(buf));
				
				write(fd2,buf,sizeof(buf));
			}
			printf("\n");
		}
		
		PQclear(res);
		close(fd2);
	}
	
	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	read(fd1, consulta, sizeof(consulta));
	//printf("%s",consulta);
	res = PQexec(conn, consulta);

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
		sprintf(mensaje, "Error al insertar ");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		close(fd2);
		exit(1);
	}
	PQclear(res);
	close(fd1);
}

void bajaAutos(){
	int fd1,fd2;
	char consulta[1024], consulta_2[1024], mensaje[200];
	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
	
	read(fd1, consulta, sizeof(consulta));
	res = PQexec(conn, consulta);

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar ");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
	close(fd1);
	close(fd2);

}

void actualizarAutos(){
	char opcionMenu[2];
	int fd1,fd2, Opcion;
	char consulta[1024];
	do
	{
		fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
		read(fd1,opcionMenu,sizeof(opcionMenu));
		close(fd1);
		Opcion = atoi(opcionMenu);	
		switch (Opcion){
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}				
				printf("Se ha actualizado la Placa del Auto\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");					
			break;
			case 2:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado el Modelo del Auto\n");
				PQclear(res);
				close(fd1);
				system("sleep 2.1");	
			break;
			case 3:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);	
				}
				printf("Se ha actualizado el color del Auto\n");			
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
			break;
			case 4:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
			
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}
				printf("Se ha actualizado La Marca del Auto\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");
				
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
	int fd2, i, j;
	char filas[130], columnas[130];
	char buf[200];
	
	
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);

	res = PQexec(conn, "SELECT auto.placa, auto.modelo, auto.color, auto.marca, pro.* FROM autos auto INNER JOIN propietario pro ON pro.id_pro = auto.id_pro");
	
	int tuples = PQntuples(res);
	int fields = PQnfields(res);

	sprintf(filas,"%d",tuples);
	sprintf(columnas,"%d",fields);

	write(fd2,filas,sizeof(filas));
	write(fd2,columnas,sizeof(columnas));

	if(res != NULL){
		printf("Imprimiendo Los Datos: \n");
		for(i = 0; i < tuples; i++){
			for(j = 0; j < fields; j++){
				char *value = PQgetvalue(res, i, j);

				sprintf(buf, value, sizeof(buf));
				
				write(fd2,buf,sizeof(buf));
			}
			printf("\n");
		}
		PQclear(res);
		close(fd2);
	}
	else{
		printf("-- No hay Autos Disponibles --\n");
		close(fd2);
		PQclear(res);
	}
}


void altaAccidente(){
	int fd1,fd2, i, j;
	char filas[130], columnas[130], consulta[1024], mensaje[200];
	char buf[200];
	
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);

	res = PQexec(conn, "SELECT placa,modelo,marca,color,id_pro FROM autos");
	
	int tuples = PQntuples(res);
	int fields = PQnfields(res);
	sprintf(filas,"%d",tuples);
	sprintf(columnas,"%d",fields);

	write(fd2,filas,sizeof(filas));
	write(fd2,columnas,sizeof(columnas));

	if(res != NULL){
		printf("Imprimiendo Todos Los Datos - Autos\n");
		for(i = 0; i < tuples; i++){
			for(j = 0; j < fields; j++){
				char *value = PQgetvalue(res, i, j);
				sprintf(buf, value, sizeof(buf));
				write(fd2,buf,sizeof(buf));
			}
			printf("\n");
		}
		PQclear(res);
		close(fd2);
	}

	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	read(fd1, consulta, sizeof(consulta));
	//printf("%s",consulta);
	res = PQexec(conn, consulta);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
		sprintf(mensaje, "Error al insertar ");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		close(fd2);
		exit(1);
	}
	PQclear(res);
	close(fd1);


}

void bajaAccidente(){
	int fd1,fd2;
	char consulta[1024], consulta_2[1024], mensaje[200];
	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
	
	read(fd1, consulta, sizeof(consulta));
	res = PQexec(conn, consulta);

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		sprintf(mensaje, "Error al insertar ");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
	close(fd1);
	close(fd2);
}

void actualizarAccidente(){
	char opcionMenu[2];
	int fd1,fd2, Opcion;
	char consulta[1024];
	do
	{
		fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
		read(fd1,opcionMenu,sizeof(opcionMenu));
		close(fd1);
		Opcion = atoi(opcionMenu);	
		switch (Opcion){
			case 1:
				system("clear");
				fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
				read(fd1, consulta, sizeof(consulta));
				res = PQexec(conn, consulta);
				if (PQresultStatus(res) != PGRES_COMMAND_OK) {
					printf("Error de consulta\n");
					printf("%s\n", PQerrorMessage(conn));
					PQclear(res);
					PQfinish(conn);
				}				
				printf("Se ha actualizado El Lugar Del Accidente\n");		
				PQclear(res);
				close(fd1);
				system("sleep 2.1");					
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
	int fd2, i, j;
	char filas[130], columnas[130];
	char buf[200];
	
	
	fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);

	res = PQexec(conn, "SELECT * FROM accidente");
	
	int tuples = PQntuples(res);
	int fields = PQnfields(res);

	sprintf(filas,"%d",tuples);
	sprintf(columnas,"%d",fields);

	write(fd2,filas,sizeof(filas));
	write(fd2,columnas,sizeof(columnas));

	if(res != NULL){
		printf("Imprimiendo Los Datos: \n");
		for(i = 0; i < tuples; i++){
			for(j = 0; j < fields; j++){
				char *value = PQgetvalue(res, i, j);

				sprintf(buf, value, sizeof(buf));
				
				write(fd2,buf,sizeof(buf));
			}
			printf("\n");
		}
		PQclear(res);
		close(fd2);
	}
	else{
		printf("-- Sin Registro --\n");
		close(fd2);
		PQclear(res);
	}
}

int main(){

	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128];


	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"agencia_accidente","postgres","unach");
	
	if(PQstatus(conn) != CONNECTION_BAD){
		strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		printf("\t\tSERVIDOR %s\n",output);
			
		mkfifo("/tmp/servidor_a_cliente", 0666);
		mkfifo("/tmp/cliente_a_servidor", 0666);

		char opcionMenu[2];
		int fd1,fd2, Opcion;
		do{
			printf("Servidor - Inicio\n");
			fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);

			read(fd1,opcionMenu,sizeof(opcionMenu));
			close(fd1);
			Opcion = atoi(opcionMenu);	
			switch(Opcion){
				case 1:
					do{
						system("sleep 2");
						printf("Servidor Menu - Propietario\n");
						memset(opcionMenu, '\0', sizeof(opcionMenu));
						fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
						read(fd1,opcionMenu,sizeof(opcionMenu));
						close(fd1);
						Opcion = atoi(opcionMenu);	
						switch (Opcion)
						{
						case 1:
							system("clear");
							printf("SERVIDOR - ALTA DE PROPIETARIO\n");
							close(fd1);
							altapropietario();
							system("sleep 2");
						break;
						case 2:
							system("clear");
							printf("SERVIDOR - BAJA DE PROPIETARIO\n");
							close(fd1);
							bajapropietario();
							system("sleep 2");
							break;
						case 3:
							printf("SERVER - Actualizacion de propietario\n\n ");
							close(fd1);
							actualizarpropietario();
							system("sleep 2");
							break;
						case 4:
							system("clear");
							printf("SERVIDOR - LISTA DE PROPIETARIOS\n ");
							close(fd1);
							consultapropietario();
							system("sleep 2");
							break;
						
						default:
							if(Opcion >= 6 || Opcion == 0){
								printf("OPCION INVALIDA En el servidor.\n");
								system("sleep 1.8");
								system("clear");
							}
							break;
						}
					}while (Opcion != 5);
					break;
				case 2:
					do
					{
						system("sleep 2");
						printf("Servidor Menu - Autos\n");
						memset(opcionMenu, '\0', sizeof(opcionMenu));
						fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
						read(fd1,opcionMenu,sizeof(opcionMenu));
						close(fd1);
						Opcion = atoi(opcionMenu);	
						switch (Opcion)
						{
							case 1:
							system("clear");
							printf("SERVIDOR - ALTA DE AUTOS\n");
							close(fd1);
							altaAutos();
							system("sleep 2");
						break;
						case 2:
							system("clear");
							printf("SERVIDOR - BAJA DE AUTOS\n");
							close(fd1);
							bajaAutos();
							system("sleep 2");
							break;
						case 3:
							printf("SERVER - Actualizacion de AUTOS\n\n ");
							close(fd1);
							actualizarAutos();
							system("sleep 2");
							break;
						case 4:
							system("clear");
							printf("SERVIDOR - LISTA DE AUTOS\n ");
							close(fd1);
							consultaAutos();
							system("sleep 2");
							break;
						
						default:
							if(Opcion >= 6 || Opcion == 0){
								printf("OPCION INVALIDA En el servidor.\n");
								system("sleep 1.8");
								system("clear");
							}
							break;
						}
						
					} while (Opcion != 5);
					break;	
				case 3:
					do
					{
						system("sleep 2");
						printf("Servidor Menu - Accidentes\n");
						memset(opcionMenu, '\0', sizeof(opcionMenu));
						fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
						read(fd1,opcionMenu,sizeof(opcionMenu));
						close(fd1);
						Opcion = atoi(opcionMenu);	
						switch (Opcion)
						{
							case 1:
							system("clear");
							printf("SERVIDOR - ALTA DE Accidentes\n");
							close(fd1);
							altaAccidente();
							system("sleep 2");
						break;
						case 2:
							system("clear");
							printf("SERVIDOR - BAJA DE AUTOS\n");
							close(fd1);
							bajaAccidente();
							system("sleep 2");
							break;
						case 3:
							printf("SERVER - Actualizacion de AUTOS\n\n ");
							close(fd1);
							actualizarAccidente();
							system("sleep 2");
							break;
						case 4:
							system("clear");
							printf("SERVIDOR - LISTA DE Accidente\n ");
							close(fd1);
							consultaAccidente();
							system("sleep 2");
							break;		
						default:
							if(Opcion >= 6 || Opcion == 0){
								printf("OPCION INVALIDA En el servidor.\n");
								system("sleep 1.8");
								system("clear");
							}
							break;
						}
						
					} while (Opcion != 5);
					break;	
				default:
					if(Opcion >= 5 || Opcion == 0){
						printf("OPCION INVALIDA.\n");
						system("sleep 1.8");
						system("clear");
					}
				break;
			}
		}while(Opcion !=4);
	}else{
		printf("Mensaje: \t ERROR De Conexion \n");
	}

}
