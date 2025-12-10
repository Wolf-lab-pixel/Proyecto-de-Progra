import pyaudio #libreria 
import speech_recognition as sr #otra libreria el cual la apodamos sr para su uso 
import paho.mqtt.client as mqtt


def audio_texto():
    reconocedor= sr.Recognizer() # llamo a una funcion de speech... que contiene: metodos para calibrar ruido, capturar audio, audio a texto
    with sr.Microphone(device_index=2) as mic: #abrimos el microfono y le damos el nombre de mic que se usara debajo de todas las lineas
        print("habla")
        reconocedor.adjust_for_ambient_noise(mic,duration=0.2)# 0.2 segundos para reconocer la vos del ruido
        audio= reconocedor.listen(mic)#captura nuestra voz

        try:
             palabras = reconocedor.recognize_google(audio, language='es-ES')#reconoce en que idioma hablamos
             palabras= palabras.lower()#texto a misnusculas
             print("estas son tus palabras: ",palabras)
             return texto

        except sr.UnknownValueError:
            print("malas noticias, sin palabras")
            return ""




def mqtt_publicador(texto):

    #definimos parametro
    broker="localhost" #nuestra maquina
    port=1883
    topic ="hogar"
    #definimos callback. Es una funcion que pasa como argumento a otra
    #tiene q conectarse para hacer aalgo

    def una_ves_conectado(client,userdata,flags, reason_code, properties):
        print("conectado")
        msj= texto
        client.publish(topic, str(msj))
        #crear un cliente mqtt
    client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect =una_ves_conectado
    client.connect(broker, port,60)#conectar al broker
    client.loop_forever() #el cliente permanecera conectado

texto=audio_texto()
if texto: # tenemos 2 estados si texto es igua a palabras entonces es vrd sino seran "" y eso es flaso
    mqtt_publicador(texto)
else:
    print("sin texto")

