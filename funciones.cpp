#include<WiFi.h>
#include <PubSubClient.h>
#include <esp_system.h>  // librería propia del ESP32
#include "funciones.h"


void conectarMQTT(){
  while(client.connected()==false){
    Serial.print("conectando al broker....");
    if(client.connect("Esp32")){// directamente devuelve un true o false, acaba con el while. Dentro de comillas es el ID del suscriptor, de arduino
        Serial.println(topic_sub);
    }
    else{
      Serial.print("Error, rc=");
      Serial.print(client.state());
      delay(2000);
   }
  }
}

void conectarWifi(){
  Serial.print("conectando a wifi...");
  WiFi.begin(ssid.c_str(), password.c_str()); 
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("wifi conectado");
  Serial.println("IP: ");
  Serial.print(WiFi.localIP());
}

//funcion calback recibe mensaje y lo convierte a texto
void callback(char* topic ,byte* mensaje, unsigned int longitud){// datos que nos dara HiveMQ
  Serial.printf("mensaje recibido en el topico: %s\n",topic);
  String bytesAtexto="";
  for(unsigned int i=0;i<longitud;i++){
    bytesAtexto+=(char)mensaje[i]
  }
  bytesAtexo.trim(); //elimina espacios
  Serial.print(bytesAtexto);
  if(texto=="prender"){
    digitalWrite(LED_PIN, HIGH);
    Serial.print("prendido");
  }
  else if(texto=="apagar"){
    digitalWrite(LED_PIN, LOW);
    Serial.print("led apagado");

  }
  else{
    Serial.print("comando no detectado")
  }
}