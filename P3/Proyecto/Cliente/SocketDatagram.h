#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include "PaqueteDatagrama.h"

#ifndef SocketDatagrama_H_
#define SocketDatagrama_H_
class SocketDatagrama
{
	public:
	SocketDatagrama(int);
	~SocketDatagrama();
	//Recibe un paquete tipo datagrama proveniente de este socket
	int recibe(PaqueteDatagrama & p);
	//Envía un paquete tipo datagrama desde este socket
	int envia(PaqueteDatagrama & p);
	private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	struct timeval timeout;
	int s; //ID socket
};
#endif

