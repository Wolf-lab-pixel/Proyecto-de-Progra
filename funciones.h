#ifndef FUNCIONES_H
#define FUNCIONES_H

// Mostrar las cabeceras 
void conectarMQTT();
void conectarWifi();
void callback(char* topic ,byte* mensaje, unsigned int longitud);

# endif