**PROYECTO DE PROGRAMACION**

ESTE PROYECTO CONSTA DE QUE POR MEDIO DE COMANDOS DE VOZ PYTHON, CREE UN MQTT Y ENVIE LA VOZ CONVERTIDA A TEXTO A UN TOPIC EN EL CUAL ESTE SUSCRITO UN PROGRAMA EN C PARA QUE LA ESP32 EJECUTE OPCIONES.
SE DIVIDE EN:

PYTHON
<img width="812" height="581" alt="image" src="https://github.com/user-attachments/assets/b32f8699-6d8f-4637-b59d-92d5c15837b1" />

EL CODIGO UTILIZADO PARA ESTE PROYECTO EN VISUAL STUDIO CODE EN LA PARTE DE PYTHON ES:

import pyaudio #libreria 
import speech_recognition as sr #otra libreria el cual la apodamos sr para su uso 
reconocedor= sr.Recognizer() # llamo a una funcion de speech... que contiene: metodos para calibrar ruido, capturar audio, audio a texto



with sr.Microphone(device_index=2) as mic: #abrimos el microfono y le damos el nombre de mic que se usara debajo de todas las lineas
    reconocedor.adjust_for_ambient_noise(mic,duration=0.2)# 0.2 segundos para reconocer la vos del ruido
    audio= reconocedor.listen(mic)
    texto = reconocedor.recognize_google(audio, language='es-ES')
    texto= texto.lower()
    print("habla")
    print("estas son tus palabras: ",texto)

EN ESTA PARTE VA LA ESTRUCTURA DEL PROYECTO
SRC
INC 
C





 
