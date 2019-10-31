#include "SocketDatagram.h"
#include "PaqueteDatagrama.h"
#include "IP.h"
#include <cstring>
#include <iostream>
#include<bits/stdc++.h>
#define TAM 2000
#define PUERTO 7200
using namespace std;

int main(void) {
	int time, res, last;
	string srt, firstPart, lastNumber;
	cin >> time >> res >> srt;
	IP ip(srt);
	firstPart = ip.getFirst();
	last = ip.getLast();
	int tiempoPrueba = 1;
	while(1) {
		// ENVIAR SOLICITUD
		for(int i = 0, last = ip.getLast(); i < 5; i++, last++) {
			srt = firstPart + to_string(last);
			cout << "------------- Enviando solicitud a: " << srt << endl; 		

    		char char_array[srt.length() + 1];   
    		strcpy(char_array, srt.c_str()); 
			
			// ENVIAR DATOS: i, resolucion
			SocketDatagrama c(PUERTO);
			int datos[2];
			datos[0] = i; datos[1] = res;
			char envia[2 * sizeof(int)];
			memcpy(envia, &datos, 2 * sizeof(int));
			
			PaqueteDatagrama a((char*)envia, 2 * sizeof(int), char_array, 1234);
			if(c.envia(a)) {				
				// RECIBIR DATOS: tamaño, bandera
				PaqueteDatagrama b(2 * sizeof(int));
				try {
					if(c.recibe(b)) {
						memcpy(datos, b.obtieneDatos(), 2 * sizeof(int));
						int size = 0;
						size = datos[1];
						cout << "Recibi size: " << size << endl;

						if(size > 0) {
							string nombreArchivo = to_string(i) + ".png";
							char char_array[nombreArchivo.length() + 1];   
			    			strcpy(char_array, nombreArchivo.c_str()); 
				
							ofstream out(char_array, ios::binary);
							for(int i = 0; i < size; i++) {
								cout << "Recibiendo paquete " << i + 1 << " de " << size << endl;
								// ESPERAR RESPUESTA
								PaqueteDatagrama d(TAM *  sizeof(int));
								try {
									if(c.recibe(d)) {
										cout << "Puerto: " << d.obtienePuerto() << endl;
										int imagenRecibida[TAM];
										memcpy(imagenRecibida, d.obtieneDatos(), TAM * sizeof(int));
										for(int j = 0; j < TAM; j++) {
											if(imagenRecibida[j] == -1) break;
											out.put(imagenRecibida[j]);
										}
										cout << endl;
									}
								} catch(const char *mensaje) {
									std::cerr << mensaje << endl;
								}
							}
							out.close();
						}
					}
				} catch(const char *mensaje) {
					std::cerr << mensaje << endl;
				}
			}
		}
		cout << "Esperando ... " << time << " millisegundos" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
	return 0;
}
