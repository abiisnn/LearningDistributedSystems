#include <bits/stdc++.h>
#include "PaqueteDatagrama.h"
using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char* data, unsigned int longi, char* ip_envio, int puerto_envio) {
	cout << "IP: " << ip_envio[0] << endl;
	cout << "Puerto: " << puerto_envio << endl;
	
	datos = new char[longi];
    longitud = longi;
    memcpy(datos, data, longi);
    memcpy(ip, ip_envio, sizeof(ip));
	puerto = puerto_envio;
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
	puerto = p;
}

void PaqueteDatagrama::inicializaIp(char* ip_envio) {
	memcpy(ip, ip_envio, 16);
}

void PaqueteDatagrama::inicializaDatos(char* data) {
	memcpy(datos, data, longitud);
}
