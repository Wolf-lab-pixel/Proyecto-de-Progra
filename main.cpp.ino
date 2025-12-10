#include<WiFi.h>
#include <PubSubClient.h>
#include <esp_system.h>  // librería propia del ESP32
#include "funciones.h"
#define LED_PIN 2
//configuracion mqtt

const char* mqtt_server ="d5b26b369ca740beb92128714ca54346.s1.eu.hivemq.cloud";
const int mqtt_port=8883;
const char* topic_sub="Python/Publicador"; //asi se guardan los areglos de caracteres 
String ssid="";
String password="";
WiFiClientSecure espClient;  // conexión segura
PubSubClient client(espClient); // cliente MQTT usando esa conexión
bool sesion= true;

void setup() {
  Serial.begin(115200);// comunicacion entre esp32 y pc
  // configuracion wifi
  Serial.println("inicio de sesion\n");
  Serial.println("INGRESE EL NOMBRE Y CONTRASENIA DEL WIFI");
  //pide datos y boora los espacios o saltos de linea
  while(true){
    if(Serial.available())// recibe texto y lo vulve bytes, si es arriba de 0 es pq se escribio algo
      char c=Serial.read();
      if(c=='\n'){
        break;
      }
      ssid+=c;
  }
  while(true){
    if(Serial.available()){
      char c = Serial.read(); // Usamos char pq recibe letra por letra, byte po byte
      if(c =='\n'){   // cuando el usuario presiona Enter
        break;         // salimos del bucle
      }
      ssid += c;      // acumulamos los caracteres
  }

  conectarWifi();
  espClient.setInsecure(); 
  //configuracion mqtt
  client.setServer(mqtt_server,mqtt_port);
  client.setCallback(callback); //para que client sepa que funcion es el callback: cada que llegue a un mensaje llama al callback
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW)
}

void loop() {  
  if(!sesion){
    esp_restart();
  
  }
  else{
     if(!client.connected()){ // siempre revisa si esta conectado al mqtt y si no lo esta lo conecta
        Serial.print("desconectado");
        conectarMQTT();
      }  
      client.loop(); //revisa si hay mensaje nuevos llama al callback por medio de client.setcallback
      if(!WiFi.connected()){
        Serial.print("desconectado");
        conectarWifi(); 
      }
      Serial.print("estado del wifi\n");
      int estadowifi= WiFi.status();
      switch(estadowifi){
        case 3:
          Serial.println("conectado a wifi");
          break;
        case 4:
          Serial.println("fallo de conexion");
          break;
        case 5:
          Serial.println("conexion perdida");
          break;
        case 6:
          Serial.println("Desconectado");
          break;
      }
      Serial.print("desea acabar secion?: 1.SI 2.NO");
      while(true){
        if(Serial.available()){
          int resp = Serial.parseInt();
          if(resp==1){
            Serial.println("fin sesion");
            sesion=false;  
            break
        }
          else if(resp==2){
            Serial.println("hecho");
        }
        else{
           Serial.println("numero invalido");
        }
      }
  }
}