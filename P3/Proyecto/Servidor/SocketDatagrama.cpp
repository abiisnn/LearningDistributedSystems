#include "SocketDatagram.h"
#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
using namespace std;

SocketDatagrama::SocketDatagrama(int puerto) {
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
	
	if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
   	// Rellena la dirección local
   	direccionLocal.sin_family = AF_INET;
   	direccionLocal.sin_addr.s_addr = INADDR_ANY;

   	if(puerto == 0)
	   	direccionLocal.sin_port = htons(puerto);
	else
		direccionLocal.sin_port = puerto;

	if(bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)) < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
}
SocketDatagrama::~SocketDatagrama() {
	close(s);
}

// Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama & p) {
	unsigned int clen = sizeof(direccionForanea);
	int res = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, &clen);

	unsigned char inet[4];
	// Copiar a INET
   	memcpy(inet, &direccionForanea.sin_addr.s_addr, 4);

   	string ip1 = to_string(inet[0]);
   	string ip2 = to_string(inet[1]);
   	string ip3 = to_string(inet[2]);
   	string ip4 = to_string(inet[3]);

   	ip1.append(".");
   	ip1.append(ip2);
   	ip1.append(".");
   	ip1.append(ip3);
   	ip1.append(".");
   	ip1.append(ip4);

   	//printf("\n");
   	char dirIP[16];
   	strcpy(dirIP, ip1.c_str());
	p.inicializaIp(dirIP);
	p.inicializaPuerto(direccionForanea.sin_port);	
	return res;
}
//Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama & p) {
	direccionForanea.sin_family = AF_INET;
   	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   	direccionForanea.sin_port = p.obtienePuerto();
	return sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud() *  sizeof(char), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}
