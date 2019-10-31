#include <bits/stdc++.h>
#include "PaqueteDatagrama.h"

using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char* data, unsigned int longi, char* ip_envio, int puerto_envio) {
	cout << "Puerto: " << puerto_envio << endl;
	
	datos = new char[longi];
	puerto = puerto_envio;
    longitud = longi;
    memcpy(ip, ip_envio, sizeof(ip));
	//strcpy(ip, ip_envio);
	cout << "SUPER IP:" << endl;
	for(int i = 0; i < 16; i++) 
		cout << "ip: " << ip[i];
	cout << endl;
	memcpy(datos, data, longi);
}
PaqueteDatagrama::PaqueteDatagrama(unsigned int longi) {
	longitud = longi;
	datos = new char[longitud];
}

PaqueteDatagrama::~PaqueteDatagrama() {
	delete [] datos;
	longitud = 0;
	puerto = 0;
}

int PaqueteDatagrama::obtienePuerto() {
	return puerto;
}

char* PaqueteDatagrama::obtieneDireccion() {
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud() {
	return longitud;
}

char* PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int p) {
	puerto= p;
}

void PaqueteDatagrama::inicializaIp(char* ip_envio) {
	memcpy(ip, ip_envio, 16);
}

void PaqueteDatagrama::inicializaDatos(char* data) {
	memcpy(datos, data, longitud);
}
