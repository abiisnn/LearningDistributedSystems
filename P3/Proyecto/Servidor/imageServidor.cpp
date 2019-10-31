#include "SocketDatagram.h"
#include "PaqueteDatagrama.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#define TAM 2000
#define PUERTO 1234
using namespace std;

int main(void) {
	while(1) {
		cout << "HOLAAAAAAA" << endl;
		// Recibir solicitud con datos
		SocketDatagrama c(PUERTO);
		PaqueteDatagrama a(2 * sizeof(int));

		cout << "CREEO EL SOCKET" << endl;
		if(c.recibe(a)) {
			cout << "Recibo solicitud" << endl;
			int datos[2];
			memcpy(datos, a.obtieneDatos(), 2 * sizeof(int));	
			system(("scrot " + to_string(datos[0]) + ".png -q " + to_string(datos[1])).c_str());
			
			// Archivo para enviar
			char * memblock;
			int size;
			string nombreArchivo = to_string(datos[0]) + ".png";
			char char_array[nombreArchivo.length() + 1];   
	    	strcpy(char_array, nombreArchivo.c_str()); 
			
			// Calculando tamaño del archivo
			ifstream file (char_array, ios::in|ios::binary|ios::ate);
			size = file.tellg();
			if((size % TAM) == 0) size /= TAM;
			else size = (size / TAM) + 1;
			
			// CREANDO VECTOR DE IMAGEN
			vector<int> imagen;
			ifstream in(to_string(datos[0]) + ".png", ios::binary);

			if(in.is_open()) {
				while(!in.eof()) 
					imagen.push_back(in.get());
			}
			in.close();

			// ENVIAR BANDERA Y TAMAÑO DE LA IMAGEN
			// Enviar señal de que se creo correctamente y tamaño de la imagen
			datos[0] = 1; 
			datos[1] = (imagen.size() / TAM) + 1;
			cout << "envio size: " << datos[1] << endl;
			char envia[2 * sizeof(int)];
			memcpy(envia, &datos, 2 * sizeof(int));
			PaqueteDatagrama b((char*)envia, 2 * sizeof(int), a.obtieneDireccion(), a.obtienePuerto());
			if(c.envia(b)) {
				cout << "Envie a puerto: " << a.obtienePuerto() << endl;
				int imagenEnviar[TAM];
				int m = 0; 	
				for(int i = 0; i < datos[1]; i++) {
					cout << "Enviando paquete " << i + 1 << " de " << datos[1] << endl;
					for(int j = 0; j < TAM; j++) {
						imagenEnviar[j] = imagen[m];
						m++;
					}
					char enviarMensaje[TAM * sizeof(int)];
					memcpy(enviarMensaje, &imagenEnviar, TAM * sizeof(int));
					PaqueteDatagrama e((char*)enviarMensaje, TAM * sizeof(int), a.obtieneDireccion(), a.obtienePuerto());
					int f = c.envia(e);
					std::this_thread::sleep_for(std::chrono::milliseconds(400));
				}	
				cout << "Termine de enviar paquetes" << endl;
			}
		}
		
	}
	return 0;
}
